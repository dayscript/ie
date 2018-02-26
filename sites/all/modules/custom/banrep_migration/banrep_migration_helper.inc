<?php

/**
 * @file
 * Funciones de ayuda para las migraciones.
 */

define('SEMINARIOS_TID', '191');

/**
 * Obtener categoria segun el tipo.
 */
function _get_concept_category($type){
	switch ($type) {
		case 'Tipo 1':
			$tids[] = array('tid' => 201);
			$tids[] = array('tid' => 202);
			return $tids;
			break;
		case 'Tipo 2':
			$tids[] = array('tid' => 201);
			$tids[] = array('tid' => 203);
			return $tids;
			break;
		case 'Tipo 3':
			$tids[] = array('tid' => 201);
			$tids[] = array('tid' => 204);
			return $tids;
			break;
		case 'Tipo 4':
			$tids[] = array('tid' => 201);
			$tids[] = array('tid' => 205);
			return $tids;
			break;
		case 'A':
			$tids[] = array('tid' => 206);
			$tids[] = array('tid' => 207);
			return $tids;
			break;
		case 'B':
			$tids[] = array('tid' => 206);
			$tids[] = array('tid' => 208);
			return $tids;
			break;
		case 'C':
			$tids[] = array('tid' => 206);
			$tids[] = array('tid' => 209);
			return $tids;
			break;
		default:
			# code...
			break;
	}
}

/**
 * Obtener nid de un vinculo.
 */
function _get_index_nid ($title){
  $result = db_select('node', 'n')
  ->fields('n',array('nid'))
  ->condition('type', 'vinculo')
  ->condition('title', '%'.db_like($title), 'LIKE')
  ->range(0,1)
   ->execute()
  ->fetchField();
  if (isset($result)) {

  	return (int) $result;

  }

	return FALSE;
}

/**
 * Obtener nid concepto.
 */
function _publication_obtener_nid_concepto ($title){
    $result = db_select('node', 'n')
    ->fields('n',array('nid'))
    ->condition('type', 'concept')
    ->condition('title', '%'.db_like($title), 'LIKE')
    ->range(0,1)
     ->execute()
    ->fetchField();
    if (isset($result)) {
    	return (int) $result;
    }
	return FALSE;
}


/**
 * Formatear a JSON.
 */
function format_json($file_uri){
  $new_json = array();
  if( strpos($file_uri, 'public://') !== false ){
    $filepath = drupal_realpath($file_uri);
  }else{
    $filepath = $file_uri;
  }
  $file_contents = file_get_contents($filepath);
  $json = drupal_json_decode($file_contents);
  if( is_array($json) && !empty($json) && isset($json["nodes"]) ){
    $nodes = $json["nodes"];
    foreach ($nodes as $key => $node) {
      if(isset($node["node"])){
        $new_json[] = $node["node"];
      }
    }
  }
  if(!empty($new_json)){
    $file_content = drupal_json_encode($new_json);
    $name = 'migrate_data.json';
    $directory = 'public://migration/events/';
    $path = $directory . $name;
    $file_delete = file_unmanaged_delete($path);
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    file_prepare_directory($directory, FILE_MODIFY_PERMISSIONS);
    $file = file_save_data($file_content, $path, $replace = FILE_EXISTS_REPLACE);
    if(isset($file->uri)){
      return $file->uri;
    }
  }
  return $file_uri;
}

/**
 * Buscar una serie de evento a partir de un titulo.
 */
function find_serie_de_evento($serie_event_title = ""){
  if(!empty($serie_event_title)){
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'serie_eventos')
      ->propertyCondition('title', '%' . db_like($serie_event_title) . '%', 'LIKE')
      ->range(0, 1);
     $result = $query->execute();
    if (isset($result['node'])) {
      $items_nids = array_keys($result['node']);
      return isset($items_nids[0])?$items_nids[0]:NULL;
    }
  }
  return NULL;
}

/**
 * Retorna tid segun nombre de tipo.
 */
function convertPublicationType($value) {
  switch ($value) {
    case 'documento de trabajo':
      $value = 4;
      break;

    case 'articulo':
      $value = 201;
      break;

    case 'libro':
      $value = 206;
      break;

    default:
      break;
  }

  return $value;
}

/**
 * Obtener mes numérico.
 */
function _publication_obtener_mes_numerico($mes){
  switch ($mes) {
    case 'Enero':$value = 1;break;
    case 'Febrero':$value = 2;break;
    case 'Marzo':$value = 3;break;
    case 'Abril':$value = 4;break;
    case 'Mayo':$value = 5;break;
    case 'Junio':$value = 6;break;
    case 'Julio':$value = 7;break;
    case 'Agosto':$value = 8;break;
    case 'Septiembre':$value = 9;break;
    case 'Octubre':$value = 10;break;
    case 'Noviembre':$value = 11;break;
    case 'Diciembre':$value = 12;break;

    default:
      break;
  }

  return $value;
}

/**
 * Obtener uid a partir del email.
 */
function _publication_obtener_autor($mail) {
  if (empty($mail)) {
    return FALSE;
  }
  $query = db_select('users', 'u');
  $query->fields('u', array('uid'));
  $query->condition('u.mail', $mail);
  return $query->execute()->fetchField();
}
