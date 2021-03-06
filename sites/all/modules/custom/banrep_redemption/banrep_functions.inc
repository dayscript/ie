<?php


function banrep_redemption_add_form($form, &$form_state, $type) {

    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['#prefix'] = '<div id="ajax_form_multistep_form"><div class="col-md-12">';
    $form['#suffix'] = '</div></div>';
    $form['#attributes']['class'] = 'activities_add_form';

    $form['query']['content'] = [
    '#type' => 'container',
    '#attributes' => [
        'class' => [
        'demo',
        ],
    ],
    '#weight' => 1,
    ];

    $fields = array();
    switch ($type) {
    case 'redemption':
        $vid = 26;
        break;
    case 'training':

    $options_date = range(2018, 1950);
        $fields['publication_year'] = array(
        '#type' => 'select',
        '#title' => t('Year'),
        '#options' => array_combine($options_date, $options_date),
        '#default_value' => get_input_value_from_publication($publication, 'act_year'),
        '#description' => t(''),
        '#prefix' => '<div class="row"><div class="col-md-3 col-sm-12">',
        '#suffix' => '</div>',
        '#required' => TRUE,
        );

        $fields['start_date'] = array(
        '#title'=>t('Start date'),
        '#date_format' => 'd-m-Y',
        '#date_year_range' => '-30:+1',
        '#type' => 'date_popup',
        '#default_value'=>get_input_value_from_publication($publication, 'start_date'),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-3 col-sm-12">',
        '#suffix' => '</div>',
        );

        $fields['end_date'] = array(
        '#title'=>t('End Date'),
        '#date_format' => 'd-m-Y',
        '#date_year_range' => '-30:+1',
        '#type' => 'date_popup',
        '#default_value'=>get_input_value_from_publication($publication, 'end_date'),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-3 col-sm-12">',
        '#suffix' => '</div>',
        );


        $fields['visibility'] = array(
        '#title' => t('Public/Private'),
        '#type' => 'select',
        '#description' => t('Public is visible for all people'),
        '#options' => array('' => t('-Select-'), 'publico' => t('Public'), 'privado' => t('Private')),
        '#default_value' => get_input_value_from_publication($publication, 'visibility'),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-3 col-sm-12">',
        '#suffix' => '</div></div>',
        );
        $fields['file'] = array(
        '#title' => t('Attach evidence'),
        '#type' => 'managed_file',
        '#default_value' => get_input_value_from_publication($publication, 'attach_doc'),
        '#description' => t('Upload an evidence document in pdf format'),
        '#upload_location' => 'public://activity',
        "#upload_validators"  => array(
            'file_validate_extensions' => 'pdf',
            '_file_validate_unique' => array($file),
        ),
        '#required' => TRUE,
        );
        global $user;
        $usuario = user_load($user->uid);
        $route        = $usuario->field_ruta['und'][0]['target_id'];
        $scale        = $usuario->field_usr_escalafon['und'][0]['tid'];
        module_load_include('inc', 'banrep_plan_carrera', 'banrep_plan_carrera.functions');
        $requirements = get_requirements($scale, $route, $usuario->uid,'training');
        $tids = array();
        foreach ($requirements as $rule) {
        foreach ($rule as $key => $requirement) {
            if ($key == 'operator') {
            continue;
            }
            $structure =  taxonomy_get_parents_all($requirement);
            foreach ($structure as $tax) {
            if ($tax->tid != $requirement) {
                $tids[] = $tax->tid;
            }
            // code...
            }
            $tids[] = $requirement;
        }
        }
        drupal_add_js(array('redemption' => array('tids' => $tids)), array('type' => 'setting'));
        $vid = 23;
        break;
        }
    $form['query']['content']['type_concept_formation'] = array(
    '#type' => 'hierarchical_select',
    '#title' => t('Concept'),
    '#config' => array(
        'module' => 'hs_taxonomy',
        'params' => array(
        'vid' => $vid, // Enter your vocabulary ID here.
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
    '#default_value' => get_input_value_from_publication($publication, 'description'),
    '#required' => TRUE,
    );

    if (count($fields) > 0 ) {
    $form += $fields;
    }


    $form['buttons']['submit'] = [
        '#type' => 'submit',
        '#value' => t('Save') . ' ❯',
    ];
    drupal_add_js(drupal_get_path('module', 'banrep_redemption') . '/redemption.js');

    return $form;
}


function banrep_redemption_add_form_submit($form, &$form_state) {
    global $user;
    $type = arg(1);
    if (empty($type)) {
    drupal_set_message(t('Error saving content.'), 'error', FALSE);
    return FALSE;
    }

    $node = NULL;
    $node = new stdClass();
    $node->type = $type;
    $node->language = LANGUAGE_NONE;
    node_object_prepare($node);
    $node->status = 0;
    $node->promote = 0;
    $node->sticky = 0;
    $node->comment = 0;
    $node->uid = $user->uid;
    $node->title = time();
    $node->body['und'][0]['value'] = isset($form_state['values']['description']) ? $form_state['values']['description'] : '';
    $field_concept = 'field_red_concepto';
    $message = 'Nuevo registro de redención creado correctamente';

    if ($type == 'training') {
    $field_concept = 'field_concept_formation';
    $message = 'Nuevo registro de formación y desarrollo creado correctamente';
    }

    if (isset($form_state['values']['start_date'])) {
    $date =  strtotime($form_state['values']['start_date']);
    $node->field_frm_date_start['und'][0]['value'] = $date;
    }
    if (isset($form_state['values']['end_date'])) {
    $date =  strtotime($form_state['values']['end_date']);
    $node->field_frm_date_end['und'][0]['value'] = $date;
    }
    if (isset($form_state['values']['publication_year'])) {
    $node->field_year['und'][0]['value'] = $form_state['values']['publication_year'];
    }
    if (isset($form_state['values']['visibility'])) {
    $node->field_act_status['und'][0]['value'] = $form_state['values']['visibility'];
    }

    if (isset($form_state['values']['type_concept_formation']) && !empty($form_state['values']['type_concept_formation'])) {
    $node->{$field_concept}['und'][0]['tid'] = $form_state['values']['type_concept_formation'];
    $puntaje = _get_puntaje_concepto_tax($form_state['values']['type_concept_formation']);
    if ($puntaje) {
        $node->field_puntaje['und'][0]['value'] = $puntaje;  
    }
        
    }
    $file = NULL;
    if (isset($form_state['values']['file'])) {
    $file = file_load($form_state['values']['file']);
    $file->filename = $file->fid . '-' . time();
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    $node->field_re_attach_doc[LANGUAGE_NONE][0] = (array)$file;
    $node->field_re_attach_doc[LANGUAGE_NONE][0]['display'] = 1;
    }

    node_save($node);

    if (isset($node->nid) && is_numeric($node->nid) && $node->nid > 0) {
    drupal_set_message(t($message));
    if (isset($file->nid)) {
        file_usage_add($file, 'banrep_core', 'node', $node->nid);
    }
    drupal_goto('dashboard');
    }
}

function banrep_redemption_update_state() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'user')
        ->addTag('role_filter');
    $result = $query->execute();
    $uids = array_keys($result['user']);
    foreach( $uids as $uid )
    {
    //Comparación de requisitios
    }
    echo "<pre>"; print_r($uids); echo "</pre>";
    }
    /*
    * Funcion que carga le puntaje del concepto
    */
    function _get_puntaje_concepto_tax($tid,$uid = 0) {
    if ($uid == 0) {
    global $user;
    $usuario = user_load($user->uid);
    }
    else {
    $usuario = user_load($uid); 
    }
    $ruta = isset($usuario->field_ruta['und'][0]['target_id']) ? $usuario->field_ruta['und'][0]['target_id'] : 0;
    $query = db_select('taxonomy_term_data', 't');
    $query->addField('p', 'field_puntaje_value', 'puntaje');
    $query->join('field_data_field_puntajes', 'f', 'f.entity_id = t.tid');
    $query->join('field_data_field_puntaje', 'p', 'p.entity_id = f.field_puntajes_value');
    $query->join('field_data_field_ruta', 'r', 'r.entity_id = f.field_puntajes_value');
    $query->condition('t.tid', $tid);
    $query->condition('r.field_ruta_target_id', $ruta);
    $result = $query->execute()->fetchObject();

    if (isset($result->puntaje) && !empty($result->puntaje) && !is_null($result->puntaje) && is_numeric($result->puntaje)) {
    return $result->puntaje;
    }
    else {
    return FALSE;
    }
}


function _get_index_field_collecion_user($user, $field = null, $value=null){

    if(!is_null($field)){
        foreach( $user->$field['und'] as $key => $item ){
            if($item['value'] = $value){
                return $index;
            }
        }
        return true;
    }

    return false;
}