<?php
/**
 * @file
 * Defines banrep_core module functionality.
 */
module_load_include('inc', 'banrep_plan_carrera', 'banrep_plan_carrera.functions');
/**
 * Callback del menu que arma el html del detalle de ascenso.
 */
function banrep_plan_carrera_page($uid) {
  $usuario = user_load($uid);
  if (!isset($usuario->uid) || $usuario->uid <= 0) {
    return 'No existe plan de carrera';
  }
  update_redemption_date($uid);
  $route    = $usuario->field_ruta['und'][0]['target_id'];
  $scale    = $usuario->field_usr_escalafon['und'][0]['tid'];
  $requirements = get_requirements($scale, $route, $usuario->uid);
  $form     = drupal_get_form('banrep_plan_carrera_form', $requirements, $usuario);
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
function banrep_plan_carrera_form($form, &$form_state, $requirements = array(), $uid = NULL) {
  global $user;
  $form = array();
  $nid_log = _get_node_log($uid->uid, $requirements['nid'], FALSE);
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $requirements['nid'],
  );
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $uid->uid,
  );
  $form['rq_tiempo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Requisitos de tiempo'),
    '#tree' => TRUE,
  );
  $tipo_tiempo = list_allowed_values(field_info_field('field_pcr_tipo_tiempo'));

  $html = '<table class="requirements__time">';
    $html .= '<tr>';
    $html .= '<th>Nombre requisito</th>';
    $html .= '<th>Valor requisito</th>';
    $html .= '<th>Valor actual</th>';
    $html .= '<th>Calificación</th>';
    $html .= '<th>Aprobación</th>';
    $html .= '<th>Observaciones</th>';
    $html .= '</tr>';
    foreach ($requirements['time'] as $key => $value) {
      $info_user = _get_time_user($uid, $key);
      $html .= '<tr>';
      $html .= '<td>' . $tipo_tiempo[$key] . '</td>';
      $html .= '<td>' . $value . '</td>';
      $html .= '<td>' . $info_user . '</td>';
      $checked = "";
      $calificacion = 'No cumple';
      if ($info_user >= $value) {
        $checked = "checked";
        $calificacion = 'Cumple';
      }
      $html .= '<td>' . $calificacion . '</td>';
      $name_item = 'rq_tiempo_' . $key;
      $comments = _output_comments($name_item, $nid_log);
      if (isset($comments['html']) && !empty($comments['html'])) {
        if ($comments['aprobado'] == 1) {
        $checked = 'checked';
        }
        else {
        $checked = '';
        }
      }
      $html .= '<td> <input type="checkbox" class="condition" name="rq_tiempo_' . $key . '_aprobado" ' . $checked . '></td>';
      $html .= '<td><textarea rows="3" cols="20" name="rq_tiempo_' . $key . '_observaciones"></textarea>' . $comments['html'] . '  </td>';
      $html .= '</tr>';
    }
  $html .= '</table>';

  $form['rq_tiempo']['html'] = array(
  '#markup' => $html,
  );

  $form['rq_publiacion'] = array(
  '#type' => 'fieldset',
  '#title' => t('Requisitos de publicaciones y/o actividades'),
  '#tree' => TRUE,
  );

  $html = '<table class="requirements__publications">';
  

   
  foreach ($requirements['publications'] as $keyg => $group) {

    if (isset($group['operator']) && !empty($group['operator'])) {
      $html .= '<tr><td colspan="6" class="operator-groups-conditions">' . $group['operator'] . '</td></tr>';
    }
    $html .= '<tr><td colspan="6">';
    $html .= '<table class="requirements__publications">';
    $html .= '<tr>';
    $html .= '<th>Nombre requisito</th>';
    $html .= '<th>Valor requisito</th>';
    $html .= '<th>Valor actual</th>';
    $html .= '<th>Tipo puntaje</th>';
    $html .= '<th>Calificación</th>';
    $html .= '<th>Aprobación</th>';
    $html .= '<th>Observaciones</th>';
    $html .= '</tr>';
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
      /*if (in_array('Admin GT', $user->roles)) {
      $input_value = '<input type="text" size="4" class="form-text" name="rq_publiacion_' . $keyg . '_' . $keyc . '_valor" value ="' . $comments['valor'] . '"placeholder="Nuevo valor">';
      }*/
      switch ($condition['type']) {
      case 'PUNTAJE':
      case 'CANTIDAD':
        if (isset($condition['serie'])) {
          $name    = node_load($condition['serie']);
          $name    = $name->title;
          $info_user = _get_publications_user($uid->uid, $condition['serie'], TRUE, $condition['type'], $requirements['general']['date_start_pub']);
        }
        else {

          if (isset($condition['concept'])) {
            $concepts  = explode(',', $condition['concept']);
            $is_activity = FALSE;
            if (isset($concepts[0]) && $concepts[0] == 211) {
              $is_activity = TRUE;
            }
            $size    = count($concepts);
            $name    = _get_concept_publications($condition['concept']);
            $info_user = _get_publications_user($uid->uid, $concepts[$size - 1], FALSE, $condition['type'], $requirements['general']['date_start_pub'],$is_activity);

          }
        }
        if(empty($condition['serie']) && empty($condition['concept']) ){
          $name = 'PUBLICACIONES';
          $info_user = user_load($uid->uid)->field_puntaje_acumulado[LANGUAGE_NONE][0]['value'];
          
        }
        $html .= '<td>' . $operator . $name . ' (' . $condition['type'] . ')</td>';
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
        }
        else {
          $checked = '';
        }
      }

      $html .= '<td>' . $condition['concept_type'] . '</td>';
      $html .= '<td>' . $calificacion . '</td>';
      $html .= '<td><input type="checkbox" name="rq_publiacion_' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
      $html .= '<td> <textarea rows="3" cols="20" name="rq_publiacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . ' </td>';
      $html .= "</tr>";
      $html .= '<tr>';
      $html .= '<td colspan="7">';
      $html .= $condition['html'];
      $html .= '</td>';
      $html .= '</tr>';
    }
    $html .= '</table></td></tr>';
  }
  $html .= '</table>';

  $form['rq_publiacion']['html'] = array(
    '#markup' => $html,
  );
  
  $html = '<table class="requirements__publications">';

  $form['rq_formacion'] = array(
    '#type' => 'fieldset',
    '#title' => t('Requisitos formación desarrollo y desempeño'),
    '#tree' => TRUE,
  );

  $html .= '<tr><td colspan="6">';
  $html .= '<table class="requirements__publications">';
    $html .= '<tr>';
    $html .= '<th></th>';

    $html .= '<th>Nombre requisito</th>';
    $html .= '<th>Valor requisito</th>';
    $html .= '<th>Valor actual</th>';
    $html .= '<th>Calificación</th>';
    $html .= '<th>Aprobación</th>';
    $html .= '<th>Observaciones</th>';
    $html .= '</tr>';
    $html .= '<tbody>';
    foreach ($requirements['training'] as $keyg => $group) {

      $name = _get_concept_publications($group[0]);
      $files = _get_training_by_tid($uid->uid,$group[0]);
      $info_user = FALSE;
      $strFiles = "";
      $keyc = 0;
      if (count($files) > 0 ) {
        $info_user = TRUE;
        $strFiles = "<br/><ul>";
        foreach($files as $arfile) {
          $strFiles .= "<li><a href='".$arfile['url']."' target='_blank'>".$arfile['name']."</a></li>";
        }
        $strFiles .= "</ul>";
      }

      $calificacion = 'No cumple';
      $checked = '';
      if ($info_user) {
        $checked = "checked";
        $calificacion = 'Cumple';
      }

      $name_item = 'rq_formacion_' . $keyg . '_' . $keyc;
      $comments = _output_comments($name_item, $nid_log);
      if (isset($comments['html']) && !empty($comments['html'])) {
        if ($comments['aprobado'] == 1) {
          $checked = 'checked';
        }
        else {
          $checked = '';
        }
      }

      $html .= '<tr>';
        $html .= '<td>'. $group['operator'] .'</td>';
        $html .= '<td>'. $name . $strFiles.'</td>';
        $html .= '<td>'.$info_user.'</td>';
        $html .= '<td>'. $calificacion .'</td>';
        
        $html .= '<td><input type="checkbox" name="rq_formacion_' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
        $html .= '<td> <textarea rows="3" cols="20" name="rq_formacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . '</td>';
      $html .= '</tr>';
    }
    $html .= '</tbody>';

  
  $html .= '</table>';

//   foreach ($requirements['training'] as $keyg => $group) {
//   if (isset($group['operator']) && !empty($group['operator'])) {
//     $html .= '<tr><td colspan="6" class="operator-groups-conditions">' . $group['operator'] . '</td></tr>';
//   }
//   $html .= '<tr><td colspan="6">';
//   $html .= '<table class="requirements__publications">';
//   $html .= '<tr>';
//   $html .= '<th>Nombre requisito</th>';
//   $html .= '<th>Valor requisito</th>';
//   $html .= '<th>Valor actual</th>';
//   $html .= '<th>Calificación</th>';
//   $html .= '<th>Aprobación</th>';
//   $html .= '<th>Observaciones</th>';
//   $html .= '</tr>';
//   $flag_first_condition = TRUE;
//   foreach ($group as $keyc => $condition) {
//     $html .= "<tr>";
//     if ($keyc == 'operator') {
//     continue;
//     }
//     if ($flag_first_condition) {
//     $operator = '';
//     $flag_first_condition = FALSE;
//     }
//     else {
//     $operator = 'Y ';
//     }
//     $name = _get_concept_publications($condition);
//     $files = _get_training_by_tid($uid->uid,$condition);
//     $info_user = FALSE;
//     $strFiles = "";
//     if (count($files) > 0 ) {
//     $info_user = TRUE;
//     $strFiles = "<br/><ul>";
//     	foreach($files as $arfile) {
//     	  $strFiles .= "<li><a href='".$arfile['url']."' target='_blank'>".$arfile['name']."</a></li>";
//     	}
//     	$strFiles .= "</ul>";
//     }
//     $html .= '<td>' . $operator . $name . $strFiles . '</td>';
//     $html .= '<td>1</td>';
//     $html .= '<td>' . $info_user . '</td>';

//     $calificacion = 'No cumple';
//     $checked = '';
//     if ($info_user) {
//     $checked = "checked";
//     $calificacion = 'Cumple';
//     }

//     $html .= '<td>' . $calificacion . '</td>';

//     $name_item = 'rq_formacion_' . $keyg . '_' . $keyc;
//     $comments = _output_comments($name_item, $nid_log);
//     if (isset($comments['html']) && !empty($comments['html'])) {
//     if ($comments['aprobado'] == 1) {
//       $checked = 'checked';
//     }
//     else {
//       $checked = '';
//     }
//     }
//     $html .= '<td><input type="checkbox" name="rq_formacion_' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
//     $html .= '<td> <textarea rows="3" cols="20" name="rq_formacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . '</td>';
//     $html .= "</tr>";
//   }
//   $html .= '</table></td></tr>';
//   }
  $html .= '</table>';
  $form['rq_formacion']['html'] = array(
  '#markup' => $html,
  );
  /*if (in_array('Admin GT', $user->roles)) {
  $form['rq_administrativos'] = array(
    '#type' => 'fieldset',
    '#title' => t('Requisitos administrativos'),
    '#tree' => TRUE,
  );
  $html = '<table class="requirements__administrative">';
  $html .= '<tr>';
  $html .= '<th>Nombre requisito</th>';
  $html .= '<th>Aprobación</th>';
  $html .= '<th>Observaciones</th>';
  $html .= '</tr>';
  $requirements__administrative = array(
    1 => 'Requerimientos en términos de conocimiento',
    2 => 'Requerimientos de experiencia',
    3 => 'Plan de formación durante su permanencia en el cargo',
    4 => 'Nivel de funciones y complejidad del cargo',
    5 => 'Indicadores de desempeño:  resultados y competencias para cada nivel',
  );
  foreach ($requirements__administrative as $key => $value) {
    $name_item = 'rq_administrative_' . $key;
    $comments = _output_comments($name_item, $nid_log);
    $checked = '';
    if (isset($comments['html']) && !empty($comments['html'])) {
    if ($comments['aprobado'] == 1) {
      $checked = 'checked';
    }
    else {
      $checked = '';
    }
    }
    $html .= '<tr>';
    $html .= '<td>' . $value . '</td>';
    $html .= '<td><input type="checkbox" name="' . $name_item . '_aprobado" ' . $checked . '></td>';
    $html .= '<td> <textarea rows="3" cols="20" name="rq_administrative_' . $key . '_observaciones"></textarea>' . $comments['html'] . ' </td>';
    $html .= '</tr>';
  }
  $html .= '</table>';
  $form['rq_administrativos']['html'] = array(
    '#markup' => $html,
  );
  }*/
  $form['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Update'),
  );
  drupal_add_js(drupal_get_path('module', 'banrep_plan_carrera') . '/plan_carrera_validate.js');
  return $form;
}

function banrep_plan_carrera_form_submit($form,&$form_state){
  global $user;
  $values = $form_state['input'];
  if (isset($values['uid']) && !empty($values['uid']) && $values['uid'] > 0 && isset($values['rid'])){
    $log = _get_node_log($values['uid'],$values['rid']);
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
        if (drupal_mail('banrep_plan_carrera', 'plan_carrera', $to, language_default(), $params)){
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
  $comments = _get_log_by_rule($name_item,$nid_log);
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