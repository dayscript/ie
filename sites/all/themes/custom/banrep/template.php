<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728096
 */


/**
 * Override or insert variables into the maintenance page template.
 *
 * @param array $variables
 *   Variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
/* -- Delete this line if you want to use this function
function banrep_preprocess_maintenance_page(&$variables, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  banrep_preprocess_html($variables, $hook);
  banrep_preprocess_page($variables, $hook);
}
// */

/**
 * Override or insert variables into the html templates.
 *
 * @param array $variables
 *   Variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("html" in this case.)
 */
/* -- Delete this line if you want to use this function
function banrep_preprocess_html(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // The body tag's classes are controlled by the $classes_array variable. To
  // remove a class from $classes_array, use array_diff().
  $variables['classes_array'] = array_diff($variables['classes_array'],
    array('class-to-remove')
  );
}
// */

function banrep_preprocess_html(&$vars) {
  drupal_add_css('https://fonts.googleapis.com/css?family=Roboto:300,400,500,700', array('group' => CSS_THEME));
  if(arg(0) == "investigadores" || arg(0) == "researchers") {
    $vars['classes_array'][] = 'page-investigadores';
  }
  if(arg(0) == "grupos-de-investigacion" || arg(0) == "research-groups") {
    $vars['classes_array'][] = 'page-grupos';
  }
  if(arg(0) == "seminarios") {
    drupal_add_library('system', 'ui.tooltip');
    drupal_add_js(drupal_get_path('module', 'banrep_seminarios') . '/js/seminarios.js');
  }
}

function banrep_preprocess_search_api_page_full_page(&$vars){
    //dpm($vars);
    hide($vars['form']);
    unset($vars['form']);
}

function banrep_preprocess_search_api_page_results(&$vars){
    hide($vars['form']);
}

/**
 * Override or insert variables into the page templates.
 *
 * @param array $variables
 *   Variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function banrep_preprocess_page(&$variables, $hook) {

  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/masonry.pkgd.min.js');
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/seminars-and-caie-services.js');

  // Agregar JS por sección.
  if(arg(0) == 'seminarios'){
    if(arg(1) == 'resultados-busqueda' || arg(1) == 'historial') {
      drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/masonry.pkgd.min.js');
      drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/seminars-and-caie-services.js');
    }
  }
  elseif(arg(0) == 'taxonomy' && arg(1) == 'term'){
    $term = taxonomy_term_load(arg(2));
    switch ($term->vid) {
      case 2:
        drupal_add_js('//d39af2mgp1pqhg.cloudfront.net/widget-group.js', 'external');
        $variables['show_title'] = FALSE;
        break;
      case 12:
        drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/soluciones_caie_services.js');
        break;

      default:
        break;
    }

  }
  elseif(arg(0) == 'investigadores' || arg(0) == 'researchers') {
    drupal_add_js('//d39af2mgp1pqhg.cloudfront.net/widget-group.js', 'external');
    drupal_add_js(drupal_get_path('module', 'banrep_investigador') . '/js/investigadores.js');
  }
  elseif(arg(0) == 'grupos-de-investigacion' || arg(0) == 'research-groups') {
    drupal_add_js('//d39af2mgp1pqhg.cloudfront.net/widget-group.js', 'external');
  }

  // Home.
  if (isset($variables['is_front'])){
    drupal_add_js(drupal_get_path('module', 'banrep_core').'/js/banrep_revistas_recientes.js');
    unset($variables['page']['content']['system_main']['default_message']);
  }
  if(isset($variables['page']['content']['system_main']['no_content'])) {
    unset($variables['page']['content']['system_main']['no_content']);
  }

  // Sugerencia template.
  if (isset($variables['node']->type)) {
    $nodetype = $variables['node']->type;
    $variables['theme_hook_suggestions'][] = 'page__' . $nodetype;
  }

  // Ocultar titulo.
  if(arg(0) == 'seminarios') {
   $variables['show_title'] = FALSE;
  }
  elseif(arg(0) =='node' && is_numeric(arg(1))){
    $node = menu_get_object();
    if($node->type == 'event'){
      $variables['show_title'] = FALSE;
    }
  }


}

/**
* Implements HOOK_preprocess_user_profile()
* Adds theme suggestions for the user view mode teaser
*/
function banrep_preprocess_user_profile(&$vars) {
  $account = $vars['elements']['#account'];
  $vars['user_profile']['uid'] = $account->uid;
  if (isset($vars['elements']['#view_mode'])) {
    $vars['theme_hook_suggestions'][] = 'user_profile__'.$vars['elements']['#view_mode'];
  }

}

/**
 * Override or insert variables into the node templates.
 *
 * @param array $variables
 *   Variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function banrep_preprocess_node(&$variables, $hook) {

  if ($variables['view_mode'] == 'teaser') {
    $variables['theme_hook_suggestions'][] = 'node__'.$variables['node']->type .'__teaser';
  }

  if ($variables['view_mode'] == 'token') {
    $variables['theme_hook_suggestions'][] = 'node__'.$variables['node']->type .'__token';
  }

  if ($variables['view_mode'] == 'search') {
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__' . $variables['view_mode'];
  }

  if ($variables['view_mode'] == 'resumen_carousel') {
    $variables['theme_hook_suggestions'][] = 'node__'.$variables['node']->type .'__carousel';
  }

  if($variables['node']->type == 'event'){
    $is_semiario = FALSE;
    if(isset($variables['node']->field_tipo_de_evento['und'][0]['tid']) && ($variables['node']->field_tipo_de_evento['und'][0]['tid'] == 191)){
      $is_semiario = TRUE;
    }
    if($is_semiario){
        $variables['theme_hook_suggestions'][] = 'node__seminario__'.$variables['view_mode'];
    }
  }

  if($variables['node']->type == 'publication' && $variables['view_mode'] == 'teaser'){
    $variables['fullname'] = _get_fullname_by_uid($variables['uid']);
  }

  // Optionally, run node-type-specific preprocess functions, like
  // banrep_preprocess_node_page() or banrep_preprocess_node_story().
  $function = __FUNCTION__ . '_' . $variables['node']->type;
  if (function_exists($function)) {
    $function($variables, $hook);
  }
}

function banrep_preprocess_field(&$vars, $hook){
  if ($vars['element']['#field_name'] == 'field_resource') {
    $vars['theme_hook_suggestions'][] = 'field__resources_collected';

    $field_array = array('field_icon', 'field_url');
    rows_from_field_collection($vars, 'field_resources', $field_array);
  }
  if ($vars['element']['#field_name'] == 'field_editorial_resource') {
    $vars['theme_hook_suggestions'][] = 'field__editorial_resource_collected';

    $field_array = array('field_icon', 'field_url');
    rows_from_field_collection($vars, 'field_editorial_resource', $field_array);
  }
}

/**
 * Creates a simple text rows array from a field collections, to be used in a
 * field_preprocess function.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 *
 * @param $field_name
 *   The name of the field being altered.
 *
 * @param $field_array
 *   Array of fields to be turned into rows in the field collection.
 */

function rows_from_field_collection(&$vars, $field_name, $field_array) {
  $vars['rows'] = array();
  foreach($vars['element']['#items'] as $key => $item) {
    $entity_id = $item['value'];
    $entity = field_collection_item_load($entity_id);
    $wrapper = entity_metadata_wrapper('field_collection_item', $entity);
    $row = array();
    foreach($field_array as $field){
      $row[$field] = $wrapper->$field->value();
    }
    $vars['rows'][] = $row;
  }
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param array $variables
 *   Variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function banrep_preprocess_comment(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
}
// */

function banrep_html_head_alter(&$head_elements){

   /* si no pertence a rol investigador se  adiciona tags para que google no indexe la pagina */
  $url_parts = explode('/', request_uri()); // se captura la url y se divide por /
  // se verifica que sea /profile/4646
  if (isset($url_parts[2]) && $url_parts[2] == 'profile' && isset($url_parts[3]) && !empty($url_parts[3]) && is_numeric($url_parts[3])) {
      $usuario = user_load($url_parts[3]);  // se cargar el usuario
      $roles = array_flip($usuario->roles);
      // se verifica que no sea de rol investigador que son los usuario publicos
      if (!isset($roles['investigador'])){
        // se define tag para no indexar la pagina con el robot de google
        $head_elements['metatag_robots_googlebot_2'] = array (
          '#type' => 'html_tag',
          '#tag' => 'meta',
          '#attributes' => array(
            'name' =>  'googlebot',
            'content' => 'noindex',
          ),
        );
        // se verifica que exista el tag del robot generico
        if (isset($head_elements['metatag_robots_0']['#value'])){
          // se cambia el valor del robot generico para que no indexe la pagina
           $head_elements['metatag_robots_0']['#value'] = 'noindex';
        }
        else {
          // si no existe el tag del robot generico se crea dicho tacg
          $head_elements['metatag_robots_0'] = array (
            '#type' => 'html_tag',
            '#tag' => 'meta',
            '#attributes' => array(
              'name' =>  'robots',
              'content' => 'noindex',
            ),
          );
        }
      }
  }


}
