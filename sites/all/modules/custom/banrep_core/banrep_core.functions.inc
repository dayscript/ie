<?php

/**
 * @file
 * Funciones de ayuda del módulo banrep core.
 */

/**
 * Obtiene una matriz renderizable para un solo valor de campo.
 */
function get_user_field_value($entity, $field_name){
  $value = FALSE;
  $entity_type = 'user';
  $field_name_values = field_get_items($entity_type, $entity, $field_name);
  if(!empty($field_name_values)){
    foreach ($field_name_values as $key => $field_name_value) {
      if(isset($field_name_value['tid'])){
       $tid = $field_name_value['tid'];
       $term = taxonomy_term_load($tid);
       if(is_object($term)) {
        if($field_name == 'field_dependency' || $field_name == 'field_position') {
          global $language;
          $term = i18n_taxonomy_term_get_translation($term, $language->language);
        }
        $value[] = $term->name;
       }
    }elseif(isset($field_name_value['fid'])){
      $value[] = $field_name_value;
      }else{
        $field_view_value = field_view_value($entity_type, $entity, $field_name, $field_name_value);
        if(isset($field_view_value['#markup'])){
          $value[] = $field_view_value['#markup'];
        }
      }
    }
  }
  if($value != FALSE && count($value) == 1){
    $value = $value[0];
  }
  return $value;
}

/**
 * Obtiene una matriz renderizable para un valor de campo
 * de una colección de campos.
 */
function get_user_field_collections_fields_values($field_collection_id, $fields){
	$entity_type = 'field_collection_item';
	$entity = field_collection_item_load($field_collection_id['value']);
	$wrapper = entity_metadata_wrapper($entity_type, $entity);
	$value = FALSE;
	foreach ($fields as $key => $field) {
		$key_val = $field;
		if(isset($wrapper->$field)){
			$value[$key_val] = $wrapper->$field->value();
		}
	}
	return $value;
}

/**
 * Obtiene colección de campos del usuario.
 */
function get_user_field_collections_value($entity, $field_name, $fields){
	$value = FALSE;
	$entity_type = 'user';
	$field_name_values = field_get_items($entity_type, $entity, $field_name);
	if(!empty($field_name_values)){
	  foreach ($field_name_values as $key => $field_collection_id) {
	  	$value[] = get_user_field_collections_fields_values($field_collection_id, $fields);
	  }
	}
	if($value != FALSE && count($value) == 1){
		$value = $value[0];
	}
	return $value;
}

/**
 * Obtiene valores de campos de usuarios.
 */
function get_user_fields_values($fields_name, $entity){
	$user_data = array();
	$field_collections = array(
		'field_social_networks' => array('field_social_network', 'field_url'),
		'field_academics_profiles' => array('field_academic_profile', 'field_url'),
		'field_studies_carried_out' => array('field_titulo', 'field_university', 'field_year'),
	);
	$field_collections_keys = array_keys($field_collections);
	foreach ($fields_name as $key => $field_name) {
		if(in_array($field_name, $field_collections_keys)){
			$str_field_name = $field_name;
		    $user_data[$field_name] = get_user_field_collections_value($entity, $field_name, $field_collections[$field_name]);
		}else{
			$user_data[$field_name] = get_user_field_value($entity, $field_name);
		}
	}
	return $user_data;
}

/**
 * Obtiene info del usuario a partir del uid.
 */
function get_current_user_data($uid = ''){

    if(empty($uid)){
        global $user;
        $uid = $user->uid;
    }
	$user_data = array();
	// if(user_is_logged_in()){
	$user_fields = user_load($uid);
	$fields = array(
		'field_full_name',
		'field_perfil',
    'field_perfil_ingles',
		'field_research_lines',
		'field_position',
		'field_dependency',
		'field_city',
		'field_date_admission',
		'field_email_corporate',
		'field_email_personal',
		'field_genre',
		'field_score',
		'field_academics_profiles',
		'field_social_networks',
		'field_likes',
		'field_cv_file',
		'field_pr_visibility',
		'field_notification_alter',
		'field_studies_carried_out',
		'field_scopus_author_author_id',
		'field_repec_id',
	);
	$user_data = get_user_fields_values($fields, $user_fields);
	$user_data['uid'] = $user_fields->uid;
	$user_data['mail'] = $user_fields->mail;
	$user_data['picture'] = $user_fields->picture;
	$user_data['roles'] = $user_fields->roles;
  $co_authors = get_co_authors_for_user($user_fields->uid);
	$user_data['co_authors'] = $co_authors['internal'];
	$user_data['otros_coautores'] = $co_authors['external'];
	//}
	return $user_data;
}

/**
 * Obtiene coauthores por usuario.
 */
function get_co_authors_for_user($uid) {
  $co_authors = array(
    'internal' => array(),
    'external' => array(),
  );
  // Selecciona las publicaciones que corresponden a los pub_user del usuario
  $query = db_select('node','n');
  $query->join('field_data_field_user_reference', 'ur', 'ur.entity_id = n.nid');
  $query->join('field_data_field_publicacion', 'p', 'p.entity_id = n.nid');
  $query->addField('p','field_publicacion_target_id','nid');
  $query->condition('n.type', 'pub_user');
  $query->condition('ur.field_user_reference_target_id', $uid);
  $publication_query = $query->execute();
  foreach ($publication_query as $publication_row) {
    // Selecciona los nodos pub_user que corresponden a la publicación, pero no
    // son del usuario
    $query = db_select('node', 'n');
    $query->join('field_data_field_user_reference', 'ur', 'ur.entity_id = n.nid');
    $query->join('field_data_field_publicacion', 'p', 'p.entity_id = n.nid');
    $query->addField('ur', 'field_user_reference_target_id', 'tid');
    $query->condition('n.type', 'pub_user');
    $query->condition('ur.field_user_reference_target_id', $uid, '<>');
    $query->condition('p.field_publicacion_target_id', $publication_row->nid);
    $author_query = $query->execute();
    foreach ($author_query as $author_row) {
      $co_authors['internal'][$author_row->tid] = TRUE;
    }
    // Selecciona el campo main_author_reference de la publicación
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_main_author_reference', 'mar', 'mar.entity_id = n.nid');
    $query->addField('mar', 'field_main_author_reference_tid', 'tid');
    $query->condition('n.type', 'publication');
    $query->condition('n.nid', $publication_row->nid);
    $query->isNotNull('mar.field_main_author_reference_tid');
    $author_query = $query->execute()->fetchObject();
    if ($author_query) {
      $co_authors['external'][$author_query->tid] = TRUE;
    }
    // Selecciona el campo other_co_authors de la publicación (pueden ser muchos)
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_other_co_authors', 'oca', 'oca.entity_id = n.nid');
    $query->addField('oca', 'field_other_co_authors_tid', 'tid');
    $query->condition('n.type', 'publication');
    $query->condition('n.nid', $publication_row->nid);
    $query->isNotNull('oca.field_other_co_authors_tid');
    $author_query = $query->execute();
    foreach ($author_query as $author_row) {
      $co_authors['external'][$author_row->tid] = TRUE;
    }
  }

  // Busca las taxonomias que tengan usuarios repetidos
  if (isset($co_authors['internal']) && isset($co_authors['external'])) {
    $co_authors_internal = array_keys($co_authors['internal']);
    if(!empty($co_authors_internal)){
      $query = db_select('taxonomy_term_data', 't');
      $query->join('field_data_field_user_reference', 'ur', 'ur.entity_id = t.tid');
      $query->fields('t', array('tid'))
            ->condition('ur.entity_type', 'taxonomy_term')
            ->condition('ur.bundle', 'autores_externos')
            ->condition('ur.field_user_reference_target_id', $co_authors_internal, 'IN');
      $taxs_repeated = $query->execute()->fetchAll();
      foreach ($taxs_repeated as $tax) {
        unset($co_authors['external'][$tax->tid]);
      }
    }
  }

  // Get keys for the authors
  foreach ($co_authors as $key => $list) {
    $co_authors[$key] = array_keys($list);
  }

  return $co_authors;
}

/**
 * Obtiene otros coauthores relacionados al usuario.
 */
function get_user_otros_coautores($uid = ''){

  $query = db_select('field_data_field_other_co_authors', 'other_co_authors');
  $query->condition('other_co_authors.bundle', 'publication');
  $query->condition('other_co_authors.entity_type', 'node');

  $query->leftJoin('node', 'n', 'n.nid = other_co_authors.entity_id');
  $query->condition('n.status', NODE_PUBLISHED);
  $query->condition('n.uid', $uid);

  $query->fields('other_co_authors', array('field_other_co_authors_tid'));

  $result = $query->execute();
  $items = array();
  while($record = $result->fetchObject()) {
    $items[] = $record->field_other_co_authors_tid;
  }

  if(count($items) > 0){
    return array_unique($items);
  }
  return FALSE;

}

/**
 * Obtiene otras publicaciones.
 */
function get_other_publications($uid = ''){
  $query = db_select('node', 'n');
  $query->condition('n.type', 'activity');
  $query->condition('n.status', NODE_PUBLISHED);
  $query->condition('n.uid', $uid);
  $query->fields('n', array('nid'));

  $query->Join('field_data_field_act_status', 'pt', 'n.nid = pt.entity_id');
  $query->condition('pt.field_act_status_value', 'publico', '=');

  $result = $query->execute();
  $items = array();
  while($record = $result->fetchObject()) {
     $items[] = $record->nid;
  }
  if(count($items) > 0){
    return $items;
  }
  return FALSE;
}

/**
 * Obtiene user coautores.
 */
function get_user_coautores($uid = ''){
	$query = db_select('field_data_field_co_author', 'co_author');
	$query->condition('co_author.bundle', 'field_co_authors');
	$query->condition('co_author.entity_type', 'field_collection_item');
	$query->fields('co_author', array('field_co_author_target_id'));

	$query->leftJoin('field_data_field_co_authors', 'co_authors', 'co_authors.field_co_authors_value = co_author.entity_id');
	$query->condition('co_authors.bundle', 'publication');
	$query->condition('co_authors.entity_type', 'node');

	$query->leftJoin('node', 'n', 'n.nid = co_authors.entity_id');
	$query->condition('n.status', NODE_PUBLISHED);
	$query->condition('n.uid', $uid);

	$result = $query->execute();
	$items = array();
	while($record = $result->fetchObject()) {
	   $items[] = $record->field_co_author_target_id;
	}
	if(count($items) > 0){
		return array_unique($items);
	}
	return FALSE;
}

/**
 * Obtener UID.
 */
function get_uid($username){
  $uid = db_select('users', 'u')
  ->fields('u',array('uid'))
  ->condition('name', $username)
  ->execute()
  ->fetchField();

  if($uid) {
    return $uid;
  }
  else {
    return 1;
  }
}

/**
 * Obtener nombre co autor.
 */
function get_other_co_author_name($tid){
	$term = taxonomy_term_load($tid);
	if(isset($term->name)){
		return $term->name;
	}
	return FALSE;
}

/**
 * Obtener nombre de usuario.
 */
function get_username($uid){
  $name = db_select('users', 'u')
  ->fields('u',array('name'))
  ->condition('uid', $uid)
  ->execute()
  ->fetchField();

  if($name) {
    return $name;
  }
  else {
    return t('Anonymous');
  }
}

/**
 * Abrir un archivo JSON.
 */
function _banrep_open_json($file) {
   if(file_exists($file)) {
     $str_data = file_get_contents($file);
    $data = json_decode($str_data,TRUE);
     return $data;
    }

   return FALSE;
}

/**
 * Valida coauthores externos de un nodo.
 */
function _banrep_core_validate_external_authors($node) {
  $co_authors = array();
  if (!empty($node->field_main_author_reference[LANGUAGE_NONE])) {
    $co_authors[] = array(
      'main'=>TRUE,
      'tid'=>$node->field_main_author_reference[LANGUAGE_NONE][0]['tid']
    );

    $co_authors = array_merge($co_authors, $node->field_other_co_authors[LANGUAGE_NONE]);
    $pending_authors = array();
    foreach ($co_authors as $author_reference) {
      if (isset($author_reference['tid'])) {
        $author_taxonomy = taxonomy_term_load($author_reference['tid']);
        if (
          $author_taxonomy !== FALSE &&
          !empty($author_taxonomy->field_review) &&
          $author_taxonomy->field_review[LANGUAGE_NONE][0]['value'] !== PUB_REVIEW_REVIEWED
        ) {
          $pending_authors[] = array(
            'main'=>isset($author_reference['main']),
            'name'=>$author_taxonomy->name,
            'uri'=>taxonomy_term_uri($author_taxonomy)['path']
          );
        }
      }
    }
    foreach ($pending_authors as $author) {
      form_set_error(
        $author['main'] ? 'field_main_author_reference' : 'field_other_co_authors',
        t(
          'El autor externo <a href="@url" target="_blank">@name</a> aún no ha sido revisado',
          array(
            '@url'=>url($author['uri'].'/edit'),
            '@name'=>$author['name'],
          )
        )
      );
    }
  }
}

/**
 * Actualizar taxonomia JEL.
 */
function _banrep_core_update_taxonomy_jel($vid){
	//load all the tids under the vocabulary specified as an argument
	$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vid));

	$count_updated = 0;
	$count_error = 0;
	$empty_jel_code_terms = array();

	foreach ($terms as $term) {
 		$term->field_title_es['und'][0]['value'] = $term->name;
 		//validate if $term->field_jel_code is empty
 		if (empty($term->field_jel_code['und'][0]['value'])){
 			$count_error++;
 			$empty_jel_code_terms[] = $term->tid;
 			continue;
 		} else {
 			$term->name = $term->field_jel_code['und'][0]['value'];
 		}
 		$retval = taxonomy_term_save($term);

 		if ($retval == SAVED_UPDATED){
 			$count_updated++;
 		} else {
 			$count_error++;
 		}
	}

	$output = array("count_updated" => $count_updated, "count_error" => $count_error, 'empty_jel_code_terms' => $empty_jel_code_terms);

	return $output;
}

/**
 * Traduce taxonomia soluciones caie.
 */
function _banrep_core_translate_taxonomy($vid)
{
	global $language;

	$soluciones_caie = taxonomy_get_tree($vid, $parent = 0, $max_depth = NULL, $load_entities = TRUE);
    $translated_soluciones_caie = array();

    foreach ($soluciones_caie as $term) {
      if ($term->language != $language->language) {
        continue;
      }

      if (module_exists('i18n_taxonomy')) {
        $tmpterm = i18n_taxonomy_term_get_translation($term, $language->language);
        if (!is_null($tmpterm)){
          $translated_soluciones_caie[] = $tmpterm;
        }
      }
    }

    return $translated_soluciones_caie;
}


/**
 * Obtiene codigos jel en uso.
 */
function _banrep_obtener_codigos_jel_en_uso($idioma){

  $query = db_select('taxonomy_term_data', 't');
  $query->Join('field_data_field_research_lines', 'lineas', 't.tid = lineas.field_research_lines_tid');
	if($idioma == 'es'){
		$query->LeftJoin('field_data_field_title_es', 'titulo', 't.tid = titulo.entity_id');
		$query->fields('titulo', array('field_title_es_value'));
	}
	else {
		$query->LeftJoin('field_data_field_title_en', 'titulo', 't.tid = titulo.entity_id');
		$query->fields('titulo', array('field_title_en_value'));
	}

  $query->condition('t.vid', 17);
  // $query->condition('t.status', 1);
  $query->fields('t', array('name', 'tid'));

  $result = $query->execute()->fetchObject();
	$items = array('All' => '- Any -');
  while($record = $result->fetchObject()) {
		if($idioma == 'es'){
    	$items[$record->tid] = $record->field_title_es_value;
		}
		else {
			if($idioma == 'en'){
				$items[$record->tid] = $record->field_title_en_value;
			}
		}
  }

  if(count($items) > 0){
    return $items;
  }
  return FALSE;

}

/**
 * Obtiene nombre tipo de solicitud.
 */
function _banrep_get_name_tipo_solicitud($token_data){
  $nid = $token_data['node']->nid;
  $submission = $token_data['webform-submission'];
  switch ($nid) {
    case SERVICES_FORM_NID_1:
        if(isset($submission->data[5][0])){
          $tipo_solicitud_key = $submission->data[5][0];
        }
        break;
    case SERVICES_FORM_NID_2:
        if(isset($submission->data[6][0])){
          $tipo_solicitud_key = $submission->data[6][0];
        }
        break;
    case SERVICES_FORM_NID_3:
        if(isset($submission->data[7][0])){
          $tipo_solicitud_key = $submission->data[7][0];
        }
        break;
    case SERVICES_FORM_NID_4:
        if(isset($submission->data[9][0])){
          $tipo_solicitud_key = $submission->data[9][0];
        }
        break;
    case SERVICES_FORM_NID_5:
        if(isset($submission->data[7][0])){
          $tipo_solicitud_key = $submission->data[7][0];
        }
        break;
    case SERVICES_FORM_NID_6:
        if(isset($submission->data[6][0])){
          $tipo_solicitud_key = $submission->data[6][0];
        }
        break;
    case SERVICES_FORM_NID_7:
        if(isset($submission->data[9][0])){
          $tipo_solicitud_key = $submission->data[9][0];
        }

        break;
    case SERVICES_FORM_NID_8:
        if(isset($submission->data[9][0])){
          $tipo_solicitud_key = $submission->data[9][0];
        }
        break;
    case SERVICES_FORM_NID_9:
        if(isset($submission->data[16][0])){
          $tipo_solicitud_key = $submission->data[16][0];
        }
        break;
}
$array = array(
  'Orientación al usuario' => 'orientaci-n-al-usuario',
  'Consulta de material bibliográfico' => 'consulta-de-material-bibliogr-fico',
  'Préstamos' => 'pr-stamos',
  'Prestámo interbibliotecario' => 'prest-mo-interbibliotecario',
  'Evaluación y adquisición de material bibliográfico' => 'evaluaci-n-y-adquisici-n-de-material-bibliogr-fico',
  'Identidad digital' => 'identidad-digital',
  'Estrategias de Publicación' => 'estrategias-de-publicaci-n',
  'Métricas alternativas de impacto académico' => 'm-tricas-alternativas-de-impacto-acad-mico',
  'Difusión de la producción en  acceso abierto (R.I., RePec)' => 'difusi-n-de-la-producci-n-en-acceso-abierto-r-i-repec',
  'Seguimiento del impacto y visibilidad de las publicaciones academicas BANREP' => 'seguimiento-del-impacto-y-visibilidad-de-las-publicaciones-academicas-banrep',
  'Asesoría en el manejo de herramientas bibliométricas' => 'asesor-a-en-el-manejo-de-herramientas-bibliom-tricas',
  'El CAIE le invita un café' => 'el-caie-le-invita-un-caf',
  'Gestión de publicaciones académicas' => 'gesti-n-de-publicaciones-acad-micas',
  'Obtención de documentos' => 'obtenci-n-de-documentos',
  'Elaboración bibliografía especializada' => 'elaboraci-n-bibliograf-a-especializada',
  'Talleres de entrenamiento' => 'talleres-de-entrenamiento',
  'Monitoreo de la información' => 'monitoreo-de-la-informaci-n',
  'Gestión y Administración Sistemas de Información' => 'gesti-n-y-administraci-n-sistemas-de-informaci-n',
  'Evaluación e implementación de nuevas estrategias tecnológicas' => 'evaluaci-n-e-implementaci-n-de-nuevas-estrategias-tecnol-gicas',
  'User orientation' => 'user-orientation',
  'Estandarización de perfiles web' => 'estandarizaci-n-de-perfiles-web',
);

  $resultado = array_search($tipo_solicitud_key, $array);

  return $resultado;

}

/**
 * Cambia el nombre de todos los términos de un vocabulario de manera que sólo
 * la primera letra sea mayúscula y el resto minúscula
 * ejemplo: Prueba UNO -> Prueba uno.
 */
function _banrep_core_normalize_terms_name_by_vocabulary($vocabulary_name) {
  $terms = entity_load(
    'taxonomy_term',
    FALSE,
    array(
      'vid' => taxonomy_vocabulary_machine_name_load($vocabulary_name)->vid
    )
  );
  foreach ($terms as $term) {
    $term->name =
      mb_strtoupper(mb_substr($term->name, 0, 1)) .
      mb_strtolower(mb_substr($term->name, 1))
    ;
    entity_save('taxonomy_term', $term);
  }
}

/**
 * Obtener concept type.
 */
function _banrep_core_get_concept_type($nid){
  $query = db_select('field_data_field_concept_category', 'c');
  $query->condition('c.entity_id', $nid);
  $query->fields('c', array('field_concept_category_tid'));
  $query->orderBy('c.field_concept_category_tid', 'DESC');
  $query->range(0,1);
  $concept_type = $query->execute()->fetchField();

  return $concept_type;
}

/**
 * Obtener usuario desde un nid.
 */
function _banrep_core_get_user_by_author_term($nid){
  // dpm($nid);
  $query = db_select('field_data_field_user_reference', 'u');
  $query->condition('u.entity_id', $nid);
  $query->condition('u.entity_type', 'taxonomy_term');
  $query->fields('u', array('field_user_reference_target_id'));
  $query->range(0,1);
  $user_id = $query->execute()->fetchField();
  return $user_id;
}

/**
 * Obtener username por UID.
 */
function _banrep_core_get_username_by_uid($uid){
  $name = db_select('users', 'u')
  ->fields('u',array('name'))
  ->condition('uid', $uid)
  ->execute()
  ->fetchField();

  if($name) {
    return $name;
  }
  else {
    return NULL;
  }
}

/**
 * Vaida si es privado.
 */
function field_can_be_private($field_name){
   $name = 'profile_setting_'.$field_name;
   return ((bool) variable_get($name, FALSE));
}
