<?php

/**
 * @file
 * Proporciona las funciones de ayuda al módulo CAIE.
 */

define('SERVICES_FORM_NID_1', '1928');
define('SERVICES_FORM_NID_2', '1929');
define('SERVICES_FORM_NID_3', '1930');
define('SERVICES_FORM_NID_4', '1931');
define('SERVICES_FORM_NID_5', '1932');
define('SERVICES_FORM_NID_6', '1934');
define('SERVICES_FORM_NID_7', '1933');
define('SERVICES_FORM_NID_8', '1935');
define('SERVICES_FORM_NID_9', '1936');

/**
 * Contiene los ids de formularios portafolio de servicios.
 *
 * @return string
 *   Arreglo con los ids de formularios.
 */
function _get_services_form_nids() {
  return variable_get('SERVICES_FORM_NIDS',
    array(
      SERVICES_FORM_NID_1,
      SERVICES_FORM_NID_2,
      SERVICES_FORM_NID_3,
      SERVICES_FORM_NID_4,
      SERVICES_FORM_NID_5,
      SERVICES_FORM_NID_6,
      SERVICES_FORM_NID_7,
      SERVICES_FORM_NID_8,
      SERVICES_FORM_NID_9,
    ));
}

/**
 * Función de ayuda que genera un nombre de máquina usando un nombre legible.
 *
 * @param string $human_name
 *   Nombre legible por humanos.
 *
 * @return string
 *   Nombre de máquina limpio de cualquier caracter especial.
 */
function human_to_machine($human_name) {
  return strtolower(preg_replace(array(
    '/[^a-zA-Z0-9]+/',
    '/-+/',
    '/^-+/',
    '/-+$/',
  ), array('-', '-', '', ''), $human_name));
}
