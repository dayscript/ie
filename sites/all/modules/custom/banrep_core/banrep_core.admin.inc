<?php


/**
 * Module settings page form.
 */
function banrep_core_search_settings_form($form, &$form_state) {
  $form['blocks'] = array(
    '#description'  => t('<ul>
        <li>' . t('Nombre: Etiqueta o título en el buscador.') . '</li>
        <li>' . t('Url: Url externa donde dirige el buscador.') . '</li>
        <li>' . t('Key: es la llave que entiende el buscador para enviar la palabra.') . '</li>
    </ul>'),
    '#title'        => t('Motores de búsqueda'),
    '#type'         => 'fieldset',
    '#prefix' => '<div id="engines-wrapper">',
    '#suffix' => '</div>'
  );

  $form['blocks']['banrep_core_engines'] = array(
    '#tree'         => TRUE,
    '#theme'        => 'banrep_core_setting_engines_search',
  );

  if (empty($form_state['engines'])) {
    $engines = variable_get('banrep_core_engines', array());
    if (empty($engines)) {
      $form_state['engines'] = array_fill(0, 3, array('pageid' => '', 'formatid' => '', 'name' => ''));
    }
    else {
      $form_state['engines'] = $engines;
    }
  }

  foreach ($form_state['engines'] as $index => $engine) {
    $form['blocks']['banrep_core_engines'][$index]['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('_banrep_core_settings_delete_engine'),
      '#ajax' => array(
        'callback' => '_banrep_core_settings_add_engine_callback',
        'wrapper' => 'engines-wrapper',
      ),
      '#engine_id' => $index,
      '#name' => 'delete-engine-' . $index,
    );
    $form['blocks']['banrep_core_engines'][$index]['pageid'] = array(
      '#type'           => 'textfield',
      '#default_value'  => isset($form_state['engines'][$index]['pageid']) ? $form_state['engines'][$index]['pageid'] : '',
      '#size'           => 24,
    );
    $form['blocks']['banrep_core_engines'][$index]['formatid'] = array(
      '#type'           => 'textfield',
      '#default_value'  => isset($form_state['engines'][$index]['formatid']) ? $form_state['engines'][$index]['formatid'] : '',
    );
    $form['blocks']['banrep_core_engines'][$index]['name'] = array(
      '#type'           => 'textfield',
      '#default_value'  => isset($form_state['engines'][$index]['name']) ? $form_state['engines'][$index]['name'] : '',
      '#size'           => 24,
    );
  }

  $form['blocks']['add_engine'] = array(
    '#type' => 'submit',
    '#value' => t('Agregar Buscador'),
    '#submit' => array('_banrep_core_settings_add_engine'),
    '#ajax' => array(
      'callback' => '_banrep_core_settings_add_engine_callback',
      'wrapper' => 'engines-wrapper'
    ),
  );

  $form['engine_core'] = array(
    '#collapsible'    => TRUE,
    '#collapsed'      => variable_get('banrep_core_engine_url', FALSE),
    '#type'           => 'fieldset',
    '#title'          => t('Buscador interno'),
    '#description'    => t('Configuración General'),
  );
  $form['engine_core']['banrep_core_engine_url'] = array(
    '#type'           => 'textfield',
    '#default_value'  => isset($form_state['values']['banrep_core_delivery_url']) ? $form_state['values']['banrep_core_delivery_url'] : variable_get('banrep_core_engine_url', ''),
    '#title'          => t('URL'),
    '#description'    => t('Ej: resultados-busqueda'),
    '#required'       => TRUE,
  );
  $form['engine_core']['banrep_core_engine_key'] = array(
    '#type'           => 'textfield',
    '#default_value'  => isset($form_state['values']['banrep_core_portal_id']) ? $form_state['values']['banrep_core_portal_id'] : variable_get('banrep_core_engine_key', ''),
    '#title'          => t('Llave o Key'),
    '#description'    => t('Ej: "palabra".'),
    '#required'       => TRUE,
  );

  $form['#submit'] = array('_banrep_core_settings_submit');
  return system_settings_form($form);
}

function _banrep_core_settings_submit(&$form, &$form_state) {
  unset($form_state['storage']);
}

function _banrep_core_settings_add_engine_callback($form, &$form_state) {
  return $form['blocks'];
}

function _banrep_core_settings_add_engine($form, &$form_state) {
  $form_state['engines'][] = array('pageid' => '', 'formatid' => '', 'name' => '');
  $form_state['rebuild'] = TRUE;
}

function _banrep_core_settings_delete_engine($form, &$form_state) {
  unset($form_state['engines'][$form_state['clicked_button']['#engine_id']]);
  if (count($form_state['engines']) < 3) {
    $form_state['engines'][] = array('pageid' => '', 'formatid' => '', 'name' => '');
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Theme the Smart blocks list as a table
 */
function theme_banrep_core_setting_engines_search($variables) {
  $form =& $variables['form'];
  $header = array(t('Nombre'), t('Url'), t('Llave o Key'), '');
  foreach (element_children($form) as $engine) {
    $rows[] = array(
      drupal_render($form[$engine]['pageid']),
      drupal_render($form[$engine]['formatid']),
      drupal_render($form[$engine]['name']),
      drupal_render($form[$engine]['delete'])
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
