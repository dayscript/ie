<?php

/**
 * @file
 * Proporciona las páginas de vista / edición / eliminación de CAIE.
 */

module_load_include('inc', 'banrep_caie', 'banrep_caie.functions');

/**
 * Página CAIE.
 */
function banrep_caie_page() {
  drupal_set_title('Centro de Apoyo a la Investigación Económica - CAIE');
  return '';
}

/**
 * Página dashboard Investigador.
 */
function banrep_caie_dashboard_page() {
  drupal_set_title($title = 'Centro de Apoyo a la Investigación Económica - CAIE');
  global $user;
  drupal_add_library('system', 'ui.accordion');
  drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/tablero_caie_block.js');
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $modal = '<div class="remodal" data-remodal-id="modal-submission-response"><a data-remodal-action="close" class="remodal-close"></a><span class="msg-label">' . t('Respuesta de su Solicitud') . '</span><div class="msg"></div></div>';
  $filters = array('uid' => $user->uid);
  // Envios por usuario.
  $submissions = webform_get_submissions($filters, NULL, 10);

  //Nids de Servicios
  $services_form_nids = _get_services_form_nids();

  $header = array(
    t('ID'), t('Tipo de solicitud'), t('Descripción'), t('Estado'), t('Acciones'),
  );
  $rows = array();

  foreach ($submissions as $key => $submission) {

    $nid = $submission->nid;
    $id = '#' . $submission->sid;
    $tipo_servicio = '';
    $tipo_servicio_key = '';
    $descripcion = '';
    $estado = '';
    $status_message = t('Tu Solicitud aun no ha sido respondida, por favor verificar mas tarde!.');

    $webform_workflow_state = webform_workflow_state_load_by_submission($submission, $reset = FALSE);
    if (isset($webform_workflow_state->color) && isset($webform_workflow_state->label)) {
      $estado = '<span class="webform-workflow-state webform-workflow-state-label webform-workflow-state-color-' . $webform_workflow_state->color . '">' . $webform_workflow_state->label . '</span>';
    }

    if (isset($webform_workflow_state->wsid)) {
      $status_message = get_webform_submission_last_message($submission->nid, $submission->sid, $webform_workflow_state->wsid);
    }

    $acciones = '<a href="javascript:void(0);" class="view-response" data-remodal-target="modal-submission-response">' . t('+ Ver') . '<div class="hide status-message">' . $status_message . '</div></a>';

    $tipo_solicitud_allowed_values = webform_options_soluciones_caie_servicios();

    switch ($nid) {
      case SERVICES_FORM_NID_1:
        if (isset($submission->data[5][0])) {
          $tipo_solicitud_key = $submission->data[5][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_2:
        if (isset($submission->data[6][0])) {
          $tipo_solicitud_key = $submission->data[6][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_3:
        if (isset($submission->data[7][0])) {
          $tipo_solicitud_key = $submission->data[7][0];
        }
        if (isset($submission->data[5][0])) {
          $descripcion = $submission->data[5][0];
        }
        break;

      case SERVICES_FORM_NID_4:
        if (isset($submission->data[9][0])) {
          $tipo_solicitud_key = $submission->data[9][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_5:
        if (isset($submission->data[7][0])) {
          $tipo_solicitud_key = $submission->data[7][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_6:
        if (isset($submission->data[6][0])) {
          $tipo_solicitud_key = $submission->data[6][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_7:
        if (isset($submission->data[9][0])) {
          $tipo_solicitud_key = $submission->data[9][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_8:
        if (isset($submission->data[9][0])) {
          $tipo_solicitud_key = $submission->data[9][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;

      case SERVICES_FORM_NID_9:
        if (isset($submission->data[16][0])) {
          $tipo_solicitud_key = $submission->data[16][0];
        }
        if (isset($submission->data[4][0])) {
          $descripcion = $submission->data[4][0];
        }
        break;
    }
    $tipo_solicitud = '';
    if (!empty($tipo_solicitud_key)) {
      if (isset($tipo_solicitud_allowed_values[$tipo_solicitud_key])) {
        $tipo_solicitud = $tipo_solicitud_allowed_values[$tipo_solicitud_key];
      }
    }
    $rows[] = array($id, $tipo_solicitud, $descripcion, $estado, $acciones);
  }
  $output = '<div class="tablero-caie publications-page listing-page">';
  if (!empty($rows)) {
    $output .= theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager') . $modal . '</div>';
  }
  else {
    $output .= '<p>' . t('You do not yet have request registered on your board') . '</p></div>';
  }

  $pubs_promote = views_embed_view('publicaciones', 'promotes_publications', $user->uid);
  $mis_pubs = views_embed_view('dashboard_mis_publicaciones', 'block', $user->uid);
  $mis_acts = views_embed_view('_gestionar_otras_actividades', 'block', $user->uid);
  // Recomendados.
  $user_favorites = module_invoke('banrep_investigador', 'block_view', 'user_favorites');

  $favoritos = views_embed_view('mis_enlaces_recomendados', 'enlaces_recomendados_privados', $user->uid);

  $html =
    '<div class="box-dashboard accordion" id="accordion"><h2>' . t('Gestión de publicaciones') . '</h2><div class="registro">' .
        '<div class="row-container">' .
          $mis_pubs .
        '</div></div><h2>' . t('Estado de solicitudes') . '</h2>' .
      '<div class="registro"><div class="row-container">' .
          $output .
        '</div></div><h2>' . t('Gestionar otras actividades') . '</h2>' .
      '<div class="registro"><div class="row-container">' .
          $mis_acts .
        '</div></div><h2>' . t('Enlaces Favoritos') . '</h2><div class="registro"><div class="row-container">' .
          $user_favorites['content'] .
        '</div></div></div>';
  return $html;
}
