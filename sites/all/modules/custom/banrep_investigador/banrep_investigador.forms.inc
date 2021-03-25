<?php
function activities_add_form($form, &$form_state){

  $form_state['step'] = isset($form_state['step']) ? $form_state['step'] : 1;
  $storage_publication = isset($form_state['storage_publication']) ? $form_state['storage_publication'] : FALSE; // Storage Publicación
  $step = $form_state['step'];
  $form['#tree'] = TRUE;
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['#prefix'] = '<div id="ajax_form_multistep_form"><div class="col-md-12">';
  $form['#suffix'] = '</div></div>';
  $form['#attributes']['class'] = 'activities_add_form';
  $publication = NULL;
  if ($storage_publication != FALSE) {
    $publication_decode = drupal_json_decode($storage_publication);
    $publication = (object) $publication_decode;
  }
  $form['query'] = [
    '#type' => 'fieldset',
    '#title' => '<i class="icon-revista"></i> ' . t('Add Activity') . '<strong><small> (' . t('step number') . ' #1)</strong></small>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];
  $form['query']['content'] = [
    '#type' => 'container',
    '#attributes' => [
      'class' => [
        'demo',
      ],
    ],
    '#weight' => 1,
  ];

  switch ($step) {
    case 3:
      // Render form elements for step #3
      _activities_add_form_step_3($form, $form_state, $publication);
      break;
    case 2:
      // Render form elements for step #2
      _activities_add_form_step_2($form, $form_state, $publication);
      break;
    case 1:
    default:
      // Render form elements for step #1
      _activities_add_form_step_1($form, $form_state, $publication);
      break;
  }

  $form['#attached']['js'] = [
    drupal_get_path('module', 'banrep_investigador') . '/js/activities_node_form.js',
  ];

  if ($storage_publication != FALSE) {
    $form['storage_publication'] = [
      '#type' => 'hidden',
      '#value' => $storage_publication,
    ];
  }
  if ($step !== 3) {
    // Create a container for our buttons
    $form['buttons'] = ['#type' => 'container'];
    // If we are on step 1, we do not want a back button
    if ($step !== 1) {
      $form['buttons']['back'] = [
        '#type' => 'submit',
        '#value' => t('❮ Back'),
        // Setting #limit_validation_errors to an empty array
        // ensures that the form fields are not validated when
        // the back button is used. Otherwise, we will get errors
        '#limit_validation_errors' => [],
        // We need to create a #submit function for this button, or else
        // #limit_validation_errors has no effect. So we create a submit
        // function specifically for this submit button.
        '#submit' => ['_ajax_multistep_form_activities_back_submit'],
        '#ajax' => [
          'wrapper' => 'ajax_form_multistep_form',
          // We pass in the wrapper we created at the start of the form
          'callback' => '_ajax_multistep_form_activities_submit_callback',
          // We pass a callback function we will use later to render the form for the user
        ],
      ];
    }
    $label_next = t('Next') . ' ❯';
    if ($step == 1) {
      $label_next = t('Next') . ' ❯';
    }
    // We only want a forward button if we are not on the last step of the form
    if ($step !== 2) {
      $form['buttons']['forward'] = [
        '#type' => 'submit',
        '#value' => $label_next,
        '#ajax' => [
          'wrapper' => 'ajax_form_multistep_form',
          // We pass in the wrapper we created at the start of the form
          'callback' => '_ajax_multistep_form_activities_submit_callback',
          // We pass a callback function we will use later to render the form for the user
        ],
      ];
    }
    else {
      // We only want a submit button if we are on the last step of the form
      $form['buttons']['submit'] = [
        '#type' => 'submit',
        '#value' => t('Save') . ' ❯',
        '#ajax' => [
          'wrapper' => 'ajax_form_multistep_form',
          // We pass in the wrapper we created at the start of the form
          'callback' => '_ajax_multistep_form_activities_submit_callback',
          // We pass a callback function we will use later to render the form for the user
        ],
      ];
    }
  }

  return $form;
}

/**
 * Form for the _activities_add_form_step_1 step.
 *
 * @see activity_add_form().
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function _activities_add_form_step_1(&$form, &$form_state, &$publication = NULL) {
  $options = taxonomy_get_tree(13, 211);
  $opciones[''] = t('-Select-');

  foreach ($options as $key => $option) {
    $opciones[$option->tid] = $option->name;
  }

  $form['query']['content']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Título',
    '#size' => 60, 
    '#maxlength' => 254,
    '#required' => TRUE,
  );
  $form['query']['content']['aprobado_por'] = array(
    '#type' => 'textfield',
    '#title' => t('Aprobado por'),
    '#autocomplete_path' => 'user/autocomplete',
    '#size' => 60,
    '#maxlength' => 1024,
    '#required' => TRUE,
  );
  $form['query']['content']['identificador_sepi'] = array(
    '#type' => 'textfield',
    '#title' => 'Identificador SEPI',
    '#size' => 60, 
    '#maxlength' => 254,
    '#required' => TRUE,
  );
  $form['query']['content']['type_accumulated'] = array(
    '#title' => t('Type of activity'),
    '#type' => 'select',
    '#description' => '',
    '#options' => $opciones,
    '#default_value' => get_input_value_from_publication($publication, 'type_accumulated'),
    '#required' => TRUE,
  );
  $form['query']['content']['type_concept_formation'] = array(
    '#type' => 'hierarchical_select',
    '#title' => t('Activity'),
    '#config' => array(
      'module' => 'hs_taxonomy',
      'params' => array(
        'vid' => 23, // Enter your vocabulary ID here.
        'root_term' => NULL, // Enter a term ID here if you want to display only terms below the term with that ID.
      ),
      'save_lineage'    => 0,
      'enforce_deepest' => 1,
      'entity_count'    => 0,
      'require_entity'  => 0,
      'resizable'       => 1,
      'level_labels' => array(
        'status' => 1,
        'labels' => array(
          0 => t('-Select-'),
          1 => t('-Select-'),
          2 => t('-Select-'),
          3 => t('-Select-'),
        ),
      ),
      'dropbox' => array(
        // Only allow for a single term or single lineage to be selected.
        'status' => 0,
      ),
      'editability' => array(
        // Creating new terms from within a form to filter by existing terms
        // doesn't make sense, hence it is disabled.
        'status' => 0,
      ),
    ),
    '#default_value' =>  get_input_value_from_publication($publication, 'concept_formation'),
  );
  $form['query']['content']['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#description' => t('Activity description'),
    '#default_value' => get_input_value_from_publication($publication, 'description'),
    '#required' => TRUE,
  );
  $options_date = range((int)date('Y'), 1950);
  $form['query']['content']['publication_year'] = array(
    '#type' => 'select',
    '#title' => t('Year'),
    '#options' => array_combine($options_date, $options_date),
    '#default_value' => get_input_value_from_publication($publication, 'act_year'),
    '#description' => t(''),
    '#prefix' => '<div class="col-md-3">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['query']['content']['start_date'] = array(
    '#title'=>t('Start date'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-30:+1',
    '#type' => 'date_popup',
    '#default_value'=>get_input_value_from_publication($publication, 'start_date'),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-3">',
    '#suffix' => '</div>',
  );
  $form['query']['content']['end_date'] = array(
    '#title'=>t('Close date'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-30:+1',
    '#type' => 'date_popup',
    '#default_value'=>get_input_value_from_publication($publication, 'end_date'),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-3">',
    '#suffix' => '</div>',
  );
  $form['query']['content']['visibility'] = array(
    '#title' => t('Public/Private'),
    '#type' => 'select',
    '#description' => t('Public is visible for all people'),
    '#options' => array('' => t('-Select-'), 'publico' => t('Public'), 'privado' => t('Private')),
    '#default_value' => get_input_value_from_publication($publication, 'visibility'),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-3">',
    '#suffix' => '</div>',
  );
  $form['query']['content']['file'] = array(
    '#title' => t('Attach evidence'),
    '#type' => 'managed_file',
    '#default_value' => get_input_value_from_publication($publication, 'attach_doc'),
    '#description' => t('Upload an evidence document in pdf format'),
    '#upload_location' => 'public://activity',
    "#upload_validators"  => array(
      'file_validate_extensions' => 'pdf',
      '_file_validate_unique' => array($file),
    ),
    '#required' => FALSE,
  );
}

function _file_validate_unique($file) {
   $errors = array();
   $filename = $file->filename;
   if (file_exists('public://activity/' . $filename)) {
      $errors[] = t('The file could not be uploaded because a file by that name already exists in the destination directory.');
   }
   return $errors;
}

/**
 * Render form elements for step #2
 */
function _activities_add_form_step_2(&$form, &$form_state, &$publication = NULL) {
  $term = taxonomy_term_load($form_state['values']['query']['content']['type_accumulated']);
  $node = (object) drupal_json_decode($form_state['storage_publication']);
  $header = [t('Information'), t('Value')];
  $rows = [];

  // Titulo
  $rows[] = [t('Type accumulated'), $term->name];
  // Descripción y resúmen del documento
  $rows[] = [
    t('Summary'),
    $node->body[LANGUAGE_NONE][0]['value'],
  ];

  // Año de publicación
  $publication_year = '';
  if (isset($node->field_year[LANGUAGE_NONE][0]['value'])) {
    $publication_year = $node->field_year[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($publication_year)) {
    $rows[] = [t('Year'), $publication_year];
  }

  // Visibility
  $visibility = '';
  if (isset($node->field_act_status[LANGUAGE_NONE][0]['value'])) {
    $visibility = $node->field_act_status[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($visibility)) {
    $rows[] = [t('Visibility'), $visibility];
  }

  $dates_range = '';
  if (isset($node->field_act_date_start[LANGUAGE_NONE][0]['value'])) {
    $dates_range = $form_state['values']['query']['content']['start_date'] . t(' to ') . $form_state['values']['query']['content']['end_date'];
  }
  if (!empty($dates_range)) {
    $rows[] = [t('Range dates'), $dates_range];
  }


  $table = theme('table', ['header' => $header, 'rows' => $rows]);

  $form['query'] = [
    '#type' => 'fieldset',
    '#title' => '<i class="icon-revista"></i> ' . t('Add activity') . '<strong><small> ' . t('step') . ' #2</strong></small>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $form['query']['header'] = [
    '#markup' => '<h3 class="confirm-registered-information">' . t('Confirm information') . '</h3><div class="row"><div class="confirm-registered-information-wrapper col-md-12">' . $table . '</div></div>',
  ];
}

/**
 * Render form elements for step #3
 */
function _activities_add_form_step_3(&$form, &$form_state, &$publication = NULL) {
  $node = (object) drupal_json_decode($form_state['storage_publication']);
  $msg = t('');
  if (isset($node->nid)) {
    $msg = t('Your activity has been successfully saved and is now in approval process!.');
    $form_state['storage_publication'] = [];
  }
  else {
    $msg = t('An error occurred while saving the publication, please try again!');
  }

  $form['query'] = [
    '#type' => 'fieldset',
    '#title' => '<i class="icon-revista"></i> ' . t('Add Activity') . '<strong><small> ' . t('step') . ' #3</strong></small>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $form['query']['header'] = [
    '#markup' => '<div class="row"><div class="confirm-registered-information-wrapper col-md-12"><p class="info">' . $msg . '</p></div></div>',
  ];
}

/**
 * #ajax callback function that we defined on all of our buttons (back, forward
 * and submit). returns the entire form each time the function is called. This
 * allows for our mulitple steps.
 */
function _ajax_multistep_form_activities_submit_callback($form, &$form_state) {
  return $form;
}

/**
 * We check which step we are on, then validate the submitted values for that
 * step. If the submitted value falls out of the allowed range of values, an
 * error is thrown against the submitted value, and the user will be returned
 * to the current step, being shown the error. Our next step is to create the
 * submit function for our back button. Remember that we needed to explicitly
 * set this function in order for #limit_validation_errors to work.
 */
function _ajax_multistep_form_activities_back_submit($form, &$form_state) {
  $form_state['step']--;
  // Because this is a multi-step form, we always need to rebuild the form
  // on every step, even after submission. This allows our form to be completely
  // Ajaxified without ever requiring a page load.
  $form_state['rebuild'] = TRUE;
}

/**
 * Add publication form submit
 */
function activities_add_form_submit($form, &$form_state) {
  // First we determine which step we are on, and save the
  // submitted values to $form_state['storage']. This will
  // allow our submitted values to persist.
  $step = $form_state['step'];
  // Check to see if the next/forward button was clicked
  if (isset($form_state['values']['buttons']['forward']) && $form_state['values']['op'] == $form_state['values']['buttons']['forward']) {
    // Increase the step by one, to move on to the next step
    $form_state['step'] = $step + 1;
  }
  elseif (isset($form_state['values']['buttons']['submit']) && $form_state['values']['op'] == $form_state['values']['buttons']['submit']) { // Check to see if the final step has been submitted

    // The form has been completed, so we want to return the user to step 1
    // as well as clear any saved values.
    $form_state['step'] = 3;
  }
  // $form_state['rebuild'] to TRUE, in able to ensure that our
  // our form is rebuilt, allowing for the multi-step process
  $form_state['rebuild'] = TRUE;
}

/**
 * Add publication form submit validate
 */
function activities_add_form_validate($form, &$form_state) {
  // First we set up a switch for each of our three steps
  $response = new stdClass();
  $response->success = FALSE;
  $response->is_valid = TRUE;
  $response->msg = '';
  switch ($form_state['step']) {
    case "1":
      _activities_add_form_validate_step_1($form, $form_state, $response);
      break;
    case '2':
      _activities_add_form_validate_step_2($form, $form_state, $response);
      break;
  }
}

/**
 * Add publication form step 1 validations
 */
function _activities_add_form_validate_step_1($form, &$form_state, &$response) {
  // Get the form values
  $values = isset($form_state['values']['query']["content"]) ? $form_state['values']['query']["content"] : [];
  $type_accumulated = isset($values['type_accumulated']) ? $values['type_accumulated'] : '';
  $type_act = array();
  if (!empty($type_accumulated)) {
    $structure =  taxonomy_get_parents_all($type_accumulated);
    foreach ($structure as $tax) {
      $type_act[] = ['tid' => $tax->tid];
    }
  }
  $concept_formation = '';
  if (!empty($type_accumulated)) {
    if ($type_accumulated == 15350) {
      $concept_formation = $values['type_concept_formation'];
      $type_tids[] = ['tid' => $concept_formation];
    }
    else {
      $type_array = explode(',', $type_accumulated);
      foreach ($type_array as $key => $type) {
        $type_tid = _get_tag_by_name($type);
        if ($type_tid) {
          $type_tids[] = ['tid' => $type_tid];
        }
      }
    }
  }
  // Descripción
  $description = isset($values['description']) ? $values['description'] : FALSE;
  if ($description == FALSE) {
    form_set_error('query[content][description]', t('Description is required'));
    $response->is_valid = FALSE;
  }

  // Publication year
  $publication_year = isset($values['publication_year']) ? $values['publication_year'] : FALSE;
  if ($publication_year == FALSE) {
    form_set_error('query[content][publication_year]', t('Publication Year is required'));
    $response->is_valid = FALSE;
  }

  // Publication year
  $visibility = isset($values['visibility']) ? $values['visibility'] : FALSE;
  if ($visibility == FALSE) {
    form_set_error('query[content][visibility]', t('Visibility Year is required'));
    $response->is_valid = FALSE;
  }

  // Start date
  $start_date = isset($values['start_date']) ? $values['start_date'] : FALSE;
  if ($start_date == FALSE) {
    form_set_error('query[content][start_date]', t('Start date is required'));
    $response->is_valid = FALSE;
  }

  // End date
  $end_date = isset($values['end_date']) ? $values['end_date'] : FALSE;
  if ($end_date == FALSE) {
    form_set_error('query[content][end_date]', t('End date is required'));
    $response->is_valid = FALSE;
  }
  // Attach
  try {
    $file = file_load($values['file']);
    $file->filename = $file->fid . '-' . time();
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'banrep_core', 'node', 4);
    // If the file passed validation:
    if (!$file) {
      form_set_error('query[content][file]', t('No file was uploaded.'));
      $response->is_valid = FALSE;
    }
  } catch (Exception $e) {
    drupal_set_message('No se adjuntó ningún archivo');
  }

  if ($response->is_valid) {
    global $user;
    // Storage Publicación
    $node = NULL;
    $storage_publication = isset($form_state['storage_publication']) ? $form_state['storage_publication'] : FALSE;
    if ($storage_publication != FALSE) {
      $node = (object) drupal_json_decode($storage_publication);
    }
    if (is_null($node)) {
      $node = new stdClass();  // Create a new node object
      $node->type = 'activity';  // Content type
      $node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
      node_object_prepare($node);  //Set some default values
      $node->status = 0;   // (1 or 0): published or unpublished
      $node->promote = 0;  // (1 or 0): promoted to front page or not
      $node->sticky = 0;  // (1 or 0): sticky at top of lists or not
      $node->comment = 0;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
    }

    $node->uid = $user->uid;
    $node->title = $values['title'];//time();
    $node->field_identificador_sepi[LANGUAGE_NONE][0]['value'] = $values['identificador_sepi'];
    
    $user_uid = user_load_by_name($values['aprobado_por'])->uid;
    if(isset($user_uid) && !empty($user_uid)) {
      $node->field_usuario[LANGUAGE_NONE][0]['target_id'] = $user_uid;
    }
    $node->field_concept_category[LANGUAGE_NONE] = $type_act;
    if (!empty($concept_formation)) {
      $node->field_concept_formation[LANGUAGE_NONE][0]['tid'] = $concept_formation;
    }
    $node->field_year[LANGUAGE_NONE][0]['value'] = $publication_year;
    $node->body[LANGUAGE_NONE][0]['value'] = $description;
    $node->field_act_status[LANGUAGE_NONE][0]['value'] = $visibility;
    $node->field_act_date_start[LANGUAGE_NONE][0]['value'] = strtotime($start_date);
    $node->field_act_date_end[LANGUAGE_NONE][0]['value'] = strtotime($end_date);
    $node->field_re_attach_doc[LANGUAGE_NONE][0] = (array)$file;
    $node->field_re_attach_doc[LANGUAGE_NONE][0]['display'] = 1;
    // END Additional Info.
    $publication = drupal_json_encode($node);
    $form_state['storage_publication'] = $publication;

  }
  else {

  }
}

/**
 * Add publication form step 2 validations
 */
function _activities_add_form_validate_step_2($form, &$form_state, &$response) {
  $is_back = FALSE;
  if (isset($form_state['values']['buttons']['back']) && $form_state['values']['op'] == $form_state['values']['buttons']['back']) {
    $is_back = TRUE;
  }
  if (!$is_back) {
    // Get the form values | Storage Publicación
    $storage_publication = isset($form_state['storage_publication']) ? $form_state['storage_publication'] : FALSE;
    if ($storage_publication != FALSE) {
      $node = (object) drupal_json_decode($storage_publication);
      // Save Publication
      // Make the storage of the file permanent.
      node_save($node);
      $form_state['storage_publication'] = drupal_json_encode($node);
    }
    else {
      form_set_error(NULL, t('Complete last steps'));
      $response->is_valid = FALSE;
    }
  }
}

/**
 * @file
 * Handles the navigation of the customer survey form
 * All hooks are in the .module file.
 */
/**
 * Generate a header which informs the user of which stage they're on.
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function _activities_get_header($form, &$form_state) {

  $form_stages = array(
    1 => 1,
    2 => 2,
    3 => 3,
  );

  if (isset($form_stages[$form_state['step']])) {
   $current_step = $form_stages[$form_state['step']];
  }
  else {
   $current_step = 1;
  }

  $stages = array(
    1 => array('data' => '1. <i class="fa fa-plus-square" aria-hidden="true"></i>' . t('Create')),
    2 => array('data' => '2. <i class="fa fa-check-circle" aria-hidden="true"></i>' . t('Confirm')),
    3 => array('data' => '3. <i class="fa fa-cloud" aria-hidden="true"></i>' . t('Save')),
  );

  $stages[$current_step]['class'] = array('active');

  $stages_list = theme('item_list', array('items' => $stages));

  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#value' => $stages_list,
  );
  return $form;

}
