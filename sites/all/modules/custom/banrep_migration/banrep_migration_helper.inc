<?php

/*
* get_estado_de_publicacion_clasificado
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

function _get_index_nid ($title){
	// $nid = 70;
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

