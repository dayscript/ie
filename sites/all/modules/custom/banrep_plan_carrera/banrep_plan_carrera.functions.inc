<?php

define('APROBADO', 3);


/**
 * @file
 * Defines banrep_core module functionality.
 */

/**
 * Funcion que cargar los requisitos de ascenso.
 */
function get_requirements($scale, $route, $uid, $type = '') {
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
      $requirements['general']      = get_general_requirements($node);
      $requirements['publications'] = get_publications_requirements($node->field_requisitos_publicaciones['und'], $uid);
      $requirements['time']         = get_time_requirements($node->field_requisitos_tiempo['und']);
      $requirements['training']     = get_training_requirements($node->field_req_formacion_desempeno['und']);
    }
    else {
      switch ($type) {
        case 'general':
        $requirements = get_general_requirements($node);
          break;
        case 'publications':
        
        $requirements = get_publications_requirements($node->field_requisitos_publicaciones['und'], $uid);
          break;
        case 'time':
        $requirements = get_time_requirements($node->field_requisitos_tiempo['und']);
          break;
        case 'training':
        $requirements = get_training_requirements($node->field_req_formacion_desempeno['und']);
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
function get_general_requirements($node) {
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
function get_time_requirements($items) {
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
function get_publications_requirements($items, $uid) {
  $data_list = [];
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
      $idCondition= '';

      switch ($type) {
        case 'CANTIDAD':
        case 'PUNTAJE':
          if (isset($rule->field_serie['und'][0]['target_id'])) {
            $requirements[$cont_group]['conditions'][$cont_condition]['serie'] = $rule->field_serie['und'][0]['target_id'];
          }
          $concept = array();
          foreach ($rule->field_concept_type['und'] as $taxonomy) {
            $concept[] = $taxonomy['tid'];
            $idCondition = $taxonomy['tid'];
          }

          $requirements[$cont_group]['conditions'][$cont_condition]['concept'] = implode(',', $concept);
          break;
      }
      $data_list = get_list_x_term($idCondition, $uid);
      $titles = ['Titulo', 'Fecha de aprobado', 'Puntos', 'Cargo Empleado', 'Tipo de publicación', 'ROL'];
      $requirements[$cont_group]['conditions'][$cont_condition]['operator']     = $rule->field_operador['und'][0]['value'];
      $requirements[$cont_group]['conditions'][$cont_condition]['type']         = $type;
      $requirements[$cont_group]['conditions'][$cont_condition]['value']        = $rule->field_cantidad_puntaje['und'][0]['value'];
      $requirements[$cont_group]['conditions'][$cont_condition]['html']         = get_table_list_view_more($data_list, 'Lista de Publicaciones' ,$titles);
      $requirements[$cont_group]['conditions'][$cont_condition]['concept_type'] = get_concept_type($rule);
      $cont_condition++;
    }
    $cont_group++;
  }

  return $requirements;
}

function get_list_x_term($idCondition, $uid){
  $resultList = [];
  $query = new EntityFieldQuery();
  $idType = _get_concept_id_publications($idCondition);
  // Traer todas las publicaciones activas por usuario y por tipo
  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'pub_user')
  ->fieldCondition('field_user_reference', 'target_id', $uid)
  ->fieldCondition('field_estado_publicaci_n', 'value', APROBADO);

  // $query->addTag('debug');
  $result = $query->execute();
  $nids = array_keys($result['node']);
  $data = node_load_multiple($nids);
  $lista_pub = [];

  foreach ($data as $key => $value) {
    $idK = $key;
    $idP = [$value->field_publicacion[LANGUAGE_NONE][0]['target_id']];
    $entity_publication = node_load('node', $idP);
    $type_id_node;
    $isPublication = FALSE;
    foreach ($entity_publication as $field => $val) {
        if ($field == 'field_pub_type') {
          if($val[LANGUAGE_NONE][0]['value'] == $idType){
            $type_id_node = $val[LANGUAGE_NONE][0]['value'];
            $tax = taxonomy_term_load($type_id_node);
            $lista_pub[$idK]['name_type_pub'] = $tax->name;
            $isPublication = TRUE;
          }
        }elseif ($field == 'field_role_within_publication') {
          $id_rol = $val[LANGUAGE_NONE][0]['tid'];
          $tax = taxonomy_term_load($id_rol);
          $lista_pub[$idK]['name_rol'] = $tax->name;
        }   
    }
    if($isPublication){
      foreach ($value as $key1 => $value1) {
        if($key1 == 'title'){
          $lista_pub[$idK]['title'] = $value1;
        }elseif ($key1 == 'revision_timestamp') {
          $lista_pub[$idK]['timestamp'] = date("d-m-Y", $value1);
        }elseif ($key1 == 'field_puntaje') {
          if($value->field_puntaje){
            $lista_pub[$idK]['score'] = $value1;
          }else {
            $lista_pub[$idK]['score'] = 0;
          }
        }elseif ($key1 == 'field_user_reference') {
          $idU = $value1[LANGUAGE_NONE][0]['target_id'];
          $entity_user = user_load($idU);
          $tax = taxonomy_term_load($entity_user->field_position[LANGUAGE_NONE][0]['tid']);
          $lista_pub[$idK]['position_user'] = $tax->name;
        }
      }

    }else{
      $lista_pub[$idK] = []; 
    }
  }
  
  // crear lista ordenada
  foreach ($lista_pub as $key3 => $value3) {
    if(count($value3) == 6){
      $resultList[$key3]['titulo'] = $value3['title'];
      $resultList[$key3]['fecha'] = $value3['timestamp'];
      $resultList[$key3]['puntos'] = $value3['score'];
      $resultList[$key3]['cargo'] = $value3['position_user'];
      $resultList[$key3]['tipo_pub'] = $value3['name_type_pub'];
      $resultList[$key3]['rol'] = $value3['name_rol'];
    }
  }
  return $resultList;
}

function get_table_list_view_more($list, $label, $titles){
  drupal_add_js(drupal_get_path('module', 'banrep_plan_carrera') .'/js/test.js');
  return theme('view-more', array(
    'list' => $list,
    'label' => $label,
    'titles' => $titles,
  ));
}

function get_concept_type($rule){
  $result = '-';
  if(isset($rule->field_concept_type[LANGUAGE_NONE][0]['tid'])){
    if($concept_type = taxonomy_term_load($rule->field_concept_type[LANGUAGE_NONE][0]['tid'])){
      if(isset($concept_type->field_puntajes[LANGUAGE_NONE][0]['value'])){
        if($puntajes = field_collection_item_load($concept_type->field_puntajes[LANGUAGE_NONE][0]['value'])){
          //Cargar la data
          if(isset($puntajes->field_acomula_en[LANGUAGE_NONE][0]['field_name'])){
            $result = get_name_acumulado($puntajes->field_acomula_en[LANGUAGE_NONE][0]['field_name']);
          }
        }
      }
    }
  }
  return $result;
}

/**
 * Funcion que carga los requisitos de formacion y desarrollo.
 */
function get_training_requirements($items) {
  $requirements = array();
  $cont = 0;
  foreach ($items as $item) {
    $rule = field_collection_item_load($item);
    $requirements[$cont]['operator'] = NULL;
    if ($cont > 0) {
      $requirements[$cont]['operator'] = 'O';
    }
    $cont_condition = 0;
    foreach ($rule->field_formacion_y_desarrollo[LANGUAGE_NONE] as $key => $value) {
      $requirements[$cont][$cont_condition] = $value['tid'];
      $cont_condition++;
    }
    $cont++;
  }
  return $requirements;
}

function get_name_acumulado($name_machine){
  $type = '-';
  switch ($name_machine) {
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
  return $type;
}

/**
 * Funcion que carga los conceptos de publicacion.
 */
function _get_concept_publications($tids) {
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
  return $name;

}

/**
 * Funcion que carga los ids de publicacion.
 */
function _get_concept_id_publications($tid) {
  $result = NULL;
  $term = taxonomy_get_parents($tid);

  if(empty(reset($term))) {
    $result = $tid;
  }else{
    $data = reset($term);
    if($data->tid){
      $result = $data->tid;
    }
  }
  return $result;
}

/**
 * Funcion que carga la experiencia del usuario.
 */
function _get_time_user($usuario, $type) {
  $experiencia = new stdClass();
  $experiencia->years = 0;
  switch ($type) {
    case 'A':
    case 'B':
      $experiencia = _get_experience($usuario->uid, 'field_date_admission');
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
      $experiencia = _get_experience($usuario->uid, 'field_date_last_score');
      break;

    case 'D':
      $experiencia = _get_experience($usuario->uid, 'field_fecha_penultimo_puntaje');
      break;

  }
  return $experiencia->years;
}

/**
 * Funcion que retorna la experiendcia del usuari que esta aplicando al ascenso.
 */
function _get_experience($uid, $field) {
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
function _get_publications_user($uid, $id_type_publication, $flag_is_node = FALSE, $type = 'CANTIDAD', $start_pub = 1, $is_activity = FALSE) {
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
      elseif ( $id_type_publication == 20708 ){
        $query->join('field_data_field_pub_type', 'c', 'c.entity_id = p.field_publicacion_target_id');
        $query->condition('c.field_pub_type_value', 20708, '=');
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
function _get_node_log($uid, $rid, $flag_return_node = TRUE) {
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
function _get_log_by_rule($rule, $nid) {
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


function _get_links_nodes($tid){

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
function _get_training_by_tid($uid,$tid) {
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

function update_redemption_date($uid){
  $user = user_load($uid);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'entityform')
    ->entityCondition('bundle', 'user_redemption')
    ->fieldCondition('field_aprobado', 'value', APROBADO)
    ->propertyCondition('uid', $uid)
    ->fieldOrderBy('field_act_date_end', 'value', 'DESC');
  
  $result = $query->execute();
  $nids = array_keys($result['entityform']);
  $data = entity_load('entityform',$nids); 

  $last_date = 0;
  foreach ($data as $key) {
    foreach ($key as $key2 => $value2) {
      if($key2 == 'field_act_date_end'){
        if($value2['und'][0]['value'] != NULL ){
          if($last_date == 0){
            $last_date = $value2['und'][0]['value'];
          } else {
            if($last_date < $value2['und'][0]['value']){
              $last_date = $value2['und'][0]['value'];
            }
          }
        }
      }
    }
  }

  //Guardar el campo de usuario 
  update_fields($user, $last_date, 'field_last_redemption_date');
}

function calculate_profile_data($uid, $date_update){

  //Cargar la data del usuario
  $user = user_load($uid);
  // Calcular puntaje acumulado General
  calculate_accumulated_general($user);

  // Calcular puntaje academico
  calculate_score_training($user);

  // Calcular puntaje BR
  
  // Fecha penultimo puntaje
  $last_date = $user->field_date_last_score['und'][0]['value'];
  // pasar esta fecha a la anterior
  update_fields($user, $last_date, 'field_fecha_penultimo_puntaje');

  // Fecha ultimo puntaje
  update_fields($user, $date_update, 'field_date_last_score');
}

function calculate_accumulated_general($user){
  // Trae la suma de puntos de publicaciones activas
  $value_all_publications = _get_all_publications_user_for_value($user->uid);
  //Guardar en el campo de usuario el valor 
  update_fields($user, $value_all_publications, 'field_acumulado_general');
}

function calculate_score_training($user){
  // La suma del valor actual con estado Aprobado
  $value_all_training = _get_score_training($user);

  //Guardar el campo de usuario 
  update_fields($user, $value_all_training, 'field_puntaje_acumulado');
}

function _get_score_BR(){
  // Obtener plan de carrera ruta

  // realizar las busquedas de la 
}

/**
 * Función que retorna el valor calculado del puntaje de toda las publicaciones aprobadas.
 */
function _get_all_publications_user_for_value($idUser) {
  $suma = 0;
  $query = new EntityFieldQuery();

  // Traer todas las publicaciones activas por usuario
  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'pub_user')
  ->fieldCondition('field_user_reference', 'target_id', $idUser)
  ->fieldCondition('field_estado_publicaci_n', 'value', APROBADO);

  // $query->addTag('debug');
  $result = $query->execute();
  $nids = array_keys($result['node']);
  $data = node_load_multiple($nids); 
  foreach ($data as $key) {
    foreach ($key as $key2 => $value2) {
      if($key2 == 'field_puntaje'){
        if($value2['und'][0]['value'] != NULL ){
          $puntaje = $value2['und'][0]['value'];
          // Realiza la suma de los puntos de las publicaciones
          $suma = $suma + $puntaje;
        }
      }
    }
  }
  return $suma;
}

/**
 * Función que retorna el valor calculado del puntaje del estudio realizados.
 */
function _get_score_training($user){
  $suma = 0.0;
  $idCarrie = $user->field_studies_carried_out['und'][0]['value'];
  $profile = field_collection_item_load($idCarrie);
  $idFormacion = $profile->field_req_formacion_desempeno['und'][0]['value'];
  $pdata2 = field_collection_item_load($idFormacion);
  $idTerm = $pdata2->field_formacion_y_desarrollo['und'][0]['tid'];
  $terms = taxonomy_term_load($idTerm);
  $query = new EntityFieldQuery();

  // Traer todos los estudios activas por usuario
  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'training')
  ->fieldCondition('field_concept_formation', 'tid', $terms->tid);

  $result = $query->execute();
  $nids = array_keys($result['node']);
  $data = node_load_multiple($nids); 

  foreach ($data as $key) {
    foreach ($key as $key2 => $value2) {
      if($key2 == 'field_puntaje' ){
        if($value2 != NULL){
          $puntaje = $value2['und'][0]['value'];
          $suma = $suma + $puntaje;
        }
      }
    }
  }
  return $suma;
}

function update_fields(&$user, $value_data, $field_name) {

  foreach ($user as $key => $value) {
    if($key == $field_name){
      $value['und'][0]['value'] = $value_data;
    }
    // user_save($user);
    field_attach_update('user', $user);
  }
  

}

function get_id_user_x_term($tid){
  $result = NULL;
  $term = taxonomy_term_load($tid);
  if($term){
    if(isset($term->field_user_reference['und'][0]['target_id'])){
      $result = $term->field_user_reference['und'][0]['target_id']; 
    }
  }
  return $result;
}