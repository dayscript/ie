<?php

/**
 * @file
 * Proporciona las páginas de vista / edición / eliminación de seminary.
 */

/**
 * Página seminary.
 */
function banrep_seminary_page() {
  global $language;
  module_load_include('inc', 'banrep_seminary', 'banrep_seminary.functions');
  $seminario = get_seminario();
  $html = array();
  if ($seminario != FALSE) {
    $node = node_load($seminario);
    $node_view = node_view($node, $view_mode = 'sem_detalle_full');
    $html = $node_view;

    if ($language->language == 'es') {
//      drupal_set_title('Seminario: ' . $node->title);
    }
    else {
      drupal_set_title('Seminary: ' . $node->title);
    }
  }

  return $html;
}
