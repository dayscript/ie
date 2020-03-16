<?php

function caie_form_1($form, &$form_state) {

  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Identification'),
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Identification'),
  );
  $form['type'] = array(
    '#title' => t('Request type'),
    '#type' => 'select',
    '#description' => '',
    '#options' => array(
      0 => t('--- SELECT ---'),
      1 => t('Sugerencia Adquisicion Material"'),
      2 => t('Asesoría en el manejo de herramientas bibliométricas"'),
      3 => t('Gestion de publicación"'),
      4 => t('Obtención de documentos"'),
      5 => t('Bibliografía Especializada"'),
      6 => t('Monitoreo de información"'),
      7 => t('Consulta para usuario Externo"'),
      8 => t('Renovación"'),
      9 => t('Préstamo Interbibliotecario"'),
    ),
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#default_value' => '',
    '#states' => array(
      'visible' => array(
        'select[name="type"]' => array('value' => 1)
      ),
      'required' => array(
        ':input[name="type"]' => array('value' => 1)
      ),
    ),
  );
  $form['specific_topic'] = array(
    '#type' => 'textfield',
    '#title' => t('Specific topic'),
  );
  return $form;
}

function caie_form_1_submit($form, &$form_state) {
  drupal_set_message('Listo');
}
