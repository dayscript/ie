<?php

/**
 * @file
 * Proporciona funciones de ayuda en módulo seminary.
 */

/**
 * Obtiene el ultimo seminario.
 */
function get_seminario(){
  $node_id = FALSE;
  $query = new EntityFieldQuery;
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'event')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_event_date', 'value', time(), '>=')
    ->fieldOrderBy('field_event_date', 'value', 'ASC')
    ->range(0, 1)
    ->execute();
  if (isset($result['node'])) {
    $nodes = array_keys($result['node']);
    $node_id = reset($nodes);
  } else {
    $query = db_select('node', 'n');
    $query->join('field_data_field_serie_de_evento', 's', 'n.nid = s.entity_id');
    $query->join('field_data_field_tipo_de_evento', 't', 'n.nid = t.entity_id');
    $query->condition('n.type', 'event');
    $query->condition('n.status', NODE_PUBLISHED);
    $query->condition('s.field_serie_de_evento_target_id', 54, '=');
    $query->condition('t.field_tipo_de_evento_tid', 191, '=');
    $query->fields('n', array('nid'));
    $query->orderBy('n.created', 'desc');
    $node_id = $query->execute()->fetchField();
  }

  return $node_id;
}
