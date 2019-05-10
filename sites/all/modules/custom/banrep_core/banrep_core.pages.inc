<?php

/**
* Publications add page
*/
function banrep_core_publications_add_page(){
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    // add validations js
    drupal_set_title(t('Add publication'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), '<front>');
    $breadcrumb[] = '<span>'. t('Add publication') . '</span>';
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
    // initialize output variable
    $output = '';
    $add_form = drupal_get_form('publications_add_form');
     // render add publication form
    $output .= '<section class="form-add-publication"><div class="form-wrapper">'.drupal_render($add_form).'</div></section>';
    return $output;
}

/**
* Publications add page
*/
function banrep_core_publications_edit_page(){
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    // add validations js
    drupal_set_title(t('Edit publication'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), '<front>');
    $breadcrumb[] = '<span>'. t('Edit publication') . '</span>';
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
    // initialize output variable
    $output = '';
    $add_form = drupal_get_form('publications_add_form');
     // render add publication form
    $output .= '<section class="form-add-publication"><div class="form-wrapper">'.drupal_render($add_form).'</div></section>';
    return $output;
}

/**
* Group add page
*/
function banrep_core_group_edit_page($tid){
  drupal_set_title(t('Manage Group'));
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = '<span>'. l(t('Group'), 'taxonomy/term/' . $tid) . '</span>';
  $breadcrumb[] = '<span>'. t('Manage') . '</span>';
  drupal_set_breadcrumb($breadcrumb);

  global $user;
  $term = taxonomy_term_load($tid);
  $output = '';
  foreach ($term->field_members['und'] as $key => $member) {
    if($member['target_id'] == $user->uid && user_has_role(ADMIN_GRUPO_RID)){
        drupal_add_library ( 'system' , 'ui.tabs' );
        drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile_edit.js');
        module_load_include('inc', 'taxonomy', 'taxonomy.admin');
        $vocabulary = taxonomy_vocabulary_load(2, FALSE);
        unset($term->field_image);
        $form = drupal_get_form('taxonomy_form_term', $term, $vocabulary);
        $output = '
        <div id="tabs">
          <ul>
            <li><a href="#tabs-1">'.t('General Information').'</a></li>
            <li><a href="#tabs-2">'.t('Manage Blog').'</a></li>
            <li><a href="#tabs-3">'.t('Manage News').'</a></li>
          </ul>
          <div id="tabs-1"><div class="tabs-wrapper">
            <div class="profile-edit-group">
            ' . drupal_render($form) . '
          </div></div></div>
          <div id="tabs-2"><div class="tabs-wrapper"><div class="tablero-caie">
            '.views_embed_view('gestionar_entradas_de_blogs','gestionar_blogs',$term->tid).'
          </div></div></div>
          <div id="tabs-3"><div class="tabs-wrapper"><div class="tablero-caie">
            '.views_embed_view('gestionar_entradas_de_blogs','gestionar_noticias',$term->tid).'
          </div></div></div>
        </div>';
        return $output;
    }
  }

  return drupal_access_denied();
}

/**
* Article add page
*/
function banrep_core_article_add_page(){
    module_load_include('inc', 'node', 'node.pages');
    global $user;
    // add validations js
    drupal_set_title('Agregar noticia');
    $breadcrumb = array();
    $breadcrumb[] = l('Home', '<front>');
    $breadcrumb[] = '<span>'.t('News').'</span>';
    $breadcrumb[] = '<span>'.t('Add').'</span>';
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
    // initialize output variable
    $node = (object) array(
      'uid' => $user->uid,
      'name' => (isset($user->name) ? $user->name : ''),
      'type' => 'article',
      'language' => 'es',
    );
    $output = '';
    $add_form = drupal_get_form('article_node_form', $node);
     // render add event form
    $output .= '<section class="form-add-noticia"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
    return $output;
}

/**
* Entrada de Blog add page
*/
function banrep_core_blogs_add_page(){
    module_load_include('inc', 'node', 'node.pages');
    global $user;
    // add validations js
    drupal_set_title('Agregar Entrada de Blog');
    $breadcrumb = array();
    $breadcrumb[] = l('Home', '<front>');
    $breadcrumb[] = '<span>Blog</span>';
    $breadcrumb[] = '<span>'.t('Add').'</span>';
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
    // initialize output variable
    $output = '';
    $node = (object) array(
      'uid' => $user->uid,
      'name' => (isset($user->name) ? $user->name : ''),
      'type' => 'blog',
      'language' => LANGUAGE_NONE,
    );
    $add_form = drupal_get_form('blog_node_form', $node);
     // render add blog form
    $output .= '<section class="form-add-blog"><div class="form-wrapper">' . drupal_render($add_form) . '</div></section>';
    return $output;
}

function banrep_core_save_like_to_user(){
    $response = FALSE;
    $new_val = 0;
    $current_val = 0;
    if(isset($_POST['data_uid'])){
        $uid = $_POST['data_uid'];
        $user = user_load($uid);
        if($user){
            if(isset($user->field_likes['und'][0]['value'])){
                $current_val = intval($user->field_likes['und'][0]['value']);
            }
        }
        $new_val = $current_val +1;
        $user->field_likes['und'][0]['value'] = $new_val;
        if(user_save($user)!= FALSE){
            $response = TRUE;
        }
    }
    drupal_json_output(array('response' => $response, 'new_val' => $new_val));
}

function banrep_core_publications_page(){
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $content = "";
    return $content;
}

function banrep_core_dashboard_save_order_page(){
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $response = FALSE;
    if(isset($_POST['profile_info_order'])){
        $value = $_POST['profile_info_order'];
        if(user_is_logged_in()){
            $uid = $GLOBALS['user']->uid;
            $name = 'profile_info_order_'.$uid;
            variable_set($name, $value);
            $response = TRUE;
        }
    }
    drupal_json_output(array('response' => $response));
}

/*
* Promote Publication
*/
function banrep_core_promote_publication_page(){
   module_load_include('inc', 'banrep_core', 'banrep_core.functions');
   $response = FALSE;
   if(isset($_POST['nid'])){
        $nid = $_POST['nid'];
        $promotes_publications = drupal_get_promotes_publications();
        $count = count($promotes_publications) - 1;
        foreach ($promotes_publications as $key => $publication_id) {
             $node = node_load($publication_id);
             if(isset($node->type) && ($node->type == 'publication')){
                $node->field_order['und'][0]['value'] = $key + 1;
                node_save($node);
             }
             if($count == $key){
                if($count == 4){
                  $node->field_order['und'][0]['value'] = 6;
                  node_save($node);
                }
                $promote = node_load($nid);
                if(isset($promote->type) && ($promote->type == 'publication')){
                    $promote->field_order['und'][0]['value'] = 5;
                    node_save($promote);
                }
             }
        }
        $response = TRUE;
   }
   drupal_json_output(array('response' => $response));
}

/*
* Save boxes order on research group detail
*/
function banrep_core_research_group_save_order_page(){
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $response = FALSE;
    if(isset($_POST['group_boxes_order']) && isset($_POST['term_id'])){
        $value = $_POST['group_boxes_order'];
        $key = $_POST['term_id'];
        if(user_is_logged_in()){
            $name = 'research_group_boxes_order_'.$key;
            variable_set($name, $value);
            $response = TRUE;
        }
    }
    drupal_json_output(array('response' => $response));
}

function banrep_core_dashboard_page() {
  drupal_set_title($title = 'Centro de Apoyo a la Investigación Económica - CAIE');
  global $user;
  drupal_add_library('system', 'ui.accordion');
  drupal_add_js(drupal_get_path('module', 'banrep_core').'/js/tablero_caie_block.js');
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $modal = '<div class="remodal" data-remodal-id="modal-submission-response"><a data-remodal-action="close" class="remodal-close"></a><span class="msg-label">' . t('Respuesta de su Solicitud') . '</span><div class="msg"></div></div>';
  $filters = array( 'uid' => $user->uid );
  // Envios por usuario.
  $submissions = webform_get_submissions($filters, NULL, 10);

  //Nids de Servicios
  $services_form_nids = _get_services_form_nids();

  $header = array(t('ID'), t('Tipo de solicitud'), t('Descripción'), t('Estado'), t('Acciones'));
  $rows = array();

  foreach ($submissions as $key => $submission) {

    $nid =  $submission->nid;
    $id = '#' . $submission->sid;
    $tipo_servicio = '';
    $tipo_servicio_key = '';
    $descripcion = '';
    $estado = '';
    $status_message = t('Tu Solicitud aun no ha sido respondida, por favor verificar mas tarde!.');

    $webform_workflow_state = webform_workflow_state_load_by_submission($submission, $reset = FALSE); // Get the state of a submission.
    if(isset($webform_workflow_state->color) && isset($webform_workflow_state->label)){
       $estado = '<span class="webform-workflow-state webform-workflow-state-label webform-workflow-state-color-' . $webform_workflow_state->color . '">' . $webform_workflow_state->label . '</span>';
    }

    if(isset($webform_workflow_state->wsid)){
      $status_message = get_webform_submission_last_message($submission->nid, $submission->sid, $webform_workflow_state->wsid);
    }

    $acciones = '<a href="javascript:void(0);" class="view-response" data-remodal-target="modal-submission-response">' . t('+ Ver') . '<div class="hide status-message">' . $status_message . '</div></a>';

    $tipo_solicitud_allowed_values = webform_options_soluciones_caie_servicios();

    switch ($nid) {
        case SERVICES_FORM_NID_1:
            if(isset($submission->data[5][0])){
              $tipo_solicitud_key = $submission->data[5][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_2:
            if(isset($submission->data[6][0])){
              $tipo_solicitud_key = $submission->data[6][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_3:
            if(isset($submission->data[7][0])){
              $tipo_solicitud_key = $submission->data[7][0];
            }
            if(isset($submission->data[5][0])){
              $descripcion = $submission->data[5][0];
            }
            break;
        case SERVICES_FORM_NID_4:
            if(isset($submission->data[9][0])){
              $tipo_solicitud_key = $submission->data[9][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_5:
            if(isset($submission->data[7][0])){
              $tipo_solicitud_key = $submission->data[7][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_6:
            if(isset($submission->data[6][0])){
              $tipo_solicitud_key = $submission->data[6][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_7:
            if(isset($submission->data[9][0])){
              $tipo_solicitud_key = $submission->data[9][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_8:
            if(isset($submission->data[9][0])){
              $tipo_solicitud_key = $submission->data[9][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
        case SERVICES_FORM_NID_9:
            if(isset($submission->data[16][0])){
              $tipo_solicitud_key = $submission->data[16][0];
            }
            if(isset($submission->data[4][0])){
              $descripcion = $submission->data[4][0];
            }
            break;
    }
    $tipo_solicitud = '';
    if(!empty($tipo_solicitud_key)){
      if(isset($tipo_solicitud_allowed_values[$tipo_solicitud_key])){
        $tipo_solicitud = $tipo_solicitud_allowed_values[$tipo_solicitud_key];
      }
    }
    $rows[] = array($id, $tipo_solicitud, $descripcion, $estado, $acciones);
  }
  $output = '<div class="tablero-caie publications-page listing-page">';
  if(!empty($rows)) {
    $output .= theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager') . $modal . '</div>';
  }
  else {
    $output .= '<p>'.t('You do not yet have request registered on your board') . '</p></div>';
  }

  $pubs_promote   = views_embed_view('publicaciones', 'promotes_publications', $user->uid);
  $mis_pubs       = views_embed_view('dashboard_mis_publicaciones', 'block', $user->uid);
  $mis_acts       = views_embed_view('_gestionar_otras_actividades', 'block', $user->uid);
  // Recomendados
  $user_favorites = module_invoke('banrep_investigador', 'block_view', 'user_favorites');

  $favoritos      = views_embed_view('mis_enlaces_recomendados', 'enlaces_recomendados_privados', $user->uid);
  $training = views_embed_view('gestionar_formacion_desarrollo', 'block', $user->uid);
  $redemption = views_embed_view('gestionar_redenciones', 'block', $user->uid);

  $html =
    '<div class="box-dashboard accordion" id="accordion">' .
      '<h2>' . t('Gestión de publicaciones') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $mis_pubs .
        '</div>' .
      '</div>' .
      '<h2>' . t('Estado de solicitudes') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $output .
        '</div>' .
      '</div>' .
      '<h2>' . t('Gestionar otras actividades') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $mis_acts .
        '</div>' .
      '</div>' .
      '<h2>' . t('Enlaces Favoritos') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $user_favorites['content'] .
        '</div>' .
      '</div>' .
      '<h2>' . t('Gestionar formación y desarrollo') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $training .
        '</div>' .
      '</div>' .
      '<h2>' . t('Gestionar redenciones') . '</h2>' .
      '<div class="registro">' .
        '<div class="row-container">' .
          $redemption .
        '</div>' .
      '</div>' .
    '</div>'
  ;
  return $html;
}

function banrep_core_seminarios_page() {
    global $language;
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $seminario = get_seminario();
    $html = array();
    if($seminario != FALSE){
        // Retrieve the html for the node.
        $node = node_load($seminario);
        $node_view = node_view($node,  $view_mode = 'sem_detalle_full');
        $html = $node_view;//drupal_render($node_view);

        if($language->language == 'es') {
            drupal_set_title('Seminario: '.$node->title);
        }
        else {
            drupal_set_title('Seminary: '.$node->title);
        }

    }else{

    }
    return $html;
}

function banrep_core_profile_page($name = '') {
    global $user;
    global $language;


    $profile_path = ($language->language == 'es') ? 'investigadores' : 'researchers';
    $profile_info_order = FALSE;
    $show_edit = FALSE;
    if(!empty($name)){
        //$user_load = user_load_by_name($name);
        $user_load = user_load($name);
        if($user_load == FALSE){
            return drupal_not_found();
        }else{
          $uid = $user_load->uid;
        }
    }else{
        $uid = $user->uid;
    }

    if(user_is_logged_in()){
        $name = 'profile_info_order_'.$uid;
        $profile_info_order = variable_get($name, FALSE);
        if($uid == $user->uid){
            $show_edit = TRUE;
        }
    }

    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $user_data = get_current_user_data($uid);
    $field_full_name = isset($user_data['field_full_name']) ? $user_data['field_full_name'] : '';

    // Build Breadcrumbs
    $breadcrumb = array();
    $breadcrumb[] = l('Home', '<front>');
    $breadcrumb[] = l(t('Researchers'). ' ', $profile_path);

    if(!empty($field_full_name)){
        $breadcrumb[] = '<span>'.$field_full_name.'</span>';
    }

    if($show_edit){
        $breadcrumb[] = '<span class="pull-right"><label class="label-sort">Ordenar</label> <label class="switch-sort"><input id="switch-sort" type="checkbox"><div class="slider round"></div></label></span>';
    }else{
        $breadcrumb[] = '<span></span>';
    }

    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);

    $title = t('Profile') . ' | Portal de Investigaciones Económicas';
    if(!empty($field_full_name)){
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


function banrep_core_backup_profile_edit_page(){
    global $user;
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    module_load_include('inc', 'user', 'user.pages');
    $account = user_load($user->uid);
    $form_state = array();
    $form_state['build_info']['args'] = array($account);
    form_load_include($form_state, 'inc', 'user', 'user.pages');
    // $get_form = drupal_get_form('user_profile_form', $user);
    // $user_profile_form = drupal_render($get_form);
    $get_form = drupal_build_form('user_profile_form', $form_state);
    $user_profile_form = render($get_form);
    $user_data = get_current_user_data();
    // Build Breadcrumbs
    $breadcrumb = array();
    $breadcrumb[] = l('Home', '<front>');
    $breadcrumb[] = l('Investigadores ', '<front>');
    $breadcrumb[] = '<span>'.$user_data['field_full_name'].'</span>';
    $breadcrumb[] = '<span></span>';

    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
    drupal_set_title($title = 'Profile Edit | Portal de Investigaciones Económicas');
    $content = theme('banrep_core_profile_edit', array('user_profile_form' => $user_profile_form));
    return $content;
}

function banrep_core_profile_edit_page(){
    global $user;
    module_load_include('inc', 'banrep_core', 'banrep_core.functions');
    $account = user_load($user->uid, $reset = TRUE);
    $full_name = isset($account->field_full_name['und'][0]['value'])?$account->field_full_name['und'][0]['value']:'';
    // Include assets
    drupal_add_library ( 'system' , 'ui.tabs' );
    drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile_edit.js');
    // Build Breadcrumbs
    $breadcrumb = array();
    $breadcrumb[] = l('Home', '<front>');
    $breadcrumb[] = l('Investigadores ', '<front>');
    if(!empty($full_name )){
        $breadcrumb[] = '<span>' . $full_name .'</span>';
    }
    $breadcrumb[] = '<span></span>';
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);

    // Set Title
    drupal_set_title($title = 'Profile Edit | Portal de Investigaciones Económicas');

    // OutPut
    $content = theme('banrep_core_profile_edit', array('account' => $account));

    return $content;
}


function theme_caie_solutions($variables) {
    $items = $variables['items'];
    $output = '';
    $output .= '<div class="soluciones-caie"><div class="row"><div class="col-lg-3"><h2>' . t('SOLUTIONS') . '</h2></div> <div class="col-lg-9"><ul class="solution-items">';
    foreach ($items as $key => $item) {
        $c = $key+1;
        $iconclass = isset($item->field_icono_class['und'][0]['value'])?$item->field_icono_class['und'][0]['value']:'';
        $icon = '<span class="' . $iconclass . '"></span>';
        $url = url('taxonomy/term/' . $item->tid);
        $output .= '<li class="item-'.$c.'"> <a href="' . $url . '" title="'. $item->name .'">' . $icon . '<strong class="item-title">'. $item->name .'</strong></a></li>';
    }
    $output .= '</ul></div></div></div>';
    return $output;
}

function theme_caie_numbers($variables) {
    $items = $variables['items'];
    $output = '<div class="cifras"><ul>';
    foreach ($items as $key => $item) {
      if($item->status) {
        $output .= '<li><strong>'.$item->field_cifra_valor['und'][0]['value'].'</strong>';
        $output .= '<p>'.$item->name.'</p></li>';
      }
    }
    $output .= '</ul></div>';
    return $output;
}

function theme_caie_resources($variables) {
    $items = $variables['items'];
    $output = '';
    $output .= '<div class="recursos"><div class="row"><div class="col-lg-12"><ul class="recursos-items">';
    foreach ($items as $key => $item) {
        $c = $key+1;
        $status_resources = FALSE;
        if(isset($item->status) && ($item->status == '1')){
            $status_resources = TRUE;
        }
        if($status_resources){
            $iconclass = isset($item->field_icono_class['und'][0]['value'])?$item->field_icono_class['und'][0]['value']:'';
            $icon = '<span class="' . $iconclass . '"></span>';
            if(isset($item->field_url_recurso['und'][0]['url'])){
                $url = $item->field_url_recurso['und'][0]['url'];
            }else{
                $url = url('taxonomy/term/' . $item->tid);
            }
            $output .= '<li class="item-'.$c.'"> <a href="' . $url . '" title="'. $item->name .'">' . $icon . '<strong class="item-title">'. $item->name .'</strong></a></li>';
        }
    }
    $output .= '</ul></div></div></div>';
    return $output;
}

function theme_caie_collaborators($variables) {
    $items = $variables['items'];
    $output = '<div class="colaboradores"><ul>';
    foreach ($items as $key => $item) {
        $output .= '<li><div class="profile-image">'.theme('image_style', array('style_name' => 'user_picture_60x60', 'path' => $item->field_imagen['und'][0]['uri'])).'</div>';
        $output .= '<div class="user-info"><div class="full-name">'.$item->name.'</div>
        <div class="position">'.$item->description.'</div></div></li>';
    }
    $output .= '</ul><div class="contact-email"><a href="mailto:caie-soluciones@banrep.gov.co"><i class="fa fa-envelope" aria-hidden="true"></i> caie-soluciones@banrep.gov.co</a></div>';
    $output .= '</ul></div>';
    return $output;
}
