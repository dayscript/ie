<?php

/**
 * @file
 * Páginas que provee el módulo core de banrep IE.
 */

/**
 * Página de creación de publicación.
 */
function banrep_core_publications_add_page() {
  module_load_include('inc', 'banrep_core', 'banrep_core.functions');
  drupal_set_title(t('Add publication'));
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = '<span>' . t('Add publication') . '</span>';
  drupal_set_breadcrumb($breadcrumb);
  $output = '';
  $add_form = drupal_get_form('publications_add_form');
  $output .= '<section class="form-add-publication"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
  return $output;
}

/**
 * Página de edición de una publicación.
 */
function banrep_core_publications_edit_page() {
  module_load_include('inc', 'banrep_core', 'banrep_core.functions');
  drupal_set_title(t('Edit publication'));
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = '<span>' . t('Edit publication') . '</span>';
  drupal_set_breadcrumb($breadcrumb);
  $output = '';
  $add_form = drupal_get_form('publications_add_form');
  $output .= '<section class="form-add-publication"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
  return $output;
}

/**
 * Página de edición de grupo de investigación.
 */
function banrep_core_group_edit_page($tid){
  drupal_set_title(t('Manage Group'));
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = '<span>' . l(t('Group'), 'taxonomy/term/' . $tid) . '</span>';
  $breadcrumb[] = '<span>' . t('Manage') . '</span>';
  drupal_set_breadcrumb($breadcrumb);

  global $user;
  $term = taxonomy_term_load($tid);
  $output = '';
  foreach ($term->field_members['und'] as $key => $member) {
    if($member['target_id'] == $user->uid && user_has_role(ADMIN_GRUPO_RID)){
      drupal_add_library ('system', 'ui.tabs');
      drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile_edit.js');
      module_load_include('inc', 'taxonomy', 'taxonomy.admin');
      $vocabulary = taxonomy_vocabulary_load(2, FALSE);
      unset($term->field_image);
      $form = drupal_get_form('taxonomy_form_term', $term, $vocabulary);
      $output = '
      <div id="tabs">
        <ul>
          <li><a href="#tabs-1">' . t('General Information') . '</a></li>
          <li><a href="#tabs-2">' . t('Manage Blog') . '</a></li>
          <li><a href="#tabs-3">' . t('Manage News') . '</a></li>
        </ul>
        <div id="tabs-1"><div class="tabs-wrapper">
          <div class="profile-edit-group">
          ' . drupal_render($form) . '
        </div></div></div>
        <div id="tabs-2"><div class="tabs-wrapper"><div class="tablero-caie">
          ' . views_embed_view('gestionar_entradas_de_blogs', 'gestionar_blogs', $term->tid) . '
        </div></div></div>
        <div id="tabs-3"><div class="tabs-wrapper"><div class="tablero-caie">
          ' . views_embed_view('gestionar_entradas_de_blogs', 'gestionar_noticias', $term->tid) . '
        </div></div></div>
      </div>';
      return $output;
    }
  }

  return drupal_access_denied();
}

/**
 * Página creación de noticia.
 */
function banrep_core_article_add_page() {
  module_load_include('inc', 'node', 'node.pages');
  global $user;

  drupal_set_title('Agregar noticia');
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = '<span>' . t('News') . '</span>';
  $breadcrumb[] = '<span>' . t('Add') . '</span>';

  drupal_set_breadcrumb($breadcrumb);

  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => 'article',
    'language' => 'es',
  );
  $output = '';
  $add_form = drupal_get_form('article_node_form', $node);

  $output .= '<section class="form-add-noticia"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
  return $output;
}

/**
 * Página creación de entrada de blog.
 */
function banrep_core_blogs_add_page() {
  module_load_include('inc', 'node', 'node.pages');
  global $user;

  drupal_set_title('Agregar Entrada de Blog');
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = '<span>Blog</span>';
  $breadcrumb[] = '<span>' . t('Add') . '</span>';

  drupal_set_breadcrumb($breadcrumb);

  $output = '';
  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => 'blog',
    'language' => LANGUAGE_NONE,
  );
  $add_form = drupal_get_form('blog_node_form', $node);

  $output .= '<section class="form-add-blog"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
  return $output;
}

/**
 * Entrada de Blog edit page.
 */
function banrep_core_blogs_edit_page($nid) {
  module_load_include('inc', 'node', 'node.pages');
  global $user;
  drupal_set_title('Editar Entrada de Blog');
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = '<span>Blog</span>';
  $breadcrumb[] = '<span>Editar Entrada de Blog</span>';
  drupal_set_breadcrumb($breadcrumb);

  $node = node_load($nid);
  if (isset($node->uid) && isset($user->uid) && ($node->uid == $user->uid)) {
    module_load_include('inc', 'node', 'node.pages');
    $add_form = drupal_get_form('blog_node_form', $node);
    $output .= '<section class="form-edit-blog"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
    return $output;
  }
  else {
    drupal_access_denied();
  }
}

/**
 * Página de edición de artículo.
 */
function banrep_core_article_edit_page($nid) {
  module_load_include('inc', 'node', 'node.pages');
  global $user;
  drupal_set_title('Edit New');
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = '<span>'.t('New').'</span>';
  $breadcrumb[] = '<span>'.t('Edit').'</span>';
  drupal_set_breadcrumb($breadcrumb);
  $node = node_load($nid);
  if (isset($node->uid) && isset($user->uid) && ($node->uid == $user->uid)) {
    module_load_include('inc', 'node', 'node.pages');
    $add_form = drupal_get_form('article_node_form', $node);
    $output .= '<section class="form-edit-noticia"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
    return $output;
  }
  else {
    drupal_access_denied();
  }
}

/**
 * Funciona que adiciona un like al perfil del usuario.
 */
function banrep_core_save_like_to_user() {
  $response = FALSE;
  $new_val = 0;
  $current_val = 0;
  if (isset($_POST['data_uid'])) {
    $uid = $_POST['data_uid'];
    $user = user_load($uid);
    if ($user) {
      if (isset($user->field_likes['und'][0]['value'])) {
        $current_val = intval($user->field_likes['und'][0]['value']);
      }
    }
    $new_val = $current_val +1;
    $user->field_likes['und'][0]['value'] = $new_val;
    if (user_save($user) != FALSE) {
      $response = TRUE;
    }
  }
  drupal_json_output(array('response' => $response, 'new_val' => $new_val));
}

/**
 * Página del perfil del investigador.
 */
function banrep_core_profile_page($name = '') {
  global $user;
  global $language;
  $profile_path = ($language->language == 'es') ? 'investigadores' : 'researchers';
  $profile_info_order = FALSE;
  $show_edit = FALSE;
  if (!empty($name)) {
    $user_load = user_load($name);
    if ($user_load == FALSE) {
      return drupal_not_found();
    }
    else {
      $uid = $user_load->uid;
    }
  }
  else {
    $uid = $user->uid;
  }

  if (user_is_logged_in()) {
    $name = 'profile_info_order_' . $uid;
    $profile_info_order = variable_get($name, FALSE);
    if ($uid == $user->uid) {
      $show_edit = TRUE;
    }
  }

  module_load_include('inc', 'banrep_core', 'banrep_core.functions');
  $user_data = get_current_user_data($uid);
  $field_full_name = isset($user_data['field_full_name']) ? $user_data['field_full_name'] : '';

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(t('Researchers') . ' ', $profile_path);

  if (!empty($field_full_name)) {
    $breadcrumb[] = '<span>' . $field_full_name . '</span>';
  }

  if ($show_edit) {
    $breadcrumb[] = '<span class="pull-right"><label class="label-sort">Ordenar</label> <label class="switch-sort"><input id="switch-sort" type="checkbox"><div class="slider round"></div></label></span>';
  }
  else {
    $breadcrumb[] = '<span></span>';
  }

  drupal_set_breadcrumb($breadcrumb);

  $title = t('Profile') . ' | Portal de Investigaciones Económicas';
  if (!empty($field_full_name)) {
    $title = $field_full_name . ' | Portal de Investigaciones Económicas';
  }

  drupal_set_title($title);
  drupal_add_library('system', 'ui.sortable');
  drupal_add_library('system', 'ui.tabs');
  drupal_add_library('system', 'ui.accordion');
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile.js');
  $content = theme('banrep_core_profile', array('user_data' => $user_data, 'profile_info_order' => $profile_info_order));
  return $content;
}

/**
 * Página de edición del perfil del investigador.
 */
function banrep_core_profile_edit_page() {
  global $user;
  module_load_include('inc', 'banrep_core', 'banrep_core.functions');
  $account = user_load($user->uid, $reset = TRUE);
  $full_name = isset($account->field_full_name['und'][0]['value'])?$account->field_full_name['und'][0]['value'] : '';

  drupal_add_library ('system', 'ui.tabs');
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile_edit.js');

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(t('Investigadores '), '<front>');
  if (!empty($full_name)) {
    $breadcrumb[] = '<span>' . $full_name . '</span>';
  }
  $breadcrumb[] = '<span></span>';
  drupal_set_breadcrumb($breadcrumb);

  drupal_set_title($title = 'Profile Edit | Portal de Investigaciones Económicas');
  $content = theme('banrep_core_profile_edit', array('account' => $account));

  return $content;
}

/**
 * Función para obtener líneas de codigos JEL.
 */
function _banrep_obtener_lineas_codigo($codigos){
  global $language;
  $nombres = array();
  foreach ($codigos as $key => $codigo) {
    if ($language->language == 'es') {
      $query = db_select('field_data_field_title_es', 't');
      $query->fields('t', array('field_title_es_value'));
    }
    else {
      $query = db_select('field_data_field_title_en', 't');
      $query->fields('t', array('field_title_en_value'));
    }
    $query->join('taxonomy_term_data', 'td', 't.entity_id = td.tid');
    $query->condition('td.name', '%' . db_like($codigo), 'LIKE')->range(0, 1);
    $nombres[] = $query->execute()->fetchField();
  }

  return $nombres;
}

/**
 * Función para obtener TID líneas de codigos JEL.
 */
function _banrep_obtener_lineas_tid($codigos) {
  global $language;
  $nombres = array();
  foreach ($codigos as $key => $codigo) {
    $query = db_select('taxonomy_term_data', 't');
    $query->fields('t', array('tid'));
    $query->condition('t.name', '%' . db_like($codigo), 'LIKE')->range(0, 1);
    $nombres[] = $query->execute()->fetchField();
  }

  return $nombres;
}


