<?php

function banrep_investigador_perfil_page($name) {
  if(!empty($name)){
      $user_load = user_load_by_name($name);
      if($user_load == FALSE){
          return drupal_not_found();
      }
      else{
        $uid = $user_load->uid;
      }
  }
  else{
      return drupal_not_found();
  }

  return theme('banrep_investigador_perfil', array('usuario' => $user_load));
}

function banrep_investigador_update_page($id = NULL, $filename = NULL){
  global $base_url;
  $url = $base_url . "/sites/default/files/migration/" . $filename;
  $request = drupal_http_request($url);
  $json_response = drupal_json_decode($request->data);
  dpm(count($json_response));
  $c=0;
  foreach ($json_response as $item) {
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->join('field_data_field_pub_type', 't', 'n.nid = t.entity_id');
    $query->condition('t.field_pub_type_value', $id, '=');
    $query->condition('n.type', 'publication');
    $query->condition('n.title', $item['titulo'], '=');
    $result = $query->execute()->fetchAll();
    foreach ($result as $nid) {
      $nids[] = $nid;
      $co_authors = array();
      $node = node_load($nid->nid);
      if($node->nid) $c++;
      if(!empty($item['autor_ppal'])){
        if($main_autor_tid = _banrep_obtener_tid_nombre(trim($item['autor_ppal']))){
          $node->field_main_author_reference[LANGUAGE_NONE][0]['tid'] = $main_autor_tid;
        }
        else {
          if($main_autor_tid = _banrep_buscar_autor_en_taxonomia(trim($item['autor_ppal']))){
            $node->field_main_author_reference[LANGUAGE_NONE][0]['tid'] = $main_autor_tid;
          }
          else {
            dpm('No hubo coincidencia con ' . $item['autor_ppal']);
          }
        }
      }
      if(!empty($item['coautor_1'])){
        if($coautor1_tid = _banrep_obtener_tid_nombre(trim($item['coautor_1']))){
          $co_authors[] = array('tid' => $coautor1_tid);
        }
        else {
          if($coautor1_tid = _banrep_buscar_autor_en_taxonomia(trim($item['coautor_1']))){
            $co_authors[] = array('tid' => $coautor1_tid);
          }
          else {
            dpm('No hubo coincidencia con ' . $item['coautor_1']);
          }
        }
      }
      if(!empty($item['coautor_2'])){
        if($coautor2_tid = _banrep_obtener_tid_nombre(trim($item['coautor_2']))){
          $co_authors[] = array('tid' => $coautor2_tid);
        }
        else {
          if($coautor2_tid = _banrep_buscar_autor_en_taxonomia(trim($item['coautor_2']))){
            $co_authors[] = array('tid' => $coautor2_tid);
          }
          else {
            dpm('No hubo coincidencia con ' . $item['coautor_2']);
          }
        }
      }
      if(!empty($item['coautor_3'])){
        if($coautor3_tid = _banrep_obtener_tid_nombre(trim($item['coautor_3']))){
          $co_authors[] = array('tid' => $coautor3_tid);
        }
        else {
          if($coautor3_tid = _banrep_buscar_autor_en_taxonomia(trim($item['coautor_3']))){
            $co_authors[] = array('tid' => $coautor3_tid);
          }
          else {
            dpm('No hubo coincidencia con ' . $item['coautor_3']);
          }
        }
      }
      if(!empty($item['coautor_4'])){
        if($coautor4_tid = _banrep_obtener_tid_nombre(trim($item['coautor_4']))){
          $co_authors[] = array('tid' => $coautor4_tid);
        }
        else {
          if($coautor4_tid = _banrep_buscar_autor_en_taxonomia(trim($item['coautor_4']))){
            $co_authors[] = array('tid' => $coautor4_tid);
          }
          else {
            dpm('No hubo coincidencia con ' . $item['coautor_4']);
          }
        }
      }
      if(!empty($item['coautor_5'])){
        if($coautor5_tid = _banrep_obtener_tid_nombre(trim($item['coautor_5']))){
          $co_authors[] = array('tid' => $coautor5_tid);
        }
        else {
          if($coautor5_tid = _banrep_buscar_autor_en_taxonomia(trim($item['coautor_5']))){
            $co_authors[] = array('tid' => $coautor5_tid);
          }
          else {
            dpm('No hubo coincidencia con ' . $item['coautor_5']);
          }
        }
      }
      $node->field_other_co_authors[LANGUAGE_NONE] = $co_authors;
      node_save($node);
    }
  }
  return $c . ' nodos actualizados';
}

/**
 * Consulta el nombre de un término.
 */
function _banrep_obtener_nombre_tid($tid) {
  return db_select('taxonomy_term_data', 't')
    ->fields('t', array('name'))
    ->condition('tid', $tid)
    ->execute()
    ->fetchField();
}

/**
 * Consulta el nombre de un término.
 */
function _banrep_obtener_tid_nombre($nombre) {
  return db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid'))
    ->condition('name', '%' . db_like($nombre) . '%', 'LIKE')
    ->execute()
    ->fetchField();
}


function _banrep_load_autores_by_json(){
  $url_autores = $base_url . "/sites/default/files/migration/autores.json";
  $autores = drupal_http_request($url_autores);
  $json_autores = drupal_json_decode($autores->data);
  dpm($json_autores);
  foreach ($json_autores as $row) {
    db_insert('banrep_autores')->fields($row)->execute();
  }
}

/**
 * Consulta el nombre de un término.
 */
function _banrep_obtener_uid_por_email($email) {
  return db_select('users', 'u')
    ->fields('u', array('uid'))
    ->condition('mail', '%' . db_like($email) . '%', 'LIKE')
    ->execute()
    ->fetchField();
}


function _banrep_buscar_autor_en_taxonomia($firma){
  $query = db_select('banrep_autores', 'a');
  $query->fields('a', array('correo', 'nombres', 'apellidos'));
  $query->condition('a.firma', $firma, '=');
  $query->range(0,1);
  $result = $query->execute()->fetchAll();
  foreach ($result as $autor) {
    if($autor->correo){
      $uid = _banrep_obtener_uid_por_email($autor->correo);
      if($uid){
        $query = db_select('taxonomy_term_data', 't');
        $query->join('field_data_field_user_reference', 'u', 't.tid = u.entity_id');
        $query->condition('u.field_user_reference_target_id', $uid, '=');
        $query->fields('t', array('tid'));
        $query->range(0,1);
        $main_autor_tid = $query->execute()->fetchField();
        if($main_autor_tid){
          return $main_autor_tid;
        }
      }
    }
  }
  return NULL;
}
