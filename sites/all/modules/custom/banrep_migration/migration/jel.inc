<?php


class CodesJELTermMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $fields = array(
      0 => array('code', 'code'),
      1 => array('ingles', 'ingles'),
      2 => array('espanol', 'espanol'),
    );
    $this->description = t('CSV feed (pull) of JEL Codes');
    $path1 = 'public://jel.json';
    $this->source = new MigrateSourceJSON($path1, 'code', $fields);
    $this->destination = new MigrateDestinationTerm('jel');
     $this->map = new MigrateSQLMap($this->machineName,
        array(
          'code' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'description' => 'Varchar.',
          ),
        ),
        MigrateDestinationTerm::getKeySchema()
      );


    $this->addFieldMapping('name', 'code');
    $this->addFieldMapping('field_jel_code', 'code');
    $this->addFieldMapping('field_title_en', 'ingles');
    $this->addFieldMapping('field_title_es', 'espanol');

  }
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
  }

/*
   * The Migration class complete() method is analogous to prepare(), but is called immediately after the complete
   * destination object is saved.
   */
  public function complete($entity, stdClass $row) {
      $term = $entity;
  }
}



