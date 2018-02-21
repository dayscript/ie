<?php


class IndexNodeMigration extends Migration {
  public $debug = false;
  public $ignore_file = false;

  public function __construct($arguments) {
		parent::__construct($arguments);
    $fields = array(
	    0 => array('title', 'Titulo del indice'),
	    1 => array('index_url', 'Url del indice'),
    );
    $this->description = t('CSV feed (pull) of Contenido tipo Vinculo');
    //The Source of the import
    //$path = variable_get('contenido_csv_path', 'public://migration/contenido.csv');
    $path = 'public://migrate/indices.csv';
    $this->source = new MigrateSourceCSV($path, $fields, array('header_rows' => 1));
    // Set up our destination - nodes of type page
    $this->destination = new MigrateDestinationNode('vinculo');
    // The source ID here is the one retrieved from each data item in the XML
    // file, and used to identify specific items
    $this->map = new MigrateSQLMap($this->machineName, array('title' => array('type' => 'varchar', 'length' => 255, 'description' => 'Contenido ID.', 'not null' => TRUE)), MigrateDestinationNode::getKeySchema());
    // Field Title <Texto>;
    $this->addFieldMapping('title', 'title'); // Field Title
    // Field Title <Texto>;
    $this->addFieldMapping('field_url_indice', 'index_url'); // Field Title
    $this->addFieldMapping('field_estado_vinculo')->defaultValue(11); // Field Title

	}
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $this->fieldMappingToIndice($row);
    //return FALSE;
  }
	public function fieldMappingToIndice($row){

  	$row->uid = 1;
	}
/*
   * The Migration class complete() method is analogous to prepare(), but is called immediately after the complete
   * destination object is saved.
   */
 	public function complete($entity, stdClass $row) {
 		//dpm($row);
   		$node = $entity;
   		//dpm($node);
  }
}



