<?php

/**
 * @file
 * Defines banrep_core module functionality.
 */

/**
 * Funcion que cargar los requisitos de ascenso.
 */
function get_requirements_ppi($scale, $route, $uid, $type = '') {
  $query = db_select('field_data_field_ruta_plan_carrera', 'r');
  $query->addField('r', 'entity_id', 'nid');
  $query->join('field_data_field_escalafon_actual', 's', 's.entity_id = r.entity_id');
  $query->condition('r.field_ruta_plan_carrera_tid', $route, '=');
  $query->condition('s.field_escalafon_actual_tid', $scale, '=');
  $result = $query->execute()->fetchObject();
  if (isset($result->nid) && is_numeric($result->nid) && $result->nid > 0) {
    $node                         = node_load($result->nid);
    $requirements                 = array();
    if (empty($type)) {
      $requirements['nid']          = $result->nid;
      $requirements['general']      = get_general_requirements_ppi($node);
      $requirements['publications'] = get_publications_requirements_ppi($node->field_requisitos_publicaciones['und']);
      $requirements['time']         = get_time_requirements_ppi($node->field_requisitos_tiempo['und']);
      $requirements['training']     = get_training_requirements_ppi($node->field_req_formacion_desempeno['und']);
      $requirements['accumulated']     = get_accumulated_requirements_ppi($node, $uid);
      $requirements['publications_req'] = $node->field_date_start_pub['und'][0]['value'];
    }
    else {
      switch ($type) {
        case 'general':
        $requirements = get_general_requirements_ppi($node);
          break;
        case 'publications':
        $requirements = get_publications_requirements_ppi($node->field_requisitos_publicaciones['und']);
          break;
        case 'time':
        $requirements = get_time_requirements_ppi($node->field_requisitos_tiempo['und']);
          break;
        case 'training':
        $requirements = get_training_requirements_ppi($node->field_req_formacion_desempeno['und']);
          break;
        case 'accumulated':
          $requirements = get_accumulated_requirements_ppi($node, $uid);
          break;
      }
    }
    return $requirements;
  }
  else {
    return FALSE;
  }
}

/**
 * Funcion que carga los campos generales de la tabla de requisitos.
 */
function get_general_requirements_ppi($node) {
  $general = array();
  $general['date_start_pub'] = 1;
  $general['lugar_posgrado'] = NULL;
  if (isset($node->field_date_start_pub['und'][0]['value'])) {
    $general['date_start_pub'] = $node->field_date_start_pub['und'][0]['value'];
  }

  if (isset($node->field_lugar_posgrado['und'][0]['value'])) {
    $general['lugar_posgrado'] = $node->field_lugar_posgrado['und'][0]['value'];
  }
  return $general;
}

/**
 * Funcion que cargar el fieldcollection de requerimientos de tiempo.
 */
function get_time_requirements_ppi($items) {
  $requirements = array();
  foreach ($items as $item) {
    $rule = field_collection_item_load($item['value']);
    $requirements[$rule->field_pcr_tipo_tiempo['und'][0]['value']] = $rule->field_pcr_tiempo['und'][0]['value'];
  }
  return $requirements;
}

/**
 * Funcion que carga los requirimientos de publicaciones.
 */
function get_publications_requirements_ppi($items) {
  $requirements = array();
  $cont_group = 0;
  foreach ($items as $group) {
    $item = field_collection_item_load($group['value']);
    $operator_g = isset($item->field_operador['und'][0]['value']) ? $item->field_operador['und'][0]['value'] : '';
    $conditions = $item->field_condicion['und'];
    $cont_condition = 0;
    $requirements[$cont_group]['operator'] = $operator_g;
    foreach ($conditions as $condition) {
      $rule = field_collection_item_load($condition['value']);
      $type = $rule->field_tipo_requisito['und'][0]['value'];
      switch ($type) {
        case 'CANTIDAD':
        case 'PUNTAJE':
          if (isset($rule->field_serie['und'][0]['target_id'])) {
            $requirements[$cont_group]['conditions'][$cont_condition]['serie'] = $rule->field_serie['und'][0]['target_id'];
          }
          $concept = array();
          foreach ($rule->field_concept_type['und'] as $taxonomy) {
            $concept[] = $taxonomy['tid'];
          }
          $requirements[$cont_group]['conditions'][$cont_condition]['concept'] = implode(',', $concept);
          break;
      }
      $requirements[$cont_group]['conditions'][$cont_condition]['operator'] = $rule->field_operador['und'][0]['value'];
      $requirements[$cont_group]['conditions'][$cont_condition]['type']     = $type;
      $requirements[$cont_group]['conditions'][$cont_condition]['value']    = $rule->field_cantidad_puntaje['und'][0]['value'];
      $cont_condition++;
    }
    $cont_group++;
  }

  return $requirements;
}

/**
 * Funcion que carga los requisitos de formacion y desarrollo.
 */
function get_training_requirements_ppi($items) {
  $requirements = array();
  $cont = 0;
  foreach ($items as $item) {
    $rule = field_collection_item_load($item);
    $requirements[$cont]['operator'] = NULL;
    if ($cont > 0) {
      $requirements[$cont]['operator'] = 'O';
    }
    $cont_condition = 0;
    foreach ($rule->field_formacion_y_desarrollo['und'] as $key => $value) {
      $requirements[$cont][$cont_condition] = $value['tid'];
      $cont_condition++;
    }
    $cont++;
  }
  return $requirements;
}

/**
 * Funcion que carga los conceptos de publicacion.
 */
function _get_concept_publications_ppi($tids) {
  $tids = explode(',', $tids);
  $terms = taxonomy_term_load_multiple($tids);
  $name = '';
  foreach ($terms as $key => $term) {
    if (!empty($name)) {
      $name .= ' - ' . $term->name;
    }
    else {
      $name = $term->name;
    }
  }

  // echo "<pre>";
  // print_r( $name );
  // echo "</pre>";

  return $name;

}

/**
 * Funcion que carga la experiencia del usuario.
 */
function _get_time_user_ppi($usuario, $type) {
  $experiencia = new stdClass();
  $experiencia->years = 0;
  switch ($type) {
    case 'A':
    case 'B':
      $experiencia = _get_experience_ppi($usuario->uid, 'field_date_admission');
      if ($type == 'B') {
        foreach ($usuario->field_studies_carried_out['und'] as $value) {
          $rule = field_collection_item_load($value['value']);
          $query = db_select('field_data_field_fecha_inicio_estudio', 'fi');
          $query->addField('fi', 'field_fecha_inicio_estudio_value', 'fecha_inicio');
          $query->addField('ff', 'field_fecha_fin_estudio_value', 'fecha_fin');
          $query->addExpression('TIMESTAMPDIFF(YEAR,FROM_UNIXTIME(fi.field_fecha_inicio_estudio_value),FROM_UNIXTIME(ff.field_fecha_fin_estudio_value))', 'years');
          $query->join('field_data_field_fecha_fin_estudio', 'ff', 'ff.entity_id = fi.entity_id');
          $query->join('field_data_field_lugar_posgrado', 'l', 'l.entity_id = fi.entity_id');
          $query->condition('ff.entity_id', $value['value'], '=');
          $query->condition('l.field_lugar_posgrado_value', 'EXTERIOR', '=');
          $query->condition('fi.field_fecha_inicio_estudio_value', $experiencia->date, '>=');
          $result = $query->execute()->fetchObject();
          if (isset($result->years) && !is_null($result->years)) {
            $experiencia->years = $experiencia->years - $result->years;
          }
        }
      }
      break;

    case 'C':
      $experiencia = _get_experience_ppi($usuario->uid, 'field_date_last_score');
      break;

    case 'D':
      $experiencia = _get_experience_ppi($usuario->uid, 'field_fecha_penultimo_puntaje');
      break;

  }
  return $experiencia->years;
}

/**
 * Funcion que retorna la experiendcia del usuari que esta aplicando al ascenso.
 */
function _get_experience_ppi($uid, $field) {
  $experiencia = 0;
  $query = db_select('field_data_' . $field, 'e');
  $query->addField('e', $field . '_value', 'date');
  $query->addExpression('TIMESTAMPDIFF(YEAR,FROM_UNIXTIME(' . $field . '_value),FROM_UNIXTIME(UNIX_TIMESTAMP(now())))', 'years');
  $query->condition('e.entity_id', $uid, '=');
  $result = $query->execute()->fetchObject();
  if (isset($result->years) && !is_null($result->years)) {
    $experiencia = $result;
  }

  return $experiencia;
}

/**
 * Función que calcula el puntaje o la cantidad de publicaciones del usuario.
 */
function _get_publications_user_ppi($uid, $id_type_publication, $flag_is_node = FALSE, $type = 'CANTIDAD', $start_pub = 1, $is_activity = FALSE) {
  $star_date = NULL;
  if ($start_pub > 1) {
    $usuario = user_load($uid);
    switch ($start_pub) {
      case 2:
        if (isset($usuario->field_fecha_penultimo_puntaje['und'][0]['value']) && !empty($usuario->field_fecha_penultimo_puntaje['und'][0]['value'])) {
          $start_date = $usuario->field_date_last_score['und'][0]['value'];
        }
        break;

      case 3:
        if (isset($usuario->field_date_last_score['und'][0]['value']) && !empty($usuario->field_date_last_score['und'][0]['value'])) {
          $start_date = $usuario->field_date_last_score['und'][0]['value'];
        }
        break;
    }
  }

  if ($is_activity) {
    $query = db_select('node', 'n');
    $query->join('field_data_field_act_wf_status', 'e', 'e.entity_id = n.nid');
    $query->join('field_data_field_concept_category', 'c', 'c.entity_id = n.nid');
    $query->condition('c.field_concept_category_tid', $id_type_publication, '=');
    $query->condition('n.type', 'activity', '=');
    $query->condition('e.field_act_wf_status_value', 20, '=');
    $query->condition('n.uid', $uid, '=');
  }
  else {
    if ($flag_is_node) {
     
      $query = db_select('node', 'n');
      $query->join('field_data_field_user_reference', 'u', 'u.entity_id = n.nid');
      $query->join('field_data_field_publicacion', 'p', 'p.entity_id = n.nid');
      $query->join('field_data_field_concept', 'c', 'c.entity_id = p.field_publicacion_target_id');
      $query->join('field_data_field_estado_publicaci_n', 'ep', 'ep.entity_id = n.nid');
      $query->condition('c.field_concept_target_id', $id_type_publication, '=');
      $query->condition('n.type', 'pub_user', '=');
      $query->condition('ep.field_estado_publicaci_n_value', 3, '=');
      $query->condition('u.field_user_reference_target_id', $uid, '=');
    }else {

      $query = db_select('node', 'n');
      $query->join('field_data_field_user_reference', 'u', 'u.entity_id = n.nid');
      $query->join('field_data_field_publicacion', 'p', 'p.entity_id = n.nid');
      $query->join('field_data_field_estado_publicaci_n', 'ep', 'ep.entity_id = n.nid');
      // if ($id_type_publication == 15348) {
      if ($id_type_publication == 20697) {
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 201, '=');
      }
      // elseif ($id_type_publication == 15349) {
      elseif ( $id_type_publication == 206  ) {
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 206, '=');
      }
      elseif ( $id_type_publication == 15317 ){
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 15317, '=');
      }
      elseif ( $id_type_publication == 20704 ){
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 20704, '=');
      }
      elseif ( $id_type_publication == 20662 ){
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 20662, '=');
      }
      elseif ( $id_type_publication == 20723 ){
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 20723, '=');
      }
      else {
        $query->join('field_data_field_concept_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_concept_type_tid', $id_type_publication, '=');
      }

      $query->condition('ep.field_estado_publicaci_n_value', 3, '=');
      $query->condition('n.type', 'pub_user', '=');
      $query->condition('u.field_user_reference_target_id', $uid, '=');
    }
  }
  

  if (!is_null($start_date)) {
    $query->condition('n.created', $start_date, '>=');
  }

  switch ($type) {
    case 'CANTIDAD':
      $query->addField('n', 'nid', 'nid');
      $num_of_result = $query->execute()->rowCount();
      break;

    case 'PUNTAJE':
      $query->leftJoin('field_data_field_puntaje', 'j', 'j.entity_id = n.nid');
      $query->addField('j', 'field_puntaje_value', 'puntaje');
      if ($is_activity) { 
      }
      else {
        $query->leftJoin('field_data_field_puntaje_usado', 'ju', 'ju.entity_id = n.nid');
        $query->addExpression('SUM(COALESCE(j.field_puntaje_value,0) - COALESCE(ju.field_puntaje_usado_value,0))', 'puntaje');                
      }
      $result = $query->execute()->fetchObject();
      
      if (isset($result->puntaje) && !is_null($result->puntaje)) {
        $num_of_result = $result->puntaje;
      }
      break;
  }
  return $num_of_result;
}

/**
 * Funcion que carga el nodo log de ascenso.
 */
function _get_node_log_ppi($uid, $rid, $flag_return_node = TRUE) {
  $query = db_select('node', 'n');
  $query->addField('n', 'nid', 'nid');
  $query->join('field_data_field_usuario', 'u', 'u.entity_id = n.nid');
  $query->join('field_data_field_requisito', 'r', 'r.entity_id = n.nid');
  $query->condition('r.field_requisito_target_id', $rid, '=');
  $query->condition('u.field_usuario_target_id', $uid, '=');
  $result = $query->execute()->fetchObject();
  if (isset($result->nid) && !is_null($result->nid)) {
    if ($flag_return_node) {
      $node_log = node_load($result->nid);
    }
    else {
      $node_log = $result->nid;
    }
    return $node_log;
  }
  else {
    if ($flag_return_node) {
      $usuario    = user_load($uid);
      $log        = new stdClass();
      $log->title = 'Actualización requisitos ascenso ' . $usuario->name . ' ' . $rid;
      $log->type  = 'log_ascenso';
      node_object_prepare($log);
      $log->field_usuario['und'][0]['target_id'] = $uid;
      $log->field_requisito['und'][0]['target_id'] = $rid;
      node_save($log);
    }
    else {
      $log = NULL;
    }
    return $log;
  }
}

/**
 * Funcion que carga las reglas del log.
 */
function _get_log_by_rule_ppi($rule, $nid) {
  $items = db_select('field_data_field_reglas', 'i');
  $items->fields('i', array('field_reglas_value'));
  $items->condition('i.entity_id', $nid, '=');

  $query = db_select('field_data_field_id', 'v');
  $query->fields('v', array('entity_id'));
  $query->condition('v.field_id_value', $rule, '=');
  $query->condition('v.entity_id', $items, 'IN');
  $query->orderBy('v.entity_id', 'DESC');
  $result = $query->execute()->fetchALL();
  return $result;
}


function _get_links_nodes_ppi($tid){

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'activity')
        ->fieldCondition('field_concept_formation', 'tid', $tid);
  $result = $query->execute();
  $nids = array_keys($result['node']);
  $nodes = entity_load('node', $nids);
  $arfiles = array();
  foreach($nodes as $node)
  {
    if(!empty($node->field_re_attach_doc)){
       $arfiles[] = array(
         'url' => file_create_url($node->field_re_attach_doc[LANGUAGE_NONE][0]['uri']),
         'name' =>  $node->field_re_attach_doc[LANGUAGE_NONE][0]['origname'],
     );
    }
  }

  if(!empty($arfiles))
  {
    $strFiles = "<br/><ul>";
  foreach($arfiles as $arfile)
  {
    $strFiles .= "<li><a href='".$arfile['url']."' target='_blank'>".$arfile['name']."</a></li>";
  }
  $strFiles .= "</ul>";

  }

  return $strFiles;

}

/**
 * Funcion que carga los nodos de tipo formacion del usuario por concepto.
 */
function _get_training_by_tid_ppi($uid,$tid) {
  $files = array();
  if (is_numeric($tid) && $tid > 0) {
    $query = db_select('node', 'n');
    $query->addField('n', 'nid', 'nid');
    $query->addField('f', 'field_re_attach_doc_fid', 'fid');
    $query->join('field_data_field_concept_formation', 'c', 'c.entity_id = n.nid');
    $query->join('field_data_field_re_attach_doc', 'f', 'f.entity_id = n.nid');
    $query->condition('n.type', 'training');
    $query->condition('n.uid', $uid);
    $query->condition('c.field_concept_formation_tid', $tid);
    $result = $query->execute()->fetchAll();
    foreach ($result as $row) {
      if (isset($row->nid) &&  !is_null($row->nid) && is_numeric($row->nid) && $row->nid > 0) {
        $file = file_load($row->fid);
        $url = file_create_url($file->uri);
        $files[] = array('url' => $url, 'name' => $file->origname);
      }
    }
  }

  return $files;

}

function get_accumulated_requirements_ppi($node , $uid) {

  $requirements = array();
  $user = user_load($uid);

  $cont = 0;
  // Puntaje del requerimiento
  $puntaje_acumulado = isset($node->field_puntaje_acumulado['und'])? $node->field_puntaje_acumulado['und'][0]['value'] : 0;
  $puntaje_br = isset($node->field_puntaje_br['und'])? $node->field_puntaje_br['und'][0]['value'] : 0;
  $puntaje_gen = isset($node->field_acumulado_general['und'])? $node->field_acumulado_general['und'][0]['value'] : 0;

  // Puntaje de usuario
  $user_punt_acum = isset($user->field_puntaje_acumulado['und'])? $user->field_puntaje_acumulado['und'][0]['value'] : 0;
  $user_punt_br = isset($user->field_puntaje_br['und'])? $user->field_puntaje_br['und'][0]['value'] : 0;
  $user_punt_gen = isset($user->field_acumulado_general['und'])? $user->field_acumulado_general['und'][0]['value'] : 0;


  //Calificación
  $cal_punt_acum = evalu_acumulate($puntaje_acumulado, $user_punt_acum) ? 'Cumple' : 'No Cumple';
  $cal_punt_br = evalu_acumulate($puntaje_br, $user_punt_br) ? 'Cumple' : 'No Cumple';
  $cal_punt_gen = evalu_acumulate($puntaje_gen, $user_punt_gen) ? 'Cumple' : 'No Cumple';

  //Aprobacion
  $aprob_punt_acum = evalu_acumulate($puntaje_acumulado, $user_punt_acum);
  $aprob_punt_br = evalu_acumulate($puntaje_br, $user_punt_br);
  $aprob_punt_gen = evalu_acumulate($puntaje_gen, $user_punt_gen);

  $requirements['academico']['name'] = 'Acumulado Academico';
  $requirements['academico']['val_requisito'] = $puntaje_acumulado;
  $requirements['academico']['val_user'] = $user_punt_acum;
  $requirements['academico']['calificacion'] = $cal_punt_acum;
  $requirements['academico']['aprobado'] = $aprob_punt_acum;

  $requirements['br']['name'] = 'Acumulado BR';
  $requirements['br']['val_requisito'] = $puntaje_br;
  $requirements['br']['val_user'] = $user_punt_br;
  $requirements['br']['calificacion'] = $cal_punt_br;
  $requirements['br']['aprobado'] = $aprob_punt_br;

  $requirements['gnral']['name'] = 'Acumulado General';
  $requirements['gnral']['val_requisito'] = $puntaje_gen;
  $requirements['gnral']['val_user'] = $user_punt_gen;
  $requirements['gnral']['calificacion'] = $cal_punt_gen;
  $requirements['gnral']['aprobado'] = $aprob_punt_gen;

  return $requirements;
}