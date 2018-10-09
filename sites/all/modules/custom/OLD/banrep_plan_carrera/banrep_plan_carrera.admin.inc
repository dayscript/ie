<?php

/**
 * @file
 * Configuración del módulo plan carrera.
 */

/**
 * Configuración del módulo.
 */
function banrep_plan_carrera_settings_form($form, &$form_state) {
  $form = array();
  return system_settings_form($form);
}

/**
 * Submit Configuración del módulo.
 */
function banrep_plan_carrera_settings_form_submit(&$form, &$form_state) {
}

