<?php


class ExternalUsersTermMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $fields = array(
      0 => array('nombrecompleto', 'nombrecompleto'),
      1 => array('apellidos', 'apellidos'),
      2 => array('nombres', 'nombres'),
    );
    $this->description = t('CSV feed (pull) of External Users');
    $path1 = 'public://migrate/externos.json';
    $this->source = new MigrateSourceJSON($path1, 'nombrecompleto', $fields);
    $this->destination = new MigrateDestinationTerm('autores_externos');
     $this->map = new MigrateSQLMap($this->machineName,
        array(
          'nombrecompleto' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'description' => 'Varchar.',
          ),
        ),
        MigrateDestinationTerm::getKeySchema()
      );


    $this->addFieldMapping('name', 'nombrecompleto');
    $this->addFieldMapping('field_surnames', 'apellidos');
    $this->addFieldMapping('field_names', 'nombres');

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



