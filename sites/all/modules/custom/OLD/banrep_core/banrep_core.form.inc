<?php

/**
 * @file
 * Formularios web del módulo banrep core.
 */

/**
 * Formulario de agregar publicación.
 */
function publications_add_form($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/publications_node_form.js', array('scope'=>'footer'));
  $form_state['step'] = isset($form_state['step']) ? $form_state['step'] : 1;
  $storage_publication = isset($form_state['storage_publication']) ? $form_state['storage_publication'] : FALSE; // Storage Publicación
  $step = $form_state['step'];
  $form['#tree'] = TRUE;
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['#prefix'] = '<div id="ajax_form_multistep_form"><div class="col-md-12">';
  $form['#suffix'] = '</div></div>';
  $form['#attributes']['class'] = 'publications_add_form';
  $publication = NULL;
  if ($storage_publication != FALSE) {
    $publication_decode = drupal_json_decode($storage_publication);
    $publication = (object) $publication_decode;
  }
  if (!$publication) {
    $nid = intval(arg(3));
    if ($nid) {
      $publication = node_load($nid);
      $publication->update_co_authors = TRUE;
      $form_state['nid'] = $nid;
    }
  }

  switch ($step) {
    case 1:
      // Render form elements for step #1
      _publications_add_form_step_1($form, $form_state, $publication);
      break;
    case 2:
      // Render form elements for step #2
      _publications_add_form_step_2($form, $form_state, $publication);
      break;
    case 3:
      // Render form elements for step #3
      _publications_add_form_step_3($form, $form_state, $publication);
      break;
    default:
      // Render form elements for step #1
      _publications_add_form_step_1($form, $form_state, $publication);
      break;
  }

  drupal_add_js(array('banrep_core' => array(
    'PUB_TYPE_ARTICLE' => PUB_TYPE_ARTICLE,
    'PUB_TYPE_BOOK' => PUB_TYPE_BOOK,
    'PUB_TYPE_BOOK_CHAPTER' => PUB_TYPE_BOOK_CHAPTER,
    'PUB_TYPE_WORK_DOCUMENT' => PUB_TYPE_WORK_DOCUMENT,
    'PUB_TYPE_CONFERENCE_DOCUMENT' => PUB_TYPE_CONFERENCE_DOCUMENT,
    'ROL_AUTHOR_COMPLETE_TID' => ROL_AUTHOR_COMPLETE_TID,
    'ROL_BOOK_COMPILER_TID' => ROL_BOOK_COMPILER_TID,
    'ROL_BOOK_EDITOR_TID' => ROL_BOOK_EDITOR_TID,
  )), 'setting');
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
        '#limit_validation_errors' => [],
        '#submit' => ['_ajax_multistep_form_publications_back_submit'],
        '#ajax' => [
          'wrapper' => 'ajax_form_multistep_form',
          // We pass in the wrapper we created at the start of the form
          'callback' => '_ajax_multistep_form_publications_submit_callback',
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
          'callback' => '_ajax_multistep_form_publications_submit_callback',
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
          'callback' => '_ajax_multistep_form_publications_submit_callback',
          // We pass a callback function we will use later to render the form for the user
        ],
      ];
    }
  }
  return $form;
}

/**
 * Formulario paso 1 de agregar publicación.
 */
function _publications_add_form_step_1(&$form, &$form_state, &$publication = NULL) {
  // Add Custom Concept:
  $custom_concept_add_form = drupal_get_form('custom_concept_add_form');
  $custom_concept_modal =
    '<div class="remodal" data-remodal-id="modal-concept">' .
      '<a data-remodal-action="close" class="remodal-close"></a>' .
      ' ' .
      drupal_render($custom_concept_add_form) .
    '</div>'
  ;

  // Add Autor externo
  $autor_externo_add_form = drupal_get_form('autor_externo_add_form');
  $autor_externo_modal =
    '<div class="remodal" data-remodal-id="modal-other-co-author">' .
      '<a data-remodal-action="close" class="remodal-close"></a>' .
      ' ' .
      drupal_render($autor_externo_add_form) .
    '</div>'
  ;

  $form['#suffix'] = $form['#suffix'] . $custom_concept_modal . $autor_externo_modal;

  $form['query'] = [
    '#type' => 'fieldset',
    '#title' =>
      '<i class="icon-revista"></i>' .
      ' ' .
      (isset($form_state['nid']) ? t('Edit publication') : t('Add publication')) .
      ' ' .
      '<strong>' .
        '<small>(' . t('Step') . ' #1' . ')</small>' .
      '</strong>'
    ,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  // Left content
  $form['query']['left_column'] = [
    '#type' => 'container',
    '#attributes' => [
      'class' => [
        'col-md-7',
        'bordered-left'
      ],
    ],
    '#weight' => 2,
  ];

  _publications_add_form_step_1_left_column($form, $form_state, $publication);

 // Right content
  $form['query']['right_column'] = [
    '#type' => 'container',
    '#attributes' => [
      'class' => [
        'col-md-5',
      ],
    ],
    '#weight' => 1,
  ];

  _publications_add_form_step_1_right_column($form, $form_state, $publication);

}

/**
 * Formulario paso 1 izquierda de agregar publicación.
 */
function _publications_add_form_step_1_left_column(&$form, &$form_state, &$publication = NULL) {
  $form['query']['left_column']['title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => get_input_value_from_publication($publication, 'title'),
    '#size' => 60,
    '#maxlength' => 256,
  ];

  $form['query']['left_column']['url'] = [
    '#type' => 'textfield',
    '#title' => t('Url'),
    '#default_value' => get_input_value_from_publication($publication, 'url'),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t('Source link'),
  ];

  $form['query']['left_column']['doi'] = [
    '#type' => 'textfield',
    '#title' => t('DOI'),
    '#default_value' => get_input_value_from_publication($publication, 'doi'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('DOI link'),
  ];

  $options = range(2018, 1990);
  $form['query']['left_column']['publication_year'] = [
    '#type' => 'select',
    '#title' => t('Publication year'),
    '#options' => array_combine($options, $options),
    '#default_value' => get_input_value_from_publication($publication, 'publication_year'),
    '#description' => t(''),
    '#prefix' => '',
    '#suffix' => '',
  ];

  $form['query']['left_column']['volumen'] = [
    '#type' => 'textfield',
    '#title' => t('Volumen'),
    '#default_value' => get_input_value_from_publication($publication, 'volumen'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Volumen'),
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_ARTICLE)),
        ),
      ),
    ),
  ];

  $form['query']['left_column']['number'] = [
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#default_value' => get_input_value_from_publication($publication, 'number'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Number'),
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_ARTICLE)),
          'or',
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_WORK_DOCUMENT)),
        ),
      ),
    ),
  ];

  $form['query']['left_column']['page'] = [
    '#type' => 'textfield',
    '#title' => t('Pages'),
    '#default_value' => get_input_value_from_publication($publication, 'page'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Pages'),
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_ARTICLE)),
          'or',
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_BOOK_CHAPTER)),
        ),
      ),
    ),
  ];

  $form['query']['left_column']['pub_city'] = [
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => get_input_value_from_publication($publication, 'pub_city'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('City'),
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_BOOK)),
        ),
      ),
    ),
  ];

  $form['query']['left_column']['editorial'] = [
    '#type' => 'textfield',
    '#title' => t('Editorial'),
    '#default_value' => get_input_value_from_publication($publication, 'editorial'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Editorial'),
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_BOOK)),
        ),
      ),
    ),
  ];

  // BEGIN Evidence
  $form['query']['left_column']['evidence'] = [
    '#type' => 'fieldset',
    '#title' => t('Evidence'),
    '#prefix' => '<div id="fieldset-wrapper-tags" class="fieldset-wrapper-tags margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $form['query']['left_column']['evidence']['approved_date'] = [
    '#title' => t('Approved date'),
    '#date_format' => 'Y-m-d',
    '#date_year_range' => '-30:+0',
    '#date_label_position' => '',
    '#datepicker_options' => array('maxDate' => 0),
    '#type' => 'date_popup',
    '#default_value'=> get_input_value_from_publication($publication, 'start_date'),
  ];

  $form['query']['left_column']['evidence']['file'] = array(
    '#title' => t('Attach evidence'),
    '#type' => 'managed_file',
    '#default_value' => get_input_value_from_publication($publication, 'attach_doc'),
    '#description' => t('Upload an evidence document in pdf format of your entry'),
    '#upload_location' => 'public://publications',
    "#upload_validators"  => array(
      'file_validate_extensions' => array('pdf'),
      '_file_validate_unique_pub' => array(),
    ),
  );

  // File jel form element starts
  $form['query']['left_column']['fieldset_jel'] = [
    '#type' => 'fieldset',
    '#title' => t('Clasificación JEL'),
    '#prefix' => '<div id="fieldset-wrapper-jel" class="fieldset-wrapper-jel margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        array(
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_ARTICLE)),
          'or',
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_WORK_DOCUMENT)),
          'or',
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_BOOK)),
          'or',
          array('select[name="query[right_column][pub_type]"]' => array('value' => PUB_TYPE_BOOK_CHAPTER)),
        ),
      ),
    ),
  ];

  $jel_default_values = get_input_value_from_publication($publication, 'jels');

  $form['query']['left_column']['fieldset_jel']['jel'] = [
    '#type' => 'textfield',
    '#title' => t('JEL'),
    '#size' => 30,
    '#maxlength' => 250,
    '#autocomplete_path' => 'taxonomy/autocomplete/field_jel',
    '#default_value' => $jel_default_values,
    '#prefix' => '<div class="row"><div class="col-md-12">',
    '#suffix' => '</div></div>',
    '#description' => t('List JEL codes separated by commas'),
  ];

  // BEGIN Tags - File tags form element starts
  $form['query']['left_column']['fieldset_tags'] = [
    '#type' => 'fieldset',
    '#title' => t('Keywords'),
    '#prefix' => '<div id="fieldset-wrapper-tags" class="fieldset-wrapper-tags margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $tags_default_values = get_input_value_from_publication($publication, $field_name = 'tags', '');

  $form['query']['left_column']['fieldset_tags']['tags'] = [
    '#type' => 'textfield',
    '#title' => t('Keywords'),
    '#size' => 30,
    '#maxlength' => 250,
    '#autocomplete_path' => 'taxonomy/autocomplete/field_publication_tags',
    '#default_value' => $tags_default_values,
    '#prefix' => '<div class="row"><div class="col-md-12">',
    '#suffix' => '</div></div>',
    '#description' => t('List the keywords separated by commas'),
  ];
  // END Tags

  // Idioma Alterno
  $form['query']['left_column']['alternate_language'] = array(
    '#type' =>
    'checkbox',
    '#default_value' => (get_input_value_from_publication($publication, 'title_en', FALSE)!==FALSE),
    '#title' => t('Do you want to include the information of your publication in another language? '),
  );

  $form['query']['left_column']['title_en'] = [
    '#type' => 'textfield',
    '#title' => t('Title (Altern Language)'),
    '#default_value' => get_input_value_from_publication($publication, 'title_en'),
    '#size' => 60,
    '#maxlength' => 128,
    '#states' => [
      'visible' => [
        'input[name="query[left_column][alternate_language]"]' => [
          'checked' => TRUE
        ],
      ],
    ],
  ];

}

/**
 * Validación campo file .
 */
function _file_validate_unique_pub($file) {
  $errors = array();
  $filename = $file->filename;
  if (file_exists('public://publications/' . $filename)) {
    $errors[] = t('The file could not be uploaded because a file by that name already exists in the destination directory.');
  }
  return $errors;
}

/**
 * Formulario paso 1 derecha de agregar publicación.
 */
function _publications_add_form_step_1_right_column(&$form, &$form_state, &$publication = NULL) {

  // Tipo de publicación *
  $field_pub_type = field_info_field('field_pub_type');

  $options = [];
  $options[''] = t('- Select -');
  if (isset($field_pub_type['settings']['allowed_values'])) {
    foreach ($field_pub_type['settings']['allowed_values'] as $key => $value) {
      if(PUB_TYPE_OTHER_CONCEPT != $key && PUB_TYPE_CONFERENCE_DOCUMENT != $key){
        $options[$key] = $value;
      }
    }
  }

  $form['query']['right_column']['pub_type'] = [
    '#type' => 'select',
    '#title' => t('Publication type'),
    '#options' => $options,
    '#default_value' => get_input_value_from_publication($publication, 'pub_type'),
    '#description' => t(''),
    '#prefix' => '',
    '#required' => TRUE,
    '#suffix' => '',
  ];

  // Box Para Articulo
  _get_fieldset_publication_article($form, $form_state, $publication);
  // Box Para Libro
  _get_fieldset_publication_book($form, $form_state, $publication);
  // Box Para Capítulo de libro
  _get_fieldset_publication_book_chapter($form, $form_state, $publication);
  // Box Para Documento de trabajo
  _get_fieldset_publication_work_document($form, $form_state, $publication);
  // Box Para Documento en conferencia
  _get_fieldset_publication_conference_document($form, $form_state, $publication);

  $form['query']['right_column']['rol_within_publication'] = [
    '#id' => 'rol-within-publication',
    '#type' => 'select',
    '#title' => t('Rol dentro de la Publicación'),
    '#options' => [
      '-1' => t('— Seleccionar'),
      ROL_AUTHOR_COMPLETE_TID => t('Autor libro completo'),
      ROL_BOOK_COMPILER_TID => t('Compilador de libro'),
      ROL_BOOK_EDITOR_TID => t('Editor de Libro'),
    ],
    '#default_value' => get_input_value_from_publication($publication, 'rol_within_publication', $default_value = ROL_AUTHOR_COMPLETE_TID),
    '#description' => t(''),
    '#prefix' => '<div class="row"><div class="col-md-12"><div class="roles-within-publication">',
    '#suffix' => '</div></div></div>',
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          'value' => PUB_TYPE_BOOK
        ],
      ],
    ],
  ];

  // Box Otros Autores
  _get_fieldset_other_co_author($form, $form_state, $publication);

  if (user_has_role(user_role_load_by_name('caie')->rid)) {
    $form['query']['right_column']['review'] = array(
      '#type'=>'select',
      '#title' => t('Review'),
      '#options'=> list_allowed_values(field_info_field('field_review')),
      '#default_value' => get_input_value_from_publication($publication, 'review', PUB_REVIEW_PENDING),
    );
  }
}

/**
 * Formulario paso 2 de agregar publicación.
 */
function _publications_add_form_step_2(&$form, &$form_state, &$publication = NULL) {
  $node = (object) drupal_json_decode($form_state['storage_publication']);
  // dpm($node);
  $header = [t('Information'), t('Value')];
  $rows = [];

  // Titulo
  $rows[] = [t('Title'), $node->title];
  if(isset($node->field_title_en[LANGUAGE_NONE][0]['value'])){
    $rows[] = [
      t('Title (Other Language)'),
      $node->field_title_en[LANGUAGE_NONE][0]['value'],
    ];
  }
  // Url de la publicación.
  $rows[] = [
    t('Url') . '.',
    $node->field_url[LANGUAGE_NONE][0]['url'],
  ];
  // DOI de la publicación.
  if (!empty($node->field_doi[LANGUAGE_NONE][0]['url'])) {
    $rows[] = [
      t('DOI'),
      $node->field_doi[LANGUAGE_NONE][0]['url'],
    ];
  }
  // Tipo de publicación
  $field_pub_type = field_info_field('field_pub_type');

  $options = [];
  $options[''] = '— ' . t('Select');
  if (isset($field_pub_type['settings']['allowed_values'])) {
    foreach ($field_pub_type['settings']['allowed_values'] as $key => $value) {
      $options[$key] = $value;
    }
  }
  $pub_type = '';
  if (isset($node->field_pub_type[LANGUAGE_NONE][0]['value'])) {
    $key = $node->field_pub_type[LANGUAGE_NONE][0]['value'];
    if (isset($options[$key])) {
      $pub_type = $options[$key];
    }
  }
  $rows[] = [t('Publication type'), $pub_type];

  // Fecha aceptación
  $approved_date = '';
  if (isset($node->field_act_start_date[LANGUAGE_NONE][0]['value'])) {
    $approved_date = $node->field_act_start_date[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($approved_date)) {
    $rows[] = [t('Approved date'), $approved_date];
  }

  // Año de publicación
  $publication_year = '';
  if (isset($node->field_publication_year[LANGUAGE_NONE][0]['value'])) {
    $publication_year = $node->field_publication_year[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($publication_year)) {
    $rows[] = [t('Year'), $publication_year];
  }

  // Volumen
  $volumen = '';
  if (isset($node->field_volumen[LANGUAGE_NONE][0]['value'])) {
    $volumen = $node->field_volumen[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($volumen)) {
    $rows[] = [t('Volumen'), $volumen];
  }

  // Number
  $number = '';
  if (isset($node->field_number[LANGUAGE_NONE][0]['value'])) {
    $number = $node->field_number[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($number)) {
    $rows[] = [t('Number'), $number];
  }

  // Page
  $page = '';
  if (isset($node->field_page[LANGUAGE_NONE][0]['value'])) {
    $page = $node->field_page[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($page)) {
    $rows[] = [t('Page'), $page];
  }

  // Editorial
  $editorial = '';
  if (isset($node->field_editorial[LANGUAGE_NONE][0]['value'])) {
    $editorial = $node->field_editorial[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($editorial)) {
    $rows[] = [t('Editorial'), $editorial];
  }

  // City
  $city = '';
  if (isset($node->field_pub_city[LANGUAGE_NONE][0]['value'])) {
    $city = $node->field_pub_city[LANGUAGE_NONE][0]['value'];
  }
  if (!empty($city)) {
    $rows[] = [t('City'), $city];
  }

  // Clasificación JEL
  $jels = [];
  if (isset($node->jels) && is_array($node->jels) && !empty($node->jels)) {
    $jels = $node->jels;
  }
  if (!empty($jels)) {
    $rows[] = [t('JEL Classification'), implode(".<br/>", $jels)];
  }

  // Etiquetas
  $tags = [];
  if (isset($node->tags) && is_array($node->tags) && !empty($node->tags)) {
    $tags = $node->tags;
  }
  if (!empty($tags)) {
    $rows[] = [t('Tags'), implode(" | ", $tags)];
  }

  // Concepto de la publicación.
  $concept_type_key = isset($node->concept_type) ? $node->concept_type : '';
  $concepts_types = get_concepts_type_options();
  $concept_type = '';
  if (isset($concepts_types[$concept_type_key])) {
    $concept_type = t('Type') . ': ' . $concepts_types[$concept_type_key];
  }
  // Nombre del Concepto.
  $concept_name = '';
  if (isset($node->concept_name)) {
    $concept_name = $node->concept_name;
  }
  if (!empty($concept_name)) {
    $concept = [$concept_type, $concept_name];
    $rows[] = [t('Publication Concept'), $concept_name];
  }

  // Rol dentro de la Publicación
  $role_within_publication = '';
  $roles = get_roles_within_publication();
  $role_within_publication_tid = '';
  if(isset($node->field_role_within_publication['und'][0]['tid'])){
    $role_within_publication_tid = $node->field_role_within_publication['und'][0]['tid'];
    $role_within_publication = isset($roles[$role_within_publication_tid])?$roles[$role_within_publication_tid]:'';
  }

  if(!empty($role_within_publication)){
    $rows[] = array(t('Publication Role'), $role_within_publication);
  }

  // Coautores Banco.
  $co_authors = [];
  $label = t('Book author');
  if(!empty($role_within_publication_tid)){
    switch ($role_within_publication_tid) {
      case ROL_CHAPTER_AUTHOR_TID:
        $label = t('Chapter authors');
        break;
      case ROL_AUTHOR_COMPLETE_TID:
        $label = t('Book author');
        break;
      case ROL_BOOK_EDITOR_TID:
        $label = t('Book Publishers');
        break;
      case ROL_BOOK_COMPILER_TID:
        $label = t('Book Compilers');
        break;
    }
  }
  $_main_author_reference = $node->main_author_reference[0]['name'];
  $_authors = [];
  if (isset($node->co_authors) && is_array($node->co_authors) && !empty($node->co_authors)) {
    foreach ($node->co_authors as $key => $co_author) {
      if (isset($co_author['name'])) {
        if (!$_main_author_reference) {
          $_main_author_reference = $co_author['name'];
        }
        else{
          $_authors[] =  $co_author['name'];
        }
      }
    }
  }
  $rows[] = array(t('Main author'), $_main_author_reference);
  if (!empty($_authors)) {
    $rows[] = array(t("Bank's Co-authors"), implode(' <br/> ', $_authors));
  }

  // Otros Coautores
  $other_co_authors = [];
  if (isset($node->other_co_authors) && is_array($node->other_co_authors) && !empty($node->other_co_authors)) {
    $other_co_authors = $node->other_co_authors;
  }
  if (!empty($other_co_authors)) {
    $rows[] = [t('Other Co-authors (externals)'), implode(' <br/> ', $other_co_authors)];
  }

  if (user_has_role(user_role_load_by_name('caie')->rid)) {
    $options = list_allowed_values(field_info_field('field_review'));
    $rows[] = [t('Review'), $options[$node->field_review[LANGUAGE_NONE][0]['value']]];
  }

  $table = theme('table', ['header' => $header, 'rows' => $rows]);

  $form['query'] = [
    '#type' => 'fieldset',
    '#title' =>
      '<i class="icon-revista"></i>' .
      ' ' .
      t('Add Publication') .
      ' ' .
      '<strong>' .
        '<small>(Paso número #2)</small>' .
      '</strong>'
    ,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $form['query']['header'] = [
    '#markup' =>
      '<h3 class="confirm-registered-information">' .
        t('Confirma la información registrada') .
      '</h3>' .
      '<div class="row">' .
        '<div class="confirm-registered-information-wrapper col-md-12">' .
          $table .
        '</div>' .
      '</div>'
    ,
  ];
}

/**
 * Formulario paso 3 de agregar publicación.
 */
function _publications_add_form_step_3(&$form, &$form_state, &$publication = NULL) {
  $node = (object) drupal_json_decode($form_state['storage_publication']);
  $msg = t('');
  if (isset($node->nid)) {
    $msg = t('Your publication has been successfully saved and is now in approval process!.');
    $form_state['storage_publication'] = [];
  }
  else {
    $msg = t('An error occurred while saving the publication, please try again!');
  }

  $form['query'] = [
    '#type' => 'fieldset',
    '#title' => '<i class="icon-revista"></i> ' . t('Add Publication') . ' <strong><small>(' . t('Publication Saved!') . ')</small></strong>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $form['query']['header'] = [
    '#markup' => '<h3 class="confirm-registered-information">' . t('Confirm registered information') . '</h3><div class="row"><div class="confirm-registered-information-wrapper col-md-12"><p class="info">' . $msg . '</p></div></div>',
  ];
}

/**
 * Ajax callback función que definimos en todos nuestros botones (atrás,
 * adelante y enviar). devuelve el formulario completo cada vez que se
 * llama a la función. Esta permite nuestros múltiples pasos.
 */
function _ajax_multistep_form_publications_submit_callback($form, &$form_state) {
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
function _ajax_multistep_form_publications_back_submit($form, &$form_state) {
  $form_state['step']--;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit formulario de agregar publicación
 */
function publications_add_form_submit($form, &$form_state) {
  $step = $form_state['step'];
  if (isset($form_state['values']['buttons']['forward']) && $form_state['values']['op'] == $form_state['values']['buttons']['forward']) {
    $form_state['step'] = $step + 1;
  }
  elseif (isset($form_state['values']['buttons']['submit']) && $form_state['values']['op'] == $form_state['values']['buttons']['submit']) {
    $form_state['step'] = 3;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Validador formulario de agregar publicación
 */
function publications_add_form_validate($form, &$form_state) {
  // First we set up a switch for each of our three steps
  $response = new stdClass();
  $response->success = FALSE;
  $response->is_valid = TRUE;
  $response->msg = '';
  switch ($form_state['step']) {
    case 1:
      publications_add_form_validate_step_1($form, $form_state, $response);
      break;
    case 2:
      publications_add_form_validate_step_2($form, $form_state, $response);
      break;
  }
}

/**
 * Validador paso 1 formulario de agregar publicación
 */
function publications_add_form_validate_step_1($form, &$form_state, &$response) {

  // Get the form values
  $values_left_column = isset($form_state['values']['query']["left_column"]) ? $form_state['values']['query']["left_column"] : [];
  $values_right_column = isset($form_state['values']['query']["right_column"]) ? $form_state['values']['query']["right_column"] : [];
  $values = array_merge($values_left_column, $values_right_column);

  // Title
  $title = isset($values['title']) ? $values['title'] : FALSE;
  if ($title == FALSE) {
    form_set_error('query[left_column][title]', t('Title is required.'));
    $response->is_valid = FALSE;
  }

  // Idioma Alterno
  $alternate_language = isset($values['alternate_language']) ? $values['alternate_language'] : FALSE;
  $title_en = FALSE;
  if($alternate_language){
    // Título (Idioma alternativo)
    $title_en = isset($values['title_en']) ? $values['title_en'] : FALSE;
  }

  // Publication year
  $publication_year = isset($values['publication_year']) ? $values['publication_year'] : FALSE;
  if ($publication_year == FALSE) {
    form_set_error('query[left_column][publication_year]', t('Publication Year is required'));
    $response->is_valid = FALSE;
  }
  // Fecha aceptación
  $start_date = isset($values['evidence']['approved_date']) ? $values['evidence']['approved_date'] : FALSE;
  // Soporte pdf
  if($values['evidence']['file']){
    $file = file_load($values['evidence']['file']);
    $file->filename = $file->fid . '-' . time();
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'banrep_investigador', 'node', 4);
  }
  else {
  }

  // Volumen
  $volumen = isset($values['volumen']) ? $values['volumen'] : FALSE;
  // Number
  $number = isset($values['number']) ? $values['number'] : FALSE;
  // Page
  $page = isset($values['page']) ? $values['page'] : FALSE;
  if ($page != FALSE) {
    if (!preg_match('/^\d+(-\d+)?$/', $page)) {
      form_set_error(
        'query[left_column][page]',
        t('Pages must be numeric, with a possible dash to denote a range')
      );
      $response->is_valid = FALSE;
    }
  }

  // Editorial
  $editorial = isset($values['editorial']) ? $values['editorial'] : FALSE;
  // City
  $city = isset($values['pub_city']) ? $values['pub_city'] : FALSE;

  // Url
  $url = isset($values['url']) ? $values['url'] : FALSE;
  if ($url == FALSE) {
    form_set_error('query[left_column][url]', t('URL is required'));
    $response->is_valid = FALSE;
  }
  // DOI
  $doi = isset($values['doi']) ? $values['doi'] : FALSE;
  // Ingresar tipo de publicación.
  $pub_type = isset($values['pub_type']) ? $values['pub_type'] : FALSE;
  if ($pub_type == FALSE) {
    form_set_error('query[right_column][pub_type]', t('Publication type is required'));
    $response->is_valid = FALSE;
  }

  // Rol dentro de la Publicación
  $rol_within_publication = isset($values['rol_within_publication']) ? $values['rol_within_publication'] : FALSE;

  // Concept type
  $concept_target_id = '';
  $concept_name = '';
  $concept_name_field = '';
  $concept_type = NULL;
  $subtype = '';
  switch ($pub_type) {
    case PUB_TYPE_ARTICLE:
      $concept_type = (
        isset($values['fieldset_publication_articulos']['concept_type']) ?
        $values['fieldset_publication_articulos']['concept_type'] :
        $concept_type
      );
      if (!empty($concept_type)) {
        $concept_id = 'article_'.$concept_type;
        $concept_name_field =
          'query[right_column][fieldset_publication_articulos]['.$concept_id.']'
        ;
        $concept_name = (
          isset($values['fieldset_publication_articulos'][$concept_id]) ?
          $values['fieldset_publication_articulos'][$concept_id] :
          $concept_name
        );
      }
      $rol_within_publication = ROL_AUTHOR_COMPLETE_TID;
      break;
    case PUB_TYPE_BOOK:
      $concept_type = (
        isset($values['fieldset_publication_books']['concept_type']) ?
        $values['fieldset_publication_books']['concept_type'] :
        $concept_type
      );
      break;
    case PUB_TYPE_BOOK_CHAPTER:
      $concept_type = (
        isset($values['fieldset_publication_book_chapters']['concept_type']) ?
        $values['fieldset_publication_book_chapters']['concept_type'] :
        $concept_type
      );
      if ($concept_type) {
        $concept_id = 'book_chapter_'.$concept_type;
        $concept_name_field =
          'query[right_column][fieldset_publication_book_chapters]['.$concept_id.']'
        ;
        $concept_name = (
          isset($values['fieldset_publication_book_chapters'][$concept_id]) ?
          $values['fieldset_publication_book_chapters'][$concept_id] :
          $concept_name
        );
      }
      $rol_within_publication = ROL_CHAPTER_AUTHOR_TID;
      break;
    case PUB_TYPE_WORK_DOCUMENT:
      $concept_target_id = (
        isset($values['fieldset_publication_work_documents']["work_document"]) ?
        $values['fieldset_publication_work_documents']["work_document"] :
        FALSE
      );
      $concept_type = 2951;
      $concept_name = get_node_title($concept_target_id);
      $rol_within_publication = ROL_AUTHOR_COMPLETE_TID;
      break;
    case PUB_TYPE_CONFERENCE_DOCUMENT:
      $concept_type = (
        isset($values['fieldset_publication_conference_documents']['concept_type']) ?
        $values['fieldset_publication_conference_documents']['concept_type'] :
        $concept_type
      );
      if ($concept_type) {
        $concept_id = 'conference_document_'.$concept_type;
        $concept_name_field =
          'query[right_column][fieldset_publication_conference_documents]['.$concept_id.']'
        ;
        $concept_name = (
          isset($values['fieldset_publication_conference_documents'][$concept_id]) ?
          $values['fieldset_publication_conference_documents'][$concept_id] :
          $concept_name
        );
      }
      $rol_within_publication = ROL_AUTHOR_COMPLETE_TID;
      break;
  }

  if ($concept_name_field && empty($concept_name)) {
    form_set_error($concept_name_field, t('El nombre de la publicación es requerido'));
    $response->is_valid = FALSE;
  }

  // Clasificación JEL
  $jels = isset($values['fieldset_jel']['jel']) ? $values['fieldset_jel']['jel'] : [];
  $jel_tids = [];
  if (!empty($jels)) {
    $jels_array = explode(',', $jels);
    foreach ($jels_array as $key => $jel) {
      $jel_tid = _get_jel_by_name($jel);
      if ($jel_tid) {
        $jel_tids[] = ['tid' => $jel_tid];
      }else{
        unset($jels[$key]);
      }
    }
  }
  // Palabras clave
  $tags = isset($values['fieldset_tags']['tags']) ? $values['fieldset_tags']['tags'] : '';
  $tag_tids = [];
  if (!empty($tags)) {
    $tags_array = explode(',', $tags);
    foreach ($tags_array as $key => $tag) {
      $tag_tid = _get_tag_by_name($tag);
      if ($tag_tid) {
        $tag_tids[] = ['tid' => $tag_tid];
      }
    }
  }

  // Autores
  $co_authors_author = (
    isset($values['co_author_fieldset']['co_authors_author']) ?
    $values['co_author_fieldset']['co_authors_author'] :
    []
  );

  $co_authors = [];
  $main_author_reference = NULL;
  $other_co_authors = [];
  $main_author = TRUE;
  foreach ($co_authors_author as $key => $name) {
    if (!empty($name)) {
      // if (_is_registered_user_by_name($name)) {
        $target_uid = _get_co_author_uid_by_name($name);
        if (count($target_uid) > 0) {
          if ($main_author) {
            $main_author_arr[] = [
              'tid' => $target_uid['tid'],
              'uid' => $target_uid['uid'],
              'name' => $name,
              'main' => TRUE,
              'rid' => $rol_within_publication
            ];
            $main_author_reference = get_term_name_by_tid($target_uid['tid']) . '(' . $target_uid['tid'] . ')';
            $main_author_reference_tid = $target_uid['tid'];
          } else {
            $co_authors[] = [
              'tid' => $target_uid['tid'],
              'uid' => $target_uid['uid'],
              'name' => $name,
              'main' => $main_author,
              'rid' => $rol_within_publication
            ];
          }
        }
      // }
      $main_author = FALSE;
    }
  }


  // Validations
  if ((!is_valid_rol_within_publication($rol_within_publication))) {
    $response->msg = t('Rol Publication is not valid');
    $response->is_valid = FALSE;
    form_set_error(NULL, $response->msg);
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
      $node->type = 'publication';  // Content type
      $node->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
      node_object_prepare($node);  //Set some default values
      $node->status = 0;   // (1 or 0): published or unpublished
      $node->promote = 0;  // (1 or 0): promoted to front page or not
      $node->sticky = 0;  // (1 or 0): sticky at top of lists or not
      $node->comment = 0;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
      if (isset($form_state['nid'])) {
        $node->nid = $form_state['nid'];
      }
    }
    $node->uid = $user->uid;
    $node->title = $title;

    if($alternate_language){
      $node->field_title_en[LANGUAGE_NONE][0]['value'] = $title_en;
    }
    else{
      $node->field_title_en[LANGUAGE_NONE] = NULL;
      $node->field_body_en[LANGUAGE_NONE] = NULL;
    }
    $node->field_url[LANGUAGE_NONE][0]['url'] = $url;
    $node->field_doi[LANGUAGE_NONE][0]['url'] = $doi;
    $node->field_publication_year[LANGUAGE_NONE][0]['value'] = $publication_year;
    $node->field_volumen[LANGUAGE_NONE][0]['value'] = $volumen;
    $node->field_number[LANGUAGE_NONE][0]['value'] = $number;
    $node->field_page[LANGUAGE_NONE][0]['value'] = (
      empty($page) ?
      NULL :
      $page
    );
    $node->field_editorial[LANGUAGE_NONE][0]['value'] = $editorial;
    $node->field_pub_city[LANGUAGE_NONE][0]['value'] = $city;
    $node->field_concept_type[LANGUAGE_NONE][0]['tid'] = $concept_type;
    if(!empty($concept_target_id)){
      $node->field_concept[LANGUAGE_NONE][0]['target_id'] = $concept_target_id;
    }else{
      $concept_target_id = _get_scoring_concept_by_name($concept_name);
      if ($concept_target_id) {
        $node->field_concept[LANGUAGE_NONE][0]['target_id'] = $concept_target_id;
      }
    }

    $node->field_act_date_start[LANGUAGE_NONE][0]['value'] = (
      empty($start_date) ?
      NULL :
      strtotime($start_date)
    );
    if (!empty($file)) {
      $node->field_re_attach_doc[LANGUAGE_NONE][0] = (array)$file;
    }
    $node->field_re_attach_doc[LANGUAGE_NONE][0]['display'] = 1;

    $node->field_order[LANGUAGE_NONE][0]['value'] = 0;
    $node->field_jel[LANGUAGE_NONE] = $jel_tids;
    $node->field_publication_tags[LANGUAGE_NONE] = $tag_tids;
    if ($rol_within_publication != FALSE && $rol_within_publication != '-1') {
      $node->field_role_within_publication[LANGUAGE_NONE][0]['tid'] =
        $rol_within_publication
      ;
    }
    $node->field_pub_type[LANGUAGE_NONE][0]['value'] = $pub_type;
    $node->field_date[LANGUAGE_NONE][0]['value'] = time();
    //$node->field_estado_publicaci_n[LANGUAGE_NONE][0]['value'] = 2; // Pendiente Aprobación
    if ($main_author_reference !== NULL) {
      $node->field_main_author_reference[LANGUAGE_NONE][0]['tid'] = $main_author_arr[0]['tid'];
      if (empty($node->field_main_author_reference[LANGUAGE_NONE][0]['tid'])) {
        $response->is_valid = FALSE;
        form_set_error(
          '',
          t(
            'Author "@author" doesn\'t exist',
            array(
              '@author' => $main_author_arr[0]['name']
            )
          )
        );
      }
    }
    else {
      $node->field_main_author_reference = array();
    }
    // Autores
    $field_other_co_authors = [];
    foreach ($co_authors as $key => $other_co_author) {
      if($main_author_arr[0]['tid'] != $other_co_author['tid']){
        $other_co_author_tid = $other_co_author['tid'];
        $field_other_co_authors[] = ['tid' => $other_co_author_tid];
        if (empty($other_co_author_tid)) {
          $response->is_valid = FALSE;
          form_set_error(
            '',
            t(
              'Author "@author" doesn\'t exist',
              array(
                '@author' => $other_co_author
              )
            )
          );
        }
      }
    }
    $node->field_other_co_authors[LANGUAGE_NONE] = $field_other_co_authors;
    if (user_has_role(user_role_load_by_name('caie')->rid)) {
      $node->field_review[LANGUAGE_NONE][0]['value'] = (
        isset($values['review']) ?
        $values['review'] :
        PUB_REVIEW_PENDING
      );
      if ($node->field_review[LANGUAGE_NONE][0]['value'] === PUB_REVIEW_REVIEWED) {
        module_load_include('int', 'banrep_core', 'banrep_core.functions');
        _banrep_core_validate_external_authors($node);
      }
    }
    else {
      $node->field_review[LANGUAGE_NONE][0]['value'] = PUB_REVIEW_PENDING; // Pendiente revisión
    }

    // BEGIN Additional Info.
    $node->jels = $jels;
    $node->tags = $tags;
    $node->co_authors = $co_authors;
    $node->main_author_reference = $main_author_arr;
    // $node->other_co_authors = $other_co_authors;
    $node->concept_target_id = $concept_target_id;
    $node->concept_name = $concept_name;
    $node->concept_type = $concept_type;
    $node->alternate_language = $alternate_language;
    // END Additional Info.
    $publication = drupal_json_encode($node);
    $form_state['storage_publication'] = $publication;
  }
}

/**
 * Validador paso 2 formulario de agregar publicación.
 */
function publications_add_form_validate_step_2($form, &$form_state, &$response) {
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
      $main_author_ref = isset($node->main_author_reference) ? $node->main_author_reference : [];
      $co_authors = isset($node->co_authors) ? $node->co_authors : [];
      unset($node->co_authors);
      unset($node->alternate_language);
      unset($node->jels);
      unset($node->tags);
      unset($node->main_author_reference);
      unset($node->other_co_authors);
      unset($node->concept_target_id);
      unset($node->concept_name);
      unset($node->concept_type);
      if (isset($node->nid) && !isset($node->vid)) {
        $node->vid = $node->nid;
      }
      node_save($node);
      if (isset($node->nid)) {
        $co_authors = array_merge($main_author_ref, $co_authors);
        _publication_create_co_authors_banco($node->nid, $co_authors);
      }
      $form_state['storage_publication'] = drupal_json_encode($node);
    }
    else {
      form_set_error(NULL, t('Complete los pasos anteriores!.'));
      $response->is_valid = FALSE;
    }
  }
}

/**
 * Obtener fieldset tags.
 */
function _get_fieldset_tags(&$form, &$form_state, &$publication = NULL) {

  if (empty($form_state['num_tags'])) {
    $form_state['num_tags'] = 1;
  }

  $count_tags = $form_state['num_tags'];
  $multiple_tags = ($count_tags > 1);

  // File tags form element starts
  $form['query']['left_column']['fieldset_tags'] = [
    '#type' => 'fieldset',
    '#title' => t('Etiquetas'),
    '#prefix' => '<div id="fieldset-wrapper-tags" class="fieldset-wrapper-tags margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];

  $default_values = get_input_value_from_publication($publication, $field_name = 'tags', []);

  for ($i = 0; $i < $count_tags; $i++) {
    $form['query']['left_column']['fieldset_tags']['tags'][$i] = [
      '#type' => 'textfield',
      '#title' => t('Etiqueta'),
      '#size' => 30,
      '#maxlength' => 250,
      '#autocomplete_path' => 'taxonomy/autocomplete/field_publication_tags',
      '#default_value' => isset($default_values[$i]) ? $default_values[$i] : '',
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    ];
  }

  $form['query']['left_column']['fieldset_tags']['add_tags'] = [
    '#type' => 'submit',
    '#value' => t('Add tag'),
    '#submit' => ['tags_add_more_callback'],
    '#limit_validation_errors' => [],
    '#ajax' => [
      'callback' => 'tags_callback',
      'wrapper' => 'fieldset-wrapper-tags',
    ],
  ];

  // Remove
  if ($multiple_tags) {
    $form['query']['left_column']['fieldset_tags']['remove_tags'] = [
      '#type' => 'submit',
      '#value' => t('Eliminar Etiqueta'),
      '#submit' => ['tags_remove_one_callback'],
      '#limit_validation_errors' => [],
      '#ajax' => [
        'callback' => 'tags_callback',
        'wrapper' => 'fieldset-wrapper-tags',
      ],
    ];
  }
}

/**
 * Obtener fieldset publicación artículo.
 */
function _get_fieldset_publication_article(&$form, &$form_state, &$publication = NULL) {
  // Field article form element starts
  $form['query']['right_column']['fieldset_publication_articulos'] = [
    '#type' => 'fieldset',
    '#title' => t('Tipo de acumulado'),
    '#prefix' =>
      '<div' .
      ' id="fieldset-wrapper-article"' .
      ' class="fieldset-wrapper-fieldset-publication-articulos margin-fieldset"' .
      '>'
    ,
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          'value' => PUB_TYPE_ARTICLE
        ],
      ],
    ],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $concept_type = _banrep_core_get_concept_type($publication->field_concept[LANGUAGE_NONE][0]['target_id']);
  $_articles_type_options = get_articles_type_options();
  $form['query']['right_column']['fieldset_publication_articulos']['concept_type'] = [
    '#type' => 'select',
    '#title' => t(''),
    '#options' => $_articles_type_options,
    '#default_value' => $concept_type,
    '#description' => t(''),
    '#attributes' => [],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $last_key = '';
  foreach ($_articles_type_options as $key => $label) {
    $form['query']['right_column']['fieldset_publication_articulos']['article_' . $key] = [
      '#type' => 'textfield',
      '#title' => t('Nombre de la Revista'),
      '#default_value' => (
        $concept_type == $key ?
        get_input_value_from_publication($publication, 'concept_name') :
        ''
      ),
      '#description' => t(''),
      '#autocomplete_path' => 'article/autocomplete/' . PUB_TYPE_ARTICLE . '/' . $key,
      '#size' => 46,
      '#maxlength' => 300,
      '#prefix' => '',
      '#suffix' => '',
      '#states' => [
        'required' => [
          'select[name="query[right_column][fieldset_publication_articulos][concept_type]"]' => [
            'value' => $key
          ],
        ],
        'visible' => [
          'select[name="query[right_column][fieldset_publication_articulos][concept_type]"]' => [
            'value' => $key
          ],
        ],
      ],
      '#attributes' => [
        'class' => [ 'query-article-name' ],
      ],
    ];
    $last_key = $key;
  }
  $help =
    '<small>' .
      '<ul>' .
        '<li>' .
          '<strong>Tipo 1</strong>:' .
          ' Que se encuentran incluidas en el índice ISI (Economics, Finance, Business and' .
          ' Finance, Mathematical Methods, Statistics and Probability). - Vigente a partir' .
          ' del 1° de julio de 2013' .
        '</li>' .
        '<li>' .
          '<strong>Tipo 2</strong>:' .
          ' Scopus (Economics, Econometrics, Finance, Statistics and Probability) y Colciencias' .
          ' A1 y A2. - Vigente a partir del 1° de julio de 2013' .
        '</li>' .
        '<li>' .
          '<strong>Tipo 3</strong>:' .
          ' Colciencias B y C, Proceedings de seminarios internacionales reconocidos y revistas' .
          ' académicas internacionales no indexadas, como por ejemplo Monetaria y Money Affairs' .
          ' (CEMLA) y Economía (LACEA). Así como la Revista del Banco de la República' .
        '</li>' .
        '<li>' .
          '<strong>Tipo 4</strong>:' .
          ' Artículo en revista nacional institucional no indexada (ej. Economía Colombiana).' .
        '</li>' .
      '</ul>' .
    '</small>'
  ;
  if (!empty($last_key)) {
    $form['query']['right_column']['fieldset_publication_articulos']['article_' . $last_key]['#suffix'] = $help;
  }

  $form['query']['right_column']['fieldset_publication_articulos']['close_article'] = [
    '#markup' =>
      '<a' .
      ' href="javascript:void(0);"' .
      ' data-remodal-target="modal-concept"' .
      ' class="add-dialog references-dialog-activate"' .
      '>' .
        ' + ' .
        t('Add magazine') .
      '</a>'
    ,
  ];
}

/**
 * Obtener fieldset Publicaciones tipo Libro.
 */
function _get_fieldset_publication_book(&$form, &$form_state, &$publication = NULL) {
  // Field book form element starts
  $form['query']['right_column']['fieldset_publication_books'] = [
    '#type' => 'fieldset',
    '#title' => t('Tipo de acumulado'),
    '#prefix' =>
      '<div' .
      ' id="fieldset-wrapper-book"' .
      ' class="fieldset-wrapper-fieldset-publication-books margin-fieldset"' .
      '>'
    ,
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          'value' => PUB_TYPE_BOOK
        ],
      ],
    ],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $form['query']['right_column']['fieldset_publication_books']['concept_type'] = [
    '#type' => 'select',
    '#title' => t(''),
    '#options' => get_books_type_options(),
    '#default_value' => get_input_value_from_publication($publication, 'concept_type', -1),
    '#description' => t(''),
    '#attributes' => [],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $help =
    '<small>' .
      '<ul>' .
        '<li>' .
          '<strong>Tipo A</strong>:'.
          ' Publicados en el extranjero con editoriales que en el momento de su publicación' .
          ' figuren en el Book Citation Index, en el SPI, Ranking General (Índice ICEE del' .
          ' Consejo Superior de Publicaciones Científicas).' .
        '</li>' .
        '<li>' .
          '<strong>Tipo B</strong>:'.
          ' Publicados con organismos multilaterales, bancos centrales diferentes al Banco de' .
          ' la República, y libros de la agenda de investigación de la Gerencia Técnica del BR.' .
        '</li>' .
        '<li>' .
          '<strong>Tipo C</strong>:' .
          ' Otros' .
        '</li>
      </ul>' .
    '</small>'
  ;
  $form['query']['right_column']['fieldset_publication_books']['close_book'] = [
    '#markup' =>
      $help .
      ''
    ,
  ];
}

/**
 * Obtener fieldset Publicaciones tipo Compilador de libro.
 */
function _get_fieldset_publication_book_chapter(&$form, &$form_state, &$publication = NULL) {
  // Field book_chapter form element starts
  $form['query']['right_column']['fieldset_publication_book_chapters'] = [
    '#type' => 'fieldset',
    '#title' => t('Tipo de acumulado'),
    '#prefix' =>
      '<div' .
      ' id="fieldset-wrapper-book_chapter"' .
      ' class="fieldset-wrapper-fieldset-publication-book_chapters margin-fieldset"' .
      '>'
    ,
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          'value' => PUB_TYPE_BOOK_CHAPTER
        ],
      ],
    ],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $concept_type = get_input_value_from_publication($publication, 'concept_type', -1);
  $_books_type_options = get_books_type_options();
  $form['query']['right_column']['fieldset_publication_book_chapters']['concept_type'] = [
    '#type' => 'select',
    '#title' => t(''),
    '#options' => $_books_type_options,
    '#default_value' => $concept_type,
    '#description' => t(''),
    '#attributes' => [],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $help =
    '<small>' .
      '<ul>' .
        '<li>' .
          '<strong>Tipo A</strong>:' .
          ' Publicados en el extranjero con editoriales que en el momento de su publicación' .
          ' figuren en el Book Citation Index, en el SPI, Ranking General (Índice ICEE del' .
          ' Consejo Superior de Publicaciones Científicas).' .
        '</li>' .
        '<li>' .
          '<strong>Tipo B</strong>:' .
          ' Publicados con organismos multilaterales, bancos centrales diferentes al Banco de' .
          ' la República, y libros de la agenda de investigación de la Gerencia Técnica del BR.' .
        '</li>' .
        '<li>' .
          '<strong>Tipo C</strong>:' .
          ' Otros' .
        '</li>' .
      '</ul>' .
    '</small>'
  ;
  $form['query']['right_column']['fieldset_publication_book_chapters']['close_book'] = [
    '#markup' => $help,
  ];
  foreach ($_books_type_options as $key => $label) {
    $form['query']['right_column']['fieldset_publication_book_chapters']['book_chapter_' . $key] = [
      '#type' => 'textfield',
      '#title' => t('Nombre del Libro'),
      '#default_value' => (
        $concept_type == $key ?
        get_input_value_from_publication($publication, 'concept_name') :
        ''
      ),
      '#description' => t(''),
      '#autocomplete_path' => 'book_chapter/autocomplete/' . PUB_TYPE_BOOK . '/' . $key,
      '#size' => 46,
      '#maxlength' => 300,
      '#prefix' => '',
      '#suffix' => '',
      '#states' => [
        'required' => [
          'select[name="query[right_column][fieldset_publication_book_chapters][concept_type]"]' => [
            'value' => $key
          ],
        ],
        'visible' => [
          'select[name="query[right_column][fieldset_publication_book_chapters][concept_type]"]' => [
            'value' => $key
          ],
        ],
      ],
      '#attributes' => [
        'class' => [ 'query-book-chapter-name' ],
      ],
    ];
  }
  $help = '';
  if(!empty($last_key)){
    $form['query']['right_column']['fieldset_publication_book_chapters']['book_chapter']['#suffix'] =
      $help
    ;
  }
  $form['query']['right_column']['fieldset_publication_book_chapters']['close_book_chapter'] = [
    '#markup' =>
      '<a' .
      ' href="javascript:void(0);"' .
      ' data-remodal-target="modal-concept"' .
      ' class="add-dialog references-dialog-activate"' .
      '>' .
        ' + ' .
        t('Add book') .
      '</a>'
    ,
  ];
}

/**
 * Obtener fieldset Publicaciones tipo Documento de trabajo.
 */
function _get_fieldset_publication_work_document(&$form, &$form_state, &$publication = NULL) {
  // Field work_document form element starts
  $form['query']['right_column']['fieldset_publication_work_documents'] = [
    '#type' => 'fieldset',
    '#title' => t('Tipo de acumulado'),
    '#prefix' =>
      '<div' .
      ' id="fieldset-wrapper-work_document"' .
      ' class="fieldset-wrapper-fieldset-publication-work_documents margin-fieldset"' .
      '>'
    ,
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          'value' => PUB_TYPE_WORK_DOCUMENT
        ],
      ],
    ],
  ];
  $form['query']['right_column']['fieldset_publication_work_documents']['work_document'] = [
    '#type' => 'select',
    '#title' => t(''),
    '#default_value' => get_input_value_from_publication($publication, 'concept_target_id'),
    '#description' => t(''),
    '#options' => get_work_document_type_options(),
    '#prefix' =>
      '<div class="work_document-wrapper">' .
        '<ul class="list-inline">' .
          '<li class="item-title">' .
            '<label for="edit-work_document_type">' .
              t('Name of the series of working papers') .
              ' ' .
              '<span class="form-required" title="Este campo es obligatorio.">' .
                '*' .
              '</span>' .
            '</label>' .
          '</li>' .
          '<li id="work_document_name">'
    ,
    '#suffix' =>
          '</li>' .
        '</ul>' .
      '</div>'
    ,
    '#attributes' => [
      'class' => [ 'query-work-document-name' ],
    ],
  ];
  $help = '';
  if (!empty($last_key)) {
    $form['query']['right_column']['fieldset_publication_work_documents']['work_document']['#suffix'] =
      $help
    ;
  }
  $form['query']['right_column']['fieldset_publication_work_documents']['close_work_document'] = [
    '#markup' =>
      '<a' .
      ' href="javascript:void(0);"' .
      ' data-remodal-target="modal-concept"' .
      ' class="add-dialog references-dialog-activate"' .
      '>' .
        ' + ' .
        t('Add work documents series') .
      '</a>'
    ,
  ];
}

/**
 * Obtener fieldset Publicaciones tipo Documento en conferencia.
 */
function _get_fieldset_publication_conference_document(&$form, &$form_state, &$publication = NULL) {

  // Field conference_document form element starts
  $form['query']['right_column']['fieldset_publication_conference_documents'] = [
    '#type' => 'fieldset',
    '#title' => t('Conference Information'),
    '#prefix' => '<div id="fieldset-wrapper-conference_document" class="fieldset-wrapper-fieldset-publication-conference_documents margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => ['value' => PUB_TYPE_CONFERENCE_DOCUMENT],
      ],
    ],
    '#prefix' => '',
    '#suffix' => '',
  ];

  $conference_document_type = -1;
  $_conference_document_type_options = get_conference_documents_type_options();
  $concept_type = get_input_value_from_publication($publication, 'concept_type', $conference_document_type);
  $form['query']['right_column']['fieldset_publication_conference_documents']['conference_document_type'] = [
    '#type' => 'select',
    '#title' => t('Conference type'),
    '#options' => $_conference_document_type_options,
    '#default_value' => $concept_type,
    '#description' => t(''),
    '#attributes' => [
      'class' => [],
    ],
    '#prefix' => '',
    '#suffix' => '',
  ];
  $last_key = '';
  foreach ($_conference_document_type_options as $key => $label) {
    $form['query']['right_column']['fieldset_publication_conference_documents']['conference_document_' . $key] = [
      '#type' => 'textfield',
      '#title' => t('Conference name'),
      '#default_value' => ($concept_type == $key)?get_input_value_from_publication($publication, 'concept_name'):'',
      '#description' => t(''),
      '#autocomplete_path' => 'conference_document/autocomplete/' . PUB_TYPE_CONFERENCE_DOCUMENT . '/' . $key,
      '#size' => 46,
      '#maxlength' => 300,
      '#prefix' => '',
      '#suffix' => '',
      '#states' => [
        'visible' => [
          'select[name="query[right_column][fieldset_publication_conference_documents][conference_document_type]"]' => ['value' => $key],
        ],
      ],
      '#attributes' => [
        'class' => [ 'query-conference-document-name' ],
      ],
    ];
    $last_key = $key;
  }
  $help = "";
  if(!empty($last_key)){
    $form['query']['right_column']['fieldset_publication_conference_documents']['conference_document_' . $last_key]['#suffix'] = $help;
  }
  $form['query']['right_column']['fieldset_publication_conference_documents']['close_conference_document'] = [
    '#markup' => '<a href="javascript:void(0);" data-remodal-target="modal-concept" class="add-dialog references-dialog-activate"> + ' . t('Add Conference') . '</a>',
  ];
}


/**
 * Obtener fieldset otros coauthores.
 */
function _get_fieldset_other_co_author(&$form, &$form_state, &$publication = NULL){
  if (empty($form_state['num_co_author'])) {
    $form_state['num_co_author'] = 1;
  }
  // File co_author form element starts
  $form['query']['right_column']['co_author_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '<span class="variable-title">' . t('Autores') . '</span>',
    '#prefix' => '<div id="co-author-fieldset-wrapper-author-complete-book" class="co-author-fieldset-wrapper-author-complete-book margin-fieldset">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => [
      'visible' => [
        'select[name="query[right_column][pub_type]"]' => [
          ['value' => PUB_TYPE_ARTICLE],
          ['value' => PUB_TYPE_BOOK],
          ['value' => PUB_TYPE_WORK_DOCUMENT],
          ['value' => PUB_TYPE_CONFERENCE_DOCUMENT],
          ['value' => PUB_TYPE_BOOK_CHAPTER],
        ],
      ],
    ],
    '#attributes' => [
      'class' => [ 'other-co-author-fieldset-wrapper' ],
    ],
  );
  $co_authors = get_input_value_from_publication($publication, 'co_authors_author', array());
  if (isset($publication->update_co_authors)) {
    unset($publication->update_co_authors);
    $form_state['num_co_author'] = count($co_authors);
  }
  $count_co_author = $form_state['num_co_author'];
  $multiple_co_author = ($count_co_author > 1);
  for ($i = 0; $i < $count_co_author; $i++) {
    $form['query']['right_column']['co_author_fieldset']['co_authors_author'][$i] = array(
      '#type' => 'textfield',
      '#title' => ($i===0?t('Autor principal'):t('Co-Autor')),
      '#size' => 30,
      '#maxlength' => 60,
      '#autocomplete_path' => 'co_author/autocomplete',
      '#default_value' => (isset($co_authors[$i]) ? $co_authors[$i] : ''),
      '#required' => ($i===0),
      '#prefix' =>
        '<div class="row">' .
          '<div class="col-md-12 coauthor-title">'
      ,
      '#suffix' =>
          '</div>' .
        '</div>'
      ,
    );
  }
  $form['query']['right_column']['co_author_fieldset']['add_co_author_complete_book'] = array(
    '#type' => 'submit',
    '#value' => '+ ' . t('Add'),
    '#submit' => array('co_author_add_more_callback'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'co_author_callback',
      'wrapper' => 'co-author-fieldset-wrapper-author-complete-book',
    ),
  );
  // Remove
  if ($multiple_co_author) {
    $form['query']['right_column']['co_author_fieldset']['remove_co_author_complete_book'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('co_author_remove_one_callback'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'co_author_callback',
        'wrapper' => 'co-author-fieldset-wrapper-author-complete-book',
      ),
    );
  }
  $form['query']['right_column']['co_author_fieldset']['register_other_co_author'] = array(
    '#markup' =>
      '<a' .
      ' href="javascript:void(0);"' .
      ' data-remodal-target="modal-other-co-author"' .
      ' class="add-dialog references-dialog-activate"' .
      '>' .
        ' + ' .
        t('Register') .
      '</a>'
    ,
  );
  // END Other-Co-Autores.
}

/**
 * Formulario agregar concepto.
 */
function custom_concept_add_form($form, &$form_state) {

    $form['#attributes']['class'] = 'custom_concept_add_form';

    // Tipo de Concepto
    $form['concept_type_parent'] = [
      '#type' => 'hidden',
      '#default_value' => '0',
      '#attributes' => [
        'class' => [ 'concept_type_parent' ],
      ],
    ];

    $form['concept_type_child'] = [
      '#type' => 'hidden',
      '#default_value' => '0',
      '#attributes' => [
        'class' => [ 'concept_type_child' ],
      ],
    ];

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => '',
      '#description' => t(''),
      '#size' => 60,
      '#maxlength' => 128,
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    $form['isbn'] = array(
      '#type' => 'textfield',
      '#title' => t('ISBN'),
      '#default_value' => '',
      '#description' => '',
      '#size' => 60,
      '#maxlength' => 128,
      '#prefix' => '<div class="row visible-on-book hidden"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    $form['issn'] = array(
      '#type' => 'textfield',
      '#title' => t('ISSN'),
      '#default_value' => '',
      '#description' => '',
      '#size' => 60,
      '#maxlength' => 128,
      '#prefix' => '<div class="row visible-on-article hidden"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    $form['doi'] = array(
      '#type' => 'textfield',
      '#title' => t('DOI'),
      '#default_value' => '',
      '#description' => t(''),
      '#size' => 60,
      '#maxlength' => 128,
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    // Vinculo fieldset
    $form['vinculo']['fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Index'),
        // Set up the wrapper so that AJAX will be able to replace the fieldset.
        '#prefix' => '<div class="row"><div class="col-md-12"><div id="vinculo-fieldset-wrapper" class="vinculo-fieldset-wrapper">',
        '#suffix' => '</div></div></div>',
    );

    $form['vinculo']['fieldset']['indice'] = array(
      '#type' => 'textfield',
      '#title' => t('Index Name'),
      '#default_value' => '',
      '#description' => t(''),
      '#size' => 60,
      '#maxlength' => 128,
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    $form['vinculo']['fieldset']['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Index Url'),
      '#default_value' => '',
      '#description' => t(''),
      '#size' => 60,
      '#maxlength' => 256,
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
    );

    $ajax = array(
        'callback' => 'custom_concept_add_form_ajax_submit',
        'wrapper' => '',
        'effect' => 'fade',
        'progress' => array(
            'type' => 'throbber',
            'message' => NULL,
        ),
        'event' => 'click',
     );

    // form submit
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#prefix' => '<div class="row"><div class="col-md-12">',
      '#suffix' => '</div></div>',
      '#ajax' => $ajax,
    );

    return $form;
}

/**
 * Submit Formulario agregar concepto.
 */
function custom_concept_add_form_ajax_submit($form, &$form_state){
    global $user;
    // Get the form values
    $values = isset($form_state['values']) ? $form_state['values'] : FALSE;
    $concept_type_parent = isset($values['concept_type_parent']) ? $values['concept_type_parent'] : FALSE;
    $concept_type_child = isset($values['concept_type_child']) ? $values['concept_type_child'] : FALSE;
    $concept_name = isset($values['name']) ? $values['name'] : FALSE;
    $isbn = isset($values['isbn']) ? $values['isbn'] : FALSE;
    $issn = isset($values['issn']) ? $values['issn'] : FALSE;
    $doi = isset($values['doi']) ? $values['doi'] : FALSE;
    $vinculo_indice  = isset($values['vinculo']['fieldset']['indice']) ? $values['vinculo']['fieldset']['indice'] : FALSE;
    $url = isset($values['vinculo']['fieldset']['url']) ? $values['vinculo']['fieldset']['url'] : FALSE;

    $response = new stdClass();
    $response->success = FALSE;
    $response->is_valid = FALSE;
    // Validations
    $response->is_valid = TRUE;
    if($concept_type_parent == FALSE || !user_is_logged_in()){
      $response->is_valid = FALSE;
    }
    // Save Concept
    if($response->is_valid){
      $node = new stdClass();
      $node->type = 'concept';
      $node->language = LANGUAGE_NONE;
      $node->status = 0;
      $node->promote = 0;
      $node->sticky = 0;
      $node->comment = 0;
      node_object_prepare($node);
      $node->title = $concept_name;
      $node->field_isbn[LANGUAGE_NONE][0]['value'] = $isbn;
      $node->field_issn[LANGUAGE_NONE][0]['value'] = $issn;
      if($concept_type_parent){
        $node->field_concept_category[LANGUAGE_NONE][0]['tid'] = $concept_type_parent;
      }
      if($concept_type_child){
        $node->field_concept_category[LANGUAGE_NONE][1]['tid'] = $concept_type_child;
      }
      $node->field_concept_source[LANGUAGE_NONE][0]['value'] = 'externo';
      $node->field_doi[LANGUAGE_NONE][0]['url'] = $doi;
      $node->uid = $user->uid;
      // Vinculo.
      if(($url != FALSE) && ($vinculo_indice != FALSE)){
        $vinculo = new stdClass();  // Create a new node object
        $vinculo->type = 'vinculo';  // Content type
        $vinculo->title = $vinculo_indice;
        $vinculo->language = LANGUAGE_NONE;  // Or e.g. 'en' if locale is enabled
        $vinculo->status = 0;   // (1 or 0): published or unpublished
        $vinculo->promote = 0;  // (1 or 0): promoted to front page or not
        $vinculo->sticky = 0;  // (1 or 0): sticky at top of lists or not
        $vinculo->comment = 0;  // 2 = comments open, 1 = comments closed, 0 = comments hidden
        $vinculo->uid = $user->uid;
        node_object_prepare($node);  //Set some default values
        $vinculo->field_url_indice[LANGUAGE_NONE][0]['url'] = $url;
        // Save Vinculo
        node_save($vinculo);
        if(isset($vinculo->nid)){
          $node->field_index[LANGUAGE_NONE][0]['target_id'] = $vinculo->nid;
        }
      }
      // Save Concept
      node_save($node);
      if(isset($node->nid)){
        $response->success = TRUE;
        $response->title = $node->title;
        $response->nid = $node->nid;
        $response->label = $node->title . ' (' . $node->nid . ')';
      }
    }
    $msg = "";
    $response->message = $msg;
    return array(
        '#type' => 'ajax',
        '#commands' => array(
            array('command' => 'responseConceptAddForm', 'data' => $response, 'msg' =>$msg),
        ),
    );
}
