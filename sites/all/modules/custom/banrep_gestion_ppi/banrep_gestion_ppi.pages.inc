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
  $requirements = get_requirements_ppi($scale, $route, $usuario->uid);
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

  $perfil_active = (arg()[1]=='plan' && arg()[2]=='carrera') ? 'plan_carrera' : 'gestion_ppi';

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
  /*Requisito de tiempo*/
  if ($perfil_active == 'plan_carrera') {
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
          } else {
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
  }

  $user_ppi = user_load($uid->uid);

  /* Modificación sprint 2 feb 2020 "agregar despliegue descuento de puntos " */
    $discounts = views_embed_view('descuento_puntos', 'block', $user_ppi->uid);
    $form['position_discounts']['html'] = array(
	    '#markup' => "
	      <span class='h4'><b>Descuentos por cambio de cargo</b></span>
        <div class='registro'>
          <div class='row-container'>
		        $discounts
		      </div>
	    </div>"
    );
  /* Modificación sprint 2 feb 2020 "agregar despliegue descuento de puntos " */
  /*Requisito de tiempo*/
  /*Requisitos de publicaciones y/o actividades*/
  $form['rq_publiacion'] = array(
    '#type' => 'fieldset',
    '#title' => t('Requisitos de publicaciones y/o actividades'),
    '#tree' => TRUE,
  );
  $moduleRoot = drupal_get_path('module', 'banrep_gestion_ppi');
  $form['#attached']['css'][]= $moduleRoot.'/css/banrep_gestion_ppi.css';

  $req = [];
  foreach ($requirements['publications'] as $key => $reqpub) {
       foreach ($reqpub['conditions'] as $key => $value) {
        $req[] = $value['concept'];
      }
  }
  
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

      $date_pub = search_date_publication($node_child->field_log_puntaje['und']);
      if (isset($date_pub) && !empty($date_pub) && isset($date_query) && !empty($date_query) && $date_pub > $date_query) {
        $tax_father = $node_father->field_pub_type['und'][0]['value'];
        if (isset($node_father->field_co_authors['und'])) {
          foreach ($node_father->field_co_authors['und'] as $key => $entity_item) {
            $field_collection_id = $entity_item['value'];
            $field_collection = entity_load('field_collection_item', array($field_collection_id))[$field_collection_id];
            $co_autor = taxonomy_term_load($field_collection->field_co_autor['und'][0]['tid']);
            if (isset($co_autor) && $co_autor->field_user_reference['und'][0]['target_id'] == $user_ppi->uid) {
              if(!empty($field_collection->field_role_within_publicat['und'][0]['tid'])) {
                $tax_child = $field_collection->field_role_within_publicat['und'][0]['tid'];
              }else{
                $tax_child = $node_father->field_concept_type['und'][0]['tid'];
              }
            }
          }
        }
        
        if ($node_child->field_main_author['und'][0]['value'] == 1) {
          $role = taxonomy_term_load($node_father->field_role_within_publication['und'][0]['tid'])->name;
        }
        if ($node_child->field_main_author['und'][0]['value'] == 1 && isset($tax_child)) {
          $role = taxonomy_term_load($tax_child)->name;
        }
        if ($node_child->field_main_author['und'][0]['value'] == 0 && isset($tax_child)) {
          $role = taxonomy_term_load($tax_child)->name;
        }

        if($role === 'Autor') {
          $role = 'Coordinador capitulo ESPE';
        }

        $pos_father = _search_father_taxonomy_term($tax_father, $tax_child, $user_ppi->field_ruta[LANGUAGE_NONE][0]['target_id'], $req);
        
        foreach ($pos_father['values'] as $key) {
          $pub_user_type[$key]['acumula'] = $pos_father['acumula'];
          $pub_user_type[$key]['type'] = $node_father->field_pub_type[LANGUAGE_NONE][0]['value'];
          $pub_user_type[$key]['values'][] = array(
            'nid' => $node_child->nid,
            'title' => $node_father->title,
            'points' => $node_child->field_puntaje['und'][0]['value'],
            'date' => date( "d/m/Y", $date_pub),
            'type' => taxonomy_term_load($tax_father)->name,
            //'type' => taxonomy_term_load($pos_father['values'][0])->name,
            //'type_concept' => taxonomy_term_load($node_father->field_concept_type['und'][0]['tid'])->name,
            /* Modificación campo nuevo tipo de concepto */
            'type_concept' => isset($node_child->field_tipo_concepto) ? 
              taxonomy_term_load($node_child->field_tipo_concepto['und'][0]['tid'])->name :
              taxonomy_term_load($node_father->field_concept_type['und'][0]['tid'])->name,
            /* Modificación campo nuevo tipo de concepto */
            'charge' => $role,
            'escalafon' => taxonomy_term_load($node_child->field_usr_escalafon['und'][0]['tid'])->name,//taxonomy_term_load($user_ppi->field_usr_escalafon['und'][0]['tid'])->name
          );
          $pub_user_type[$key]['total_points'] += (isset($node_child->field_puntaje['und'][0]['value']) && !empty($node_child->field_puntaje['und'][0]['value'])) ? $node_child->field_puntaje['und'][0]['value'] : 0;
          $pub_user_type[$key]['count_pub'] = count($pub_user_type[$key]['values']);
        }
      }
    }
    
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'activity')
      ->propertyCondition('uid', $uid->uid)
      ->fieldCondition('field_act_wf_status', 'value', 20, '=');
    $result = $query->execute();
   
    $key = 211;
    $pos_father = _search_father_taxonomy_term($key, '', $user_ppi->field_ruta[LANGUAGE_NONE][0]['target_id'], $req);
    foreach ($result['node'] as $nid => $value) {
      $node = node_load($value->nid);
      $date_act = search_date_publication($node->field_log_puntaje['und']);
      if (!empty($date_act) && !empty($date_query) && $date_act > $date_query) {
        $pub_user_type[$key]['acumula'] = $pos_father['acumula'];
        $pub_user_type[$key]['type'] = $key;
        $pub_user_type[$key]['values'][] = array(
          'nid' => $node->nid,
          'title' => $node->title,
          'points' => $node->field_puntaje['und'][0]['value'],
          'date' => date( "d/m/Y", $date_act),
          'charge' => user_load($node->field_usuario['und'][0]['target_id'])->field_full_name['und'][0]['value'],
          'escalafon' => taxonomy_term_load($node_child->field_usr_escalafon['und'][0]['tid'])->name,//taxonomy_term_load($user_ppi->field_usr_escalafon['und'][0]['tid'])->name
        );
        $pub_user_type[$key]['total_points'] += (isset($node->field_puntaje['und'][0]['value']) && !empty($node->field_puntaje['und'][0]['value'])) ? $node->field_puntaje['und'][0]['value'] : 0;
        $pub_user_type[$key]['count_pub'] = count($pub_user_type[$key]['values']);
      }
    }
  }

  $html = '<table class="requirements__publications">';
  $has_points = false;
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
          } else {
            if (isset($condition['concept'])) {
              $concepts  = explode(',', $condition['concept']);
              $is_activity = FALSE;
              if (isset($condition['concept']) && $condition['concept'] == 211) {
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

          $puntaje_type_concept = ($condition['type'] == 'PUNTAJE') ? 
            $pub_user_type[$condition['concept']]['total_points'] : 
            $pub_user_type[$condition['concept']]['count_pub'];
          
          /* Modificación Consulta puntajes faltantes */
          if(empty($puntaje_type_concept)) {
            if ($condition['concept'] == '21236' || $condition['concept'] == '21237') {
              if ($name == $pub_user_type['20685']['values'][0]['charge']) {
                //var_dump($pub_user_type['20685']['total_points']);
                $puntaje_type_concept = $pub_user_type['20685']['total_points'];
                $has_points = true;
              }
            }
          }
          /* Modificación Consulta puntajes faltantes */
          //var_dump($puntaje_type_concept);
          $html .= '<td id="'.$condition['concept'].'">' . $operator . $name . ' (' . $condition['type'] . ')</td>';
          $html .= '<td>' . $condition['value'] . '</td>'; // falta para libros // valor requisito
          $html .= '<td>' . $puntaje_type_concept . '</td>'; // falta para libros //$info_user . $input_value
          break;
      }
      //capitulos_espe
      $calificacion = 'No cumple';
      $checked = '';
      if (!empty($puntaje_type_concept) && !empty($condition['value']) && $puntaje_type_concept >= $condition['value']) {
        $checked    = "checked";
        $calificacion = 'Cumple';
      }
      if (!empty($comments['html'])) {
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
      
      /*if ($keyc == 1 && $has_points) {
        $html .= "<a id='21236' class='pub_dropdown'>Listado de publicaciones</a>";
        $html .= '<div class="pub_dropdown_21236" style="display:none">'.
            //views_embed_view('capitulos_espe', 'block', $user_ppi->uid).
            drupal_render(_block_get_renderable_array(_block_render_blocks(array(block_load('views', 'capitulos_espe', $user_ppi->uid))))).
          '</div>';
      }*/
      
      //var_dump('Publicacion por concepto: '.$pub_user_type[$condition['concept']]);
      //var_dump('Concepto: '.$condition['concept']);
      //var_dump('Fecha publicación: '. date('Y-m-d', $date_pub) . ' > Fecha redención: '. date('Y-m-d', $date_query));
      /*var_dump($pub_user_type['20685']['values']);*/
      //var_dump($name);
      //var_dump($pub_user_type['20685']['values'][0]['charge'])
      if (isset($pub_user_type[$condition['concept']])) {
        switch ($condition['concept']) {
          case '201'://Articulo
          case '2951'://Doc trabajo
          case '15317'://Otros Doc
          case '21236':
          case '21237':
          case '20685':
            $sub_html = '<table id="table-'.$condition['concept'].'"class="table-list-pub">
              <tr> 
                <th class="text-left">Título</th>
                <th>Fecha Aprobación</th>
                <th>Puntos</th>
                <th>Cargo empleado</th>
                <th>Tipo Publicación</th>
                <th>Tipo Concepto</th>
              </tr>';
            break;
          case '211'://Actividades
            $sub_html = '<table id="table-'.$condition['concept'].'" class="table-list-pub">
              <tr>
                <th class="text-left">Título</th>
                <th>Fecha Aprobación</th>
                <th>Puntos</th>
                <th>Cargo empleado</th>
                <th>Aprobado por</th>
              </tr>';
            break;
          default:
            $sub_html = '<table id="table-'.$condition['concept'].'" class="table-list-pub">
              <tr>
                <th class="text-left">Título</th>
                <th>Fecha Aprobación</th>
                <th>Puntos</th>
                <th>Cargo empleado</th>
                <th>Tipo Publicación</th>
                <th>Rol</th>
              </tr>';
            break;
        }
        foreach ($pub_user_type[$condition['concept']]['values'] as $key => $value) {
          switch ($condition['concept']) {
            case '201'://Articulo
            case '15317'://Otros Doc
            $sub_html .= '<tr>
                <td id="'.$value['nid'].'" class="text-left">'.$value['title'].'</td>
                <td>'.$value['date'].'</td>
                <td>'.$value['points'].'</td>
                <td>'.$value['escalafon'].'</td>
                <td>'.$value['type'].'</td>
                <td>'.$value['type_concept'].'</td>
              </tr>';
              break;
            case '2951'://Doc trabajo
              $sub_html .= '<tr>
                  <td id="'.$value['nid'].'" class="text-left">'.$value['title'].'</td>
                  <td>'.$value['date'].'</td>
                  <td>'.$value['points'].'</td>
                  <td>'.$value['escalafon'].'</td>
                  <td>'.$value['type_concept'].'</td>
                </tr>';
              break;
            case '211'://Actividades
              $sub_html .= '<tr>
                  <td id="'.$value['nid'].'" class="text-left">'.$value['title'].'</td>
                  <td>'.$value['date'].'</td>
                  <td>'.$value['points'].'</td>
                  <td>'.$value['escalafon'].'</td>
                  <td>'.$value['type_concept'].'</td>
                  <td>'.$value['charge'].'</td>
                </tr>';
              break;
            default:
              $sub_html .= '<tr>
                  <td id="'.$value['nid'].'" class="text-left">'.$value['title'].'</td>
                  <td>'.$value['date'].'</td>
                  <td>'.$value['points'].'</td>
                  <td>'.$value['escalafon'].'</td>
                  <td>'.$value['type'].'</td>
                  <td>'.$value['type_concept'].'</td>
                  
                </tr>';
              break;
          }
        }
        $sub_html .= '</table>';
        $list = ($condition['concept']==211) ? 'Listado de Actividades': 'Listado de publicaciones';
        $html .= '
          <tr>
            <td colspan="7">
              <a id="'.$condition['concept'].'" class="pub_dropdown">'.$list.'</a>
              <div class="pub_dropdown_'.$condition['concept'].'" style="display: none;">'.$sub_html.'</div>
            </td>
          </tr>';
      //} elseif($keyc == 1 && ($condition['concept'] == '21236' || $condition['concept'] == '21237')) {
      } elseif($name == $pub_user_type['20685']['values'][0]['charge'] && ($condition['concept'] == '21236' || $condition['concept'] == '21237')) {
      //} elseif(($condition['concept'] == '21236' && strpos($name, 'Contribuyente') > 0) || ($condition['concept'] == '21237' && (strpos($name, 'Autor') > 0) || strpos($name, 'Coordinador') > 0)) {
        $sub_html = '<table id="table-'.$condition['concept'].'"class="table-list-pub"><tr><th class="text-left">Título</th><th>Fecha Aprobación</th><th>Puntos</th><th>Cargo empleado</th><th>Tipo Publicación</th></tr>';
        
        foreach($pub_user_type['20685']['values'] AS $key => $value) {
          $sub_html .= '<tr><td id="'.$value['nid'].'" class="text-left">'.$value['title'].'</td><td>'.$value['date'].'</td><td>'.$value['points'].'</td><td>'.$value['escalafon'].'</td><td>'.$value['type'].'-'.$value['type_concept'].'</td></tr>';
        }

        $sub_html .= '</table>';
        $html .= '
          <tr>
            <td colspan="7">
              <a id="'.$condition['concept'].'" class="pub_dropdown">Listado de publicaciones</a>
              <div class="pub_dropdown_'.$condition['concept'].'" style="display: none;">'.$sub_html.'</div>
            </td>
          </tr>';
      } else {
        //var_dump($pub_user_type['20685']);
        //var_dump($name);
        //var_dump($pub_user_type['20685']['values'][0]['charge']);
        /*if($name == $pub_user_type['20685']['values'][0]['charge'] && ($condition['concept'] == '21236' || $condition['concept'] == '21237')) {
          var_dump($pub_user_type['20685']['values'][0]['charge']);
        }*/
      }
    }
    $html .= '</table></td></tr>';
  }
  $html .= '</table>';

  $form['rq_publiacion']['html'] = array(
    '#markup' => $html,
  );
  /*Requisitos de publicaciones y/o actividades*/
  /*Requisitos formación desarrollo y desempeño*/
    if ($perfil_active == 'plan_carrera') {
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
        if (count($files[$group[0]]) > 0 ) {
          $info_user = TRUE;
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
          } else {
            $checked = '';
          }
        }

        $info_user_count = !empty($files[$group[0]]) ? count($files[$group[0]]) : '';
        
        $html .= '<tr>';
        $html .= '<td>'. $group['operator'] .'</td>';
        $html .= '<td id="'.$group[0].'">'. $name .'</td>';
        $html .= '<td>'.$info_user.'</td>';
        $html .= '<td>'.$info_user_count.'</td>';
        $html .= '<td>'. $calificacion .'</td>';
        $html .= '<td><input type="checkbox" name="rq_formacion_' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
        $html .= '<td> <textarea rows="3" cols="20" name="rq_formacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . '</td>';
        $html .= '</tr>';

        if (count($files[$group[0]]) > 0) {
          $strFiles = '<table class="table-list-pub"><tr><th></th><th>Título</th><th>Año</th></tr><tbody>';
          foreach ($files[$group[0]] as $key => $item) {
            $title_fd = !empty($item['title']) ? $item['title'] : $item['description'];
            $strFiles .= '<tr><td></td><td>'. $title_fd .'</td><td>'. $item['year'].'</td></tr>';
          }
          $strFiles .= '</tbody></table>';

          $html .= '
          <tr>
            <td colspan="7">
              <a id="'.$condition['concept'].'" class="pub_dropdown">Listado de requisitos</a>
              <div class="pub_dropdown_'.$condition['concept'].'" style="display: none;">'.$strFiles.'</div>
            </td>
          </tr>';
        }
      }
      $html .= '</tbody>';


      $html .= '</table>';
      $html .= '</table>';
      $form['rq_formacion']['html'] = array(
      '#markup' => $html,
      );
  }
  /*Requisitos formación desarrollo y desempeño*/
  /*Requisitos puntaje acumulado*/ 
  $html = '<table class="requirements__publications">';

  $form['rq_puntaje_acumulado'] = array(
    '#type' => 'fieldset',
    '#title' => t('Requisitos puntaje acumulado'),
    '#tree' => TRUE,
  );

  $html .= '<tr><td colspan="6">';
  $html .= '<table class="requirements__publications">';
    $html .= '<tr>';
    $html .= '<th>Nombre requisito</th>';
    $html .= '<th>Valor requisito</th>';
    $html .= '<th>Valor actual</th>';
    $html .= '<th>Calificación</th>';
    $html .= '<th>Aprobación</th>';
    $html .= '<th>Observaciones</th>';
    $html .= '</tr>';
    $html .= '<tbody>';
    foreach ($requirements['accumulated'] AS $keyg => $group) {
      $keyc = 0;
      $name_item = 'rq_formacion_' . $keyg . '_' . $keyc;
      $comments = _output_comments($name_item, $nid_log);

      if (isset($group['val_requisito']) && !empty($group['val_requisito']) && $group['val_requisito'] > 0 && $group['aprobado']) {
        $checked = 'checked';
      } else {
        $checked = '';
      }
      
      $html .= '<tr>';
        $html .= '<td>'. $group['name'] .'</td>';
        $html .= '<td>'. $group['val_requisito'] .'</td>';
        $html .= '<td>'. $group['val_user'] .'</td>';
        $html .= '<td>'. $group['calificacion'] .'</td>';
        $html .= '<td><input type="checkbox" name="rq_ac_acumulado' . $keyg . '_' . $keyc . '_aprobado" ' . $checked . '></td>';
        $html .= '<td> <textarea rows="3" cols="20" name="rq_formacion_' . $keyg . '_' . $keyc . '_observaciones"></textarea>' . $comments['html'] . '</td>';
      $html .= '</tr>';
    }
    $html .= '</tbody>';

  
  $html .= '</table>';
  $html .= '</table>';
  $form['rq_puntaje_acumulado']['html'] = array(
  '#markup' => $html,
  );
  /*Requisitos puntaje acumulado*/

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

function _search_father_taxonomy_term($tfather, $tchild, $uruta, $req){
  $name = 'categorias_de_conceptos';
  $voc = taxonomy_vocabulary_machine_name_load($name);
  $tree = taxonomy_get_tree($voc->vid);
  $terms = [];

  foreach ($tree as $term) {  
    switch ($term->depth) {
      case 0:
        $father = $term->tid;
        $terms[$father] = array('tid' => $term->tid, 'name' => $term->name);
        break;
      case 1:
        $child = $term->tid;
        
        $type = load_acumula_points($child, $uruta);
        $terms[$father]['acumula'] = ($type!=='') ? $type : $terms[$father]['acumula'];
        $terms[$father]['childs'][$child] = array('tid' => $term->tid, 'name' => $term->name, 'acumula' => $type);
        
        break;
      case 2:
        $childs = $term->tid;
        $type = load_acumula_points($childs, $uruta);
        $terms[$father]['acumula'] = ($type!=='') ? $type : $terms[$father]['acumula'];
        $terms[$father]['childs'][$child]['childs'][$childs] = array('tid' => $term->tid, 'name' => $term->name, 'acumula' => $type);
        break;
    }
  }
  
  $terms['21204']['childs'][$child] = $terms['206']['childs'][$child];
  $tfather = ($tfather==1) ? 21204 : $tfather;//Ajuste para ID de Capítulos de libro
  $find = array('acumula' => $terms[$tfather]['acumula'], 'values' => array($tfather));
  foreach ($terms[$tfather]['childs'] as $terms_) {
    if(in_array($tfather, $req) && in_array($tchild, $req) && $terms_['tid'] == $tchild){
      $find = array('acumula' => $terms[$tfather]['acumula'], 'values' => array($tchild));
    }
    foreach ($terms_['childs'] as $term_) {
      if(in_array($tfather, $req) && in_array($tchild, $req) && $terms_['tid'] == $tchild){
        $find = array('acumula' => $terms[$tfather]['acumula'], 'values' => array($tchild));
      }
    }
  }
  return $find;
}

function load_acumula_points($tuid, $uruta) {
  $type = '';
  $e = taxonomy_term_load($tuid);
  foreach ($e->field_puntajes[LANGUAGE_NONE] as $field_puntaje) {
    $field_collection_item_value = $field_puntaje['value']; 
    $field_collection_value = entity_load('field_collection_item', array($field_collection_item_value));
    if ($uruta == $field_collection_value[key($field_collection_value)]->field_ruta[LANGUAGE_NONE][0]['target_id']) {
      switch ($field_collection_value[key($field_collection_value)]->field_acumula_en[LANGUAGE_NONE][0]['field_name']) {
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
    }
  }
  return $type;
}

function search_date_publication($log) {
  $date = '';
  if (isset($log)) {
    $date_endl = end($log)['value'];
    $date_l = explode(' ', $date_endl);
    $date_fl = explode('/', $date_l[0]);
    $date_t = $date_fl[1].'/'.$date_fl[0].'/'.$date_fl[2];//Cambio de día x mes
    $date = strtotime($date_t);
  }
  
  return $date;
}
