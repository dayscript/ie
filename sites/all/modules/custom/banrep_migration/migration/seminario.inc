<?php

module_load_include('inc', 'banrep_migration', 'banrep_migration_helper');

class EventsSeminarNodeMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $fields = array(
      'nid' => 'nid',
      'titulo' => 'titulo',
      'body' => 'body',
      'field_serie_event' => 'consulte_eventos_de_la_misma_serie',
      'ciudad' =>'ciudad',
      'expositor' => 'expositor',
      'field_language' => 'Language',
      'field_inscripcion' => 'Inscription',
      'fecha' => 'fecha',
      'fecha_inicio' => 'fecha_inicio',
      'fecha_final' => 'fecha_final',
    );

    $this->description = t('JSON feed (pull) of Contenido tipo Eventos (Seminario)');
    //The Source of the import

    $file_uri = variable_get('MIGRATE_EVENTS', 'http://www.banrep.gov.co/es/expose-events/json');
    // $file_uri = 'public://migrate/seminarios.json';
    $file_uri_format = format_json($file_uri);

    $this->source = new MigrateSourceJSON($file_uri_format, 'nid', $fields);

    // Set up our destination - nodes of type Event
    $this->destination = new MigrateDestinationNode('event');

    // The source ID here is the one retrieved from each data item in the XML
    // file, and used to identify specific items
    $this->map = new MigrateSQLMap($this->machineName, array('nid' => array('type' => 'varchar', 'length' => 255, 'description' => 'Contenido ID.', 'not null' => TRUE)), MigrateDestinationNode::getKeySchema());

    // Field Title <Texto>;
    $this->addFieldMapping('title', 'titulo'); // Field Title

    // Field Body <Texto largo y formato>;
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format', 'body_format');

    // Field Serie Event <Texto>;
    $this->addFieldMapping('field_serie_de_evento', 'field_serie_event'); // Field Serie de evento
    $this->addFieldMapping('field_serie_de_evento:source_type')->defaultValue('target_id');

    $this->addFieldMapping('field_exhibitor_name', 'expositor'); // Field Serie de evento
    $this->addFieldMapping('field_place', 'ciudad'); // Field Serie de evento

    $this->addFieldMapping('field_tipo_de_evento:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_tipo_de_evento')->defaultValue(SEMINARIOS_TID);

    $this->addFieldMapping('field_url_archivo_historial:source_type')->defaultValue('url');
    $this->addFieldMapping('field_url_archivo_historial')->defaultValue('');


    $this->addFieldMapping('field_languages')->defaultValue('spa');
    $this->addFieldMapping('field_inscripcion:source_type')->defaultValue('url');
    $this->addFieldMapping('field_inscripcion')->defaultValue('http://quimbaya.banrep.gov.co:8080/seminarios/');

    $this->addFieldMapping('field_event_date', 'date_from');
    $this->addFieldMapping('field_event_date:to', 'date_to');
    $this->addFieldMapping('field_event_date:timezone', 'date_timezone');

    // System Fields.
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('changed', 'current_time');

  }

  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $row->uid = 1;
    $row->status = 1;
    $row->body_format = "rich_text"; // Full HTML
    if( isset($row->consulte_eventos_de_la_misma_serie) && !empty($row->consulte_eventos_de_la_misma_serie) ){
      // Seminario Semanal de Economía
      $row->consulte_eventos_de_la_misma_serie = find_serie_de_evento($row->consulte_eventos_de_la_misma_serie);
    }
    $row->date_timezone = 'America/Bogota';
    if(isset($row->fecha_inicio) && !empty($row->fecha_inicio) ){
      $fecha_ini = str_replace('"', "", $row->fecha_inicio);
      $row->date_from = strtotime($fecha_ini);
    }
    if(isset($row->fecha_final) && !empty($row->fecha_final) ){
      $fecha_fin = str_replace('"', "", $row->fecha_final);
      $row->date_to = strtotime($fecha_fin);
    }
    // if(isset($row->fecha) && !empty($row->fecha) ){
    //     $fecha = str_replace('"', "", $row->fecha);
    //     $row->date_from = strtotime($fecha);
    //     $row->date_to = NULL;
    //     $row->date_timezone = 'America/Bogota';
    // }

    $body_copy = $row->body;
    $body_copy = str_replace('<p> </p>', '',  $body_copy);
    $body_copy = str_replace('<p></p>', '', $body_copy);
    $body_copy = str_replace('<p>&nbsp;</p>>', '', $body_copy);
    $body_copy = str_replace('<div>&nbsp;</div>', '', $body_copy);
    $body_copy = str_replace('<div> </div>', '', $body_copy);
    $row->body = str_replace('\n', '', $body_copy);

    $row->original_nid = $row->nid;
    $row->current_time = time();
  }

  /*
   * The Migration class complete() method is analogous to prepare(), but is called immediately after the complete
   * destination object is saved.
   */
  public function complete($entity, stdClass $row) {
    //dpm($row);
      $node = $entity;
      if( !is_null($row->consulte_eventos_de_la_misma_serie) ){
        $node->field_serie_de_evento['und'][0]['target_id'] = $row->consulte_eventos_de_la_misma_serie;
        if(isset($node->body['und'][0]['value'])){
          $node->body['und'][0]['value'] = str_replace('<div> </div>', '', $node->body['und'][0]['value']);
          $node->body['und'][0]['value'] = str_replace('<div>&nbsp;</div>', '', $node->body['und'][0]['value']);
          $node->body['und'][0]['value'] = str_replace('<p>&nbsp;</p>', '', $node->body['und'][0]['value']);
          $node->body['und'][0]['value'] = str_replace('<span>&nbsp;</span>', '', $node->body['und'][0]['value']);
          $body = $node->body['und'][0]['value'];
          $pdfs = getPdfUrlsFormString($body);
          if(!empty($pdfs) && is_array($pdfs)){
            $node->field_url_archivo_historial['und'][0]['url'] = reset($pdfs);
          }
        }
        node_save($node);
      }

  }

}
