<?php
/**
 * @file
 * Defines banrep_core module functionality.
 */
module_load_include('inc', 'banrep_gestion_ppi', 'banrep_gestion_ppi.functions');
/**
 * Callback del menu que arma el html del detalle de ascenso.
 */
function banrep_gestion_ppi_page($uid) {
  $usuario = user_load($uid);

  if (!isset($usuario->uid) || $usuario->uid <= 0) {
    return 'No existe Plan de promoción a la investigación';
  }

  $route    = $usuario->field_ruta['und'][0]['target_id'];
  $scale    = $usuario->field_usr_escalafon['und'][0]['tid'];
  $requirements = get_requirements_ppi($scale, $route);
  $form     = drupal_get_form('banrep_gestion_ppi_form', $requirements, $usuario);
  $name = 'profile_info_order_' . $uid;
  $profile_info_order = variable_get($name, FALSE);

  if ($uid == $user->uid) {
    $show_edit = TRUE;
  }

  $user_data = get_current_user_data($uid);
  $field_full_name = isset($user_data['field_full_name']) ? $user_data['field_full_name'] : '';
  $user_data['only_personal_information'] = TRUE;
  drupal_add_library('system', 'ui.sortable');
  drupal_add_library('system', 'ui.tabs');
  drupal_add_library('system', 'ui.accordion');
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile.js');
  $content = theme('banrep_core_profile', array('user_data' => $user_data, 'profile_info_order' => $profile_info_order));
  $html = $content;
  $html .= drupal_render($form);
  return $html;
}
/**
 * Funcion que pinta el formulario del detalle de ascenso.
 */
function banrep_gestion_ppi_form($form, &$form_state, $requirements = array(), $uid = NULL) {
  global $user;
  $form = array();
  $nid_log = _get_node_log_ppi($uid->uid, $requirements['nid'], FALSE);
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $requirements['nid'],
  );
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $uid->uid,
  );
  $form['rq_publiacion'] = array(
  '#type' => 'fieldset',
  '#title' => t('Requisitos de publicaciones y/o actividades'),
  '#tree' => TRUE,
  );

  $user_ppi = user_load($uid->uid);

  $crumbs = array();
  $crumbs[] = l(t('Home'), '');
  $crumbs[] = l(t('Gestión de PPI'), 'admin/content/gestion-ppi');
  $crumbs[] = l(t('Perfil'), 'profile/'.$user_ppi->uid);
  $crumbs[] = l(t($user_ppi->name), 'profile/gestion-ppi/'.$user_ppi->uid);
  drupal_set_breadcrumb($crumbs);

  if ($requirements['publications_req']) {
    switch ($requirements['publications_req']) {
      case '1'://Creación de usuario (Todo)
        $date_query = $user_ppi->created;
        break;
      case '2'://Penúltimo puntaje
        $date_query = $user_ppi->field_fecha_penultimo_puntaje[LANGUAGE_NONE][0]['value'];
        break;
      case '3'://Último puntaje
        $date_query = $user_ppi->field_date_last_score[LANGUAGE_NONE][0]['value'];
        break;
      case '4'://Ultima solicitud beneficios
        $date_query = $user_ppi->field_last_redemption_date[LANGUAGE_NONE][0]['value'];
        break;
    }
  
    $pub_user_type = array();
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'pub_user')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_user_reference', 'target_id', $uid->uid, '=')
    ->fieldCondition('field_estado_publicaci_n', 'value', 3, '=');
    $result = $query->execute();

    foreach ($result['node'] as $nid => $value) {
      $node_child = node_load($value->nid);
      $node_father = node_load($node_child->field_publicacion[LANGUAGE_NONE][0]['target_id']);
      if (isset($node_father->field_date) && !empty($node_father->field_date) && isset($date_query) && !empty($date_query) && $node_father->field_date['und'][0]['value'] > $date_query) {
        $pos_father = _search_father_taxonomy_term($node_father->field_pub_type['und'][0]['value'], $node_father->field_role_within_publication['und'][0]['tid']);
        $pub_user_type[$pos_father]['type'] = $node_father->field_pub_type[LANGUAGE_NONE][0]['value'];
        $pub_user_type[$pos_father]['values'][] = array(
          'nid' => $node_child->nid,
          'title' => $node_father->title,
          'points' => $node_child->field_puntaje['und'][0]['value'],
          'date' => isset($node_father->field_act_date_start['und'][0]['value']) ? date( "m/d/Y", $node_father->field_act_date_start['und'][0]['value']) : '',
          'type' => taxonomy_term_load($node_father->field_pub_type['und'][0]['value'])->name,
          'charge' => taxonomy_term_load($node_father->field_role_within_publication['und'][0]['tid'])->name
        );
      }
    }

    foreach ($pub_user_type as $nid => $value) {
      $e = taxonomy_term_load( $nid );
      foreach ($e->field_puntajes[LANGUAGE_NONE] as $field_puntaje) {
        $field_collection_item_value = $field_puntaje['value']; 
        $field_collection_value = entity_load('field_collection_item', array($field_collection_item_value));
        if ($user_ppi->field_ruta[LANGUAGE_NONE][0]['target_id'] == $field_collection_value[key($field_collection_value)]->field_ruta[LANGUAGE_NONE][0]['target_id']) {
          $type = '';
          switch ($field_collection_value[key($field_collection_value)]->field_acomula_en[LANGUAGE_NONE][0]['field_name']) {
            case 'field_puntaje_acumulado':
             $type = 'Academico';
              break;
            case 'field_acumulado_general':
             $type = 'General';
              break;
            case 'field_puntaje_br':
             $type = 'BR';
              break;
          }
          $pub_user_type[$nid]['acumula'] = $type;
        }
      }
    }
  }

  $html = '<table class="requirements__publications">';
  foreach ($requirements['publications'] as $keyg => $group) {
    if (isset($group['operator']) && !empty($group['operator'])) {
      $html .= '<tr><td colspan="6" class="operator-groups-conditions">' . $group['operator'] . '</td></tr>';
    }
    $html .= '<tr><td colspan="6">
    <table class="requirements__publications">
    <tr>
      <th>Nombre requisito</th>
      <th>Valor requisito</th>
      <th>Valor actual</th>
      <th>Tipo puntaje</th>
      <th>Calificación</th>
      <th>Aprobación</th>
      <th>Observaciones</th>
    </tr>';

    foreach ($group['conditions'] as $keyc => $condition) {
      $form['rq_publiacion'][$keyg][$keyc] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('row')),
      );
      $operator = '';
      if (isset($condition['operator']) && !empty($condition['operator'])) {
        $operator = $condition['operator'] . ' ';
      }
      $name_item = 'rq_publiacion_' . $keyg . '_' . $keyc;
      $comments = _output_comments($name_item, $nid_log);
      $html .= "<tr>";
      $input_value = '';
     
      switch ($condition['type']) {
        case 'PUNTAJE':
        case 'CANTIDAD':
          if (isset($condition['serie'])) {
            $name    = node_load($condition['serie']);
            $name    = $name->title;
            $info_user = _get_publications_user_ppi($uid->uid, $condition['serie'], TRUE, $condition['type'], $requirements['general']['date_start_pub']);
          }
          else {
            if (isset($condition['concept'])) {
              $concepts  = explode(',', $condition['concept']);
              $is_activity = FALSE;
              if (isset($concepts[0]) && $concepts[0] == 211) {
                $is_activity = TRUE;
              }
              $size    = count($concepts);
              $name    = _get_concept_publications_ppi($condition['concept']);
              $info_user = _get_publications_user_ppi($uid->uid, $concepts[$size - 1], FALSE, $condition['type'], $requirements['general']['date_start_pub'],$is_activity);
            }
          }
          if(empty($condition['serie']) && empty($condition['concept']) ){
            $name = 'PUBLICACIONES';
            $info_user = user_load($uid->uid)->field_puntaje_acumulado[LANGUAGE_NONE][0]['value'];
          }

          /*if(isset($pub_user_type[$condition['concept']])){
            $pub_user_type_f = '<br><a id="'.$condition['concept'].'" class="pub_dropdown">Listado de publicaciones</a><div class="pub_dropdown_'.$condition['concept'].'" style="display: none;"><ul>';
            foreach ($pub_user_type[$condition['concept']]['values'] as $key => $value) {
              $pub_user_type_f .= '<li>'.$value['title'].'</li>';
            }
            $pub_user_type_f .= '</ul></div>';
          }else {
            $pub_user_type_f =  '';
          }*/

          $html .= '<td id="'.$condition['concept'].'">' . $operator . $name . ' (' . $condition['type'] . ')</td>';
          $html .= '<td>' . $condition['value'] . '</td>'; // falta para libros // valor requisito
          $html .= '<td>' . $info_user . $input_value . '</td>'; // falta para libros
          break;
      }

      $calificacion = 'No cumple';
      $checked = '';
      if ($info_user >= $condition['value']) {
        $checked    = "checked";
        $calificacion = 'Cumple';
      }
      if (isset($comments['html']) && !empty($comments['html'])) {
        if ($comments['aprobado'] == 1) {
          $checked = 'checked';
        }else {
          $checked = '';
        }
      }
      $html .= '<td>'.$pub_user_type[$condition['concept']]['acumula'].'</td>';
      $html .= '<td>' . $calificacion . '</td>';
      $html .= '<td><input type="checkbox" name="rq_publiacion_' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
      $html .= '<td> <textarea rows="3" cols="20" name="rq_publiacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . ' </td>';
      $html .= "</tr>";

      if (isset($pub_user_type[$condition['concept']])) {
        $sub_html = '<table style="text-align: center;"><tr><th>Publicación</th><th style="text-align: center;">Fecha Aprobación</th><th style="text-align: center;">Puntos</th><th style="text-align: center;">Rol</th><th style="text-align: center;">Tipo Publicación</th></tr>';
        foreach ($pub_user_type[$condition['concept']]['values'] as $key => $value) {
          $sub_html .= '<tr><td id="'.$value['nid'].'" style="text-align: left;">'.$value['title'].'</td><td>'.$value['date'].'</td><td>'.$value['points'].'</td><td>'.$value['charge'].'</td><td>'.$value['type'].'</td></tr>';
        }
        $sub_html .= '</table>';
        $html .= '
        <tr>
          <td colspan="7">
            <a id="'.$condition['concept'].'" class="pub_dropdown">Listado de publicaciones</a>
            <div class="pub_dropdown_'.$condition['concept'].'" style="display: none;">'.$sub_html.'</div>
          </td>
        </tr>';
      }
    }
    $html .= '</table></td></tr>';
  }
  $html .= '</table>';

  $form['rq_publiacion']['html'] = array(
    '#markup' => $html,
  );
  
  $form['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Update'),
  );
  drupal_add_js(drupal_get_path('module', 'banrep_gestion_ppi') . '/gestion_ppi_validate.js');
  return $form;
}
function banrep_gestion_ppi_form_submit($form,&$form_state){
  global $user;
  $values = $form_state['input'];
  if (isset($values['uid']) && !empty($values['uid']) && $values['uid'] > 0 && isset($values['rid'])){
    $log = _get_node_log_ppi($values['uid'],$values['rid']);
    $flag_aprobado = TRUE;
    foreach ($values as $key => $value) {
      $pos = strpos($key, 'observaciones');
      if ($pos !== false) {
        if (!empty($value)){
           $item = entity_create('field_collection_item', array('field_name' => 'field_reglas'));
           $item->setHostEntity('node', $log);
           $key_aprobado = str_replace("observaciones", 'aprobado', $key);
           $item->field_id['und'][0]['value']         = str_replace("_observaciones", '', $key);
           if (isset($values[$key_aprobado])){
            $item->field_estado_regla['und'][0]['value'] = 1;
           }
           else {
            $flag_aprobado = FALSE;
            $item->field_estado_regla['und'][0]['value'] = 0;
           }
           $date = format_date(time(),'custom','d/m/Y h:i');
           $item->field_comentario['und'][0]['value']     = $date . ' - '. $user->name . ': ' . $value;
           $item->field_usuario_update['und'][0]['target_id'] = $user->uid;
           $key_valor = str_replace("observaciones", 'valor', $key);
           if(isset($values[$key_valor])){
            $item->field_valor['und'][0]['value'] = $values[$key_valor];
           }
           $item->save();
        }
        else {
           $key_aprobado = str_replace("observaciones", 'aprobado', $key);
           if (!isset($values[$key_aprobado])){
            $flag_aprobado = FALSE;
           }
        }
      }
    }
    if ($flag_aprobado){
      if (in_array('Admin GT', $user->roles)){
        $usuario = user_load($values['uid']);
        $usuario->field_estado_plan_carrera['und'][0]['value'] = 'APROBADO_PARA_CAMBIO_DE_CARGO';
        user_save($usuario);
        $log->field_fullfilled_requirements['und'][0]['value'] = 1;
        node_save($log);
        $to = $usuario->mail;
        $params = array();
        if (drupal_mail('banrep_gestion_ppi', 'plan_carrera', $to, language_default(), $params)){
        drupal_set_message(t('Your message has been sent.'));
        }
        else {
          drupal_set_message(t('There was an error send mail for this user. Please try again later'));
        }
      }
    }
  }
}
function _output_comments ($name_item,$nid_log){
  $comments = _get_log_by_rule_ppi($name_item,$nid_log);
  $output_comments = array('html'=>'','aprobado'=>'');
  $cont = 0;
  foreach ($comments as  $comment) {
     $item       = field_collection_item_load($comment->entity_id);
     $usuario_comment  = user_load($item->field_usuario_update['und'][0]['target_id']);
     $output_comments['html'] .= '<div class="comment"><div class="text">'. $item->field_comentario['und'][0]['value'] . '</div></div>';
     if ($cont==0){
       $output_comments['aprobado'] = $item->field_estado_regla['und'][0]['value'];
       $output_comments['valor'] = isset($item->field_valor['und'][0]['value'])?$item->field_valor['und'][0]['value']:'';
       $cont++;
     }
  }
  return $output_comments;
}

function _search_father_taxonomy_term($tfather, $tchild){
  $name = 'categorias_de_conceptos';
  $voc = taxonomy_vocabulary_machine_name_load($name);
  $tree = taxonomy_get_tree($voc->vid);
  $terms = [];

  foreach ($tree as $term) {
    if($term->depth == 0){
      $father = $term->tid;
      $terms[$term->tid] = array('tid' => $term->tid, 'name' => $term->name);
    }else {
      $terms[$father]['values'][$term->tid] = array('tid' => $term->tid, 'name' => $term->name);
    }
  }
  
  if(isset($terms[$tfather]['values'][$tchild])){
    return $tchild;
  }
  return $tfather;
}