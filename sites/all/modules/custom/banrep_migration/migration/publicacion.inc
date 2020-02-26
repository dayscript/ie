<?php

require_once dirname(__FILE__) . '/../banrep_migration_helper.inc';
class PublicationsNodeMigration extends Migration {
  public $debug = false;
  public $ignore_file = false;

  public function __construct($arguments) {
		parent::__construct($arguments);
    $fields = array(
	    0 => array('categoria', 'Categoria Concepto'),
	    1 => array('tipo_concepto', 'Tipo Concepto'),
	    2 => array('title', 'Nombre'),
	    3 => array('notes', 'Notas'),
	    4 => array('isbn', 'ISBN'),
	    5 => array('issn', 'ISSN'),
	    6 => array('doi', 'DOI url'),
	    7 => array('index', 'Indice'),
    );
    $this->description = t('JSON feed (pull) of Contenido tipo Eventos (Seminario)');
    //The Source of the import
    //$path = variable_get('contenido_csv_path', 'public://migration/contenido.csv');
    $path = 'public://migrate/conceptos.csv';
    $this->source = new MigrateSourceCSV($path, $fields, array('header_rows' => 1));
    // Set up our destination - nodes of type page
    $this->destination = new MigrateDestinationNode('concept');
    // The source ID here is the one retrieved from each data item in the XML
    // file, and used to identify specific items
    $this->map = new MigrateSQLMap($this->machineName, array('title' => array('type' => 'varchar', 'length' => 255, 'description' => 'Contenido ID.', 'not null' => TRUE)), MigrateDestinationNode::getKeySchema());
    // Field Title <Texto>;

    $this->addFieldMapping('field_concept_category');
    $this->addFieldMapping('field_index');
    // $this->addFieldMapping('field_concept_category')->defaultValue(array(201,202));


    //$this->addFieldMapping('')->defaultValue(array('tid' => 201))); // Field Title
    // $this->addFieldMapping('tipo_concepto', 'tipo_concepto'); // Field Title
    $this->addFieldMapping('title', 'title'); // Field Title
    $this->addFieldMapping('field_notes', 'notes'); // Field Title
    $this->addFieldMapping('field_isbn', 'isbn'); // Field Title
    $this->addFieldMapping('field_issn', 'issn'); // Field Title
    $this->addFieldMapping('field_doi', 'doi'); // Field Title
    $this->addFieldMapping('field_concept_source')->defaultValue('sistema'); // Field Title
    $this->addFieldMapping('field_estado_concepto')->defaultValue(7); // Field Title
    //$this->addFieldMapping('field_index'); // Field Title
    //$this->addFieldMapping('index', 'index'); // Field Title

	}

  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

   $row->uid = 1;

  }

	public function prepare(stdClass $entity, stdClass $current_row) {
		$tids = _get_concept_category($current_row->tipo_concepto);
    $index = _get_index_nid($current_row->index);
		$entity->field_concept_category['und'] = $tids;
    if (!empty($index)) {
      dpm($index);

      $entity->field_index['und'][]['target_id'] = $index;
      dpm($entity);
      //dpm();
    }

	}


  /*
  * The Migration class complete() method is analogous to prepare(), but is called immediately after the complete
  * destination object is saved.
  */
 	public function complete($entity, stdClass $row) {
   		$node = $entity;
  }
}



