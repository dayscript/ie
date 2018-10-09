<?php

/**
 * @file
 * Funciones de ayuda para el módulo investigador.
 */

/**
 * Recibe un arreglo de autores con nombres y apellidos, y lo convierte en una
 * texto con formato APA (levemente modificado, se utilizan todos los apellidos
 * separados por guión)
 * Ejemplo:
 *  < array(array('names'=>'Carlos Piyin Eduardo','surnames'=>'Tejada Guevara'),array('names'=>'Diana','surnames'=>'Ortega'))
 *  > Tejada-Guevara, C. P., Ortega, D.
 * @param $authors arreglo de arreglos asociativos indicando nombres y apellidos
 * @return string Texto listando las personas en formato APA
 */
function banrep_investigador_authors_to_apa($authors) {
  $text = '';
  foreach ($authors as $author) {
    $text .= (empty($text) ? '' : ', ');
    $text .= preg_replace('/\s+/', '-', $author['surnames']);
    $text .= ', ';
    $names = explode(' ',$author['names']);
    $text .= mb_substr($names[0], 0, 1) . '.';
    if (isset($names[1])) {
      $text .= ' ' . mb_substr($names[1], 0, 1) . '.';
    }
  }
  return $text;
}

/**
 * Recibe un arreglo de co-autores con nombres y apellidos, y lo convierte en una
 * texto con formato APA, se le agrega el tipo de rol editor entre parentesis ya
 * sea 'editor' o 'compilador'
 * Ejemplo:
 *  < array(array('names'=>'Carlos Piyin Eduardo','surnames'=>'Tejada Guevara'),array('names'=>'Diana','surnames'=>'Ortega'))
 *  > Tejada-Guevara, C. P.(Ed.), Ortega, D.(Comp.)
 * @param $authors arreglo de arreglos asociativos indicando nombres y apellidos
 * @param $tid el tid de la taxonomia referente a los roles de edicion
 * @return string Texto listando las personas en formato APA
 */
function banrep_investigador_authors_with_role_editor_to_apa($authors, $tid) {
  $tax_editor = taxonomy_term_load($tid);
  $name_role = $tax_editor->name;
  $suffix = '';
  if (stripos($name_role, 'editor') !== FALSE) {
    $suffix = ' (Ed.)';
  }
  elseif (stripos($name_role, 'compilador') !== FALSE) {
    $suffix = ' (Comp.)';
  }

  $text = '';
  foreach ($authors as $author) {
    $text .= (empty($text) ? '' : ', ');
    $text .= preg_replace('/\s+/', '-', $author['surnames']);
    $text .= ', ';
    $names = explode(' ',$author['names']);
    $text .= mb_substr($names[0], 0, 1) . '.';
    if (isset($names[1])) {
      $text .= ' ' . mb_substr($names[1], 0, 1) . '.';
    }
    $text .= $suffix;
  }
  return $text;
}

/**
 * Retorna el nombre del autor a partir de un tid de la tax. autores.
 */
function _banrep_core_obtener_nombres_autor($tid){
  $query = db_select('taxonomy_term_data', 't');
  $query->leftJoin('field_data_field_names','n','t.tid = n.entity_id');
  $query->addField('n', 'field_names_value', 'names');
  $query->condition('n.entity_id', $tid);
  $names = $query->execute()->fetchField();

  return $names;
}

/**
 * Retorna apellidos del autor a partir de un tid de la tax. autores.
 */
function _banrep_core_obtener_apellidos_autor($tid){
  $query = db_select('taxonomy_term_data', 't');
  $query->leftJoin('field_data_field_surnames','n','t.tid = n.entity_id');
  $query->addField('n', 'field_surnames_value', 'names');
  $query->condition('n.entity_id', $tid);
  $surnames = $query->execute()->fetchField();

  return $surnames;
}

/**
 * Retorna información completa del libro.
 */
function _banrep_core_obtener_libro_de_capitulo($book_id){
  $book_data = array();
  $query = db_select('node','n');
  $query->LeftJoin('field_data_field_main_author_reference', 'm', 'n.nid = m.entity_id');
  $query->LeftJoin('field_data_field_other_co_authors', 'o', 'n.nid = o.entity_id');
  $query->LeftJoin('field_data_field_page', 'p', 'n.nid = p.entity_id');
  $query->LeftJoin('field_data_field_pub_city', 'c', 'n.nid = c.entity_id');
  $query->LeftJoin('field_data_field_editorial', 'e', 'n.nid = e.entity_id');
  $query->LeftJoin('field_data_field_url', 'u', 'n.nid = u.entity_id');
  $query->fields('n', array('title'));
  $query->fields('m', array('field_main_author_reference_tid'));
  $query->fields('o', array('field_other_co_authors_tid'));
  $query->fields('p', array('field_page_value'));
  $query->fields('c', array('field_pub_city_value'));
  $query->fields('e', array('field_editorial_value'));
  $query->fields('u', array('field_url_url'));
  $query->condition('n.type', 'publication');
  $query->condition('n.nid', $book_id);
  $book_info = $query->execute()->fetchAll();
  if(count($book_info)){
    $book_data['title'] = $book_info[0]->title;
    $query = db_select('field_data_field_other_co_authors','o');
    $query->fields('o', array('field_other_co_authors_tid'));
    $query->condition('o.bundle', 'publication');
    $query->condition('o.entity_id', $book_id);
    $book_coauthors = $query->execute()->fetchAll();

    if(count($book_coauthors)){
      // Obtengo el tid (Rol editor) de la publicación relacionada
      $query = db_select('field_data_field_role_within_publication', 'fdfr');
      $query->fields('fdfr', array('field_role_within_publication_tid'))
        ->condition('fdfr.entity_type', 'node')
        ->condition('fdfr.bundle', 'publication')
        ->condition('fdfr.entity_id', $book_id);
      $tid_role_edition_book = $query->execute()->fetchfield();

      foreach ($book_coauthors as $key => $value) {
          $k = $key+1;
          if($key == 0){
            $book_data['coauthors'][$key]['names'] = _banrep_core_obtener_nombres_autor($book_info[0]->field_main_author_reference_tid);
            $book_data['coauthors'][$key]['surnames'] = _banrep_core_obtener_apellidos_autor($book_info[0]->field_main_author_reference_tid);

            // Role edition
            $tid_main_author = $book_info[0]->field_main_author_reference_tid;
            $full_name_main = array(
              array(
                'names' => _banrep_core_obtener_nombres_autor($tid_main_author),
                'surnames' => _banrep_core_obtener_apellidos_autor($tid_main_author)
              )
            );
            $book_data['authors_role_edition'][$tid_main_author]['full_name'] = $full_name_main;
            $book_data['authors_role_edition'][$tid_main_author]['name_format'] = banrep_investigador_authors_to_apa($full_name_main);

          }
          $book_data['coauthors'][$k]['names'] = _banrep_core_obtener_nombres_autor($value->field_other_co_authors_tid);
          $book_data['coauthors'][$k]['surnames'] = _banrep_core_obtener_apellidos_autor($value->field_other_co_authors_tid);

          // Role edition
          $full_name_other = array(
            array(
              'names' => _banrep_core_obtener_nombres_autor($value->field_other_co_authors_tid),
              'surnames' => _banrep_core_obtener_apellidos_autor($value->field_other_co_authors_tid)
            )
          );
          $book_data['authors_role_edition'][$value->field_other_co_authors_tid]['full_name'] = $full_name_other;
          $book_data['authors_role_edition'][$value->field_other_co_authors_tid]['name_format'] = banrep_investigador_authors_with_role_editor_to_apa($full_name_other, $tid_role_edition_book);
      }
    }
    elseif($book_info[0]->field_main_author_reference_tid) {
      $book_data['coauthors'][0]['names'] = _banrep_core_obtener_nombres_autor($book_info[0]->field_main_author_reference_tid);
      $book_data['coauthors'][0]['surnames'] = _banrep_core_obtener_apellidos_autor($book_info[0]->field_main_author_reference_tid);
      // Role edition
      $book_data['authors_role_edition']['main'][0]['names'] = _banrep_core_obtener_nombres_autor($book_info[0]->field_main_author_reference_tid);
      $book_data['authors_role_edition']['main'][0]['surnames'] = _banrep_core_obtener_apellidos_autor($book_info[0]->field_main_author_reference_tid);
    }
    $book_data['page'] = $book_info[0]->field_page_value;
    $book_data['city'] = $book_info[0]->field_pub_city_value;
    $book_data['editorial'] = $book_info[0]->field_editorial_value;
    $book_data['url'] = $book_info[0]->field_url_url;
  }
  else {
    return NULL;
  }

  return $book_data;
}

/**
 * Migra usuarios drupal a taxonomia autores.
 */
function _banrep_migrar_usuarios_a_taxonomia(){
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'u.uid = ur.uid');
  $query->fields('u', array('uid'));
  $query->condition('ur.rid', array('4', '5'), 'IN');
  $query->range(0,1);
  $result = $query->execute()->fetchAll();
  foreach ($result as $user) {
    if($user->uid != 333){
      $usuario = user_load($user->uid);
      $query = db_select('taxonomy_term_data', 't');
        $query->join('field_data_field_user_reference', 'u', 't.tid = u.entity_id');
        $query->condition('u.field_user_reference_target_id', $user->uid, '=');
        $query->fields('t', array('tid'));
        $query->range(0,1);
        $main_autor_tid = $query->execute()->fetchField();
        if(!$main_autor_tid){
          $term = new stdClass();
          $term->name = $usuario->field_names['und'][0]['value'] . ' ' . $usuario->field_surnames['und'][0]['value'];
          $term->field_names['und'][0]['value'] = $usuario->field_names['und'][0]['value'];
          $term->field_surnames['und'][0]['value'] = $usuario->field_surnames['und'][0]['value'];
          $term->field_user_reference['und'][0]['target_id'] = $usuario->uid;
          $term->field_author_type['und'][0]['value'] = 2;
          $term->vid = 16;
          $term->parent = 0;
          taxonomy_term_save($term);
        }
    }
  }
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
 * Consulta el tid de un término.
 */
function _banrep_obtener_tid_nombre($nombre) {
  return db_select('taxonomy_term_data', 't')
    ->fields('t', array('tid'))
    ->condition('name', '%' . db_like($nombre) . '%', 'LIKE')
    ->execute()
    ->fetchField();
}

/**
 * Consulta el uid a partir del email.
 */
function _banrep_obtener_uid_por_email($email) {
  return db_select('users', 'u')
    ->fields('u', array('uid'))
    ->condition('mail', '%' . db_like($email) . '%', 'LIKE')
    ->execute()
    ->fetchField();
}
