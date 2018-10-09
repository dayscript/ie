<?php

require_once dirname(__FILE__) . '/../banrep_migration_helper.inc';
class UsersMigration extends Migration {
  public $insert;
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->insert = ($arguments['machine_name'] === 'InsertarUsuarios');

    $fields = array(
      'usuario' => 'usuario',
      'correo' => 'correo',
      'contrasena' => 'contrasena',
      'estado' => 'estado',
      'rol' => 'rol',
      'apellidos' => 'apellidos',
      'nombres' => 'nombres',
      'firma' => 'firma',
      'tipodocumento' => 'tipodocumento',
      'cedula' => 'cedula',
      'genero' => 'genero',
      'ciudad' => 'ciudad',
      'ingreso' => 'ingreso',
      'cargo' => 'cargo',
      'departamento' => 'departamento',
      'puntajecargo' => 'puntajecargo',
      'fechacargo' => 'fechacargo',
      'fechaultimopuntaje' => 'fechaultimopuntaje',
    );
    $this->description = t('Json de usuarios');
    $file_uri = 'public://migration/usuarios-banrep.json';
    $this->source = new MigrateSourceJSON(format_json($file_uri), 'usuario', $fields);
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'cedula' => array(
          'type' => 'varchar',
          'length' => 255,
          'description' => 'Usuario',
          'not null' => TRUE)
      ),
      MigrateDestinationUser::getKeySchema()
    );
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('name', 'usuario');
    $this->addFieldMapping('mail', 'correo');
    $this->addFieldMapping('pass', 'contrasena');
    $this->addFieldMapping('field_email_personal', 'correo');
    $this->addFieldMapping('status', 'estado');
    $this->addFieldMapping('roles', 'rol');
    $this->addFieldMapping('field_full_name', 'firma');
    $this->addFieldMapping('field_names', 'nombres');
    $this->addFieldMapping('field_surnames', 'apellidos');
    $this->addFieldMapping('field_document_type', 'tipodocumento');
    $this->addFieldMapping('field_document_number', 'cedula');
    $this->addFieldMapping('field_genre', 'genero');
    $this->addFieldMapping('field_city', 'ciudad');
    $this->addFieldMapping('field_city:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_date_admission', 'ingreso');
    $this->addFieldMapping('field_position', 'cargo');
    $this->addFieldMapping('field_position:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_dependency', 'departamento');
    $this->addFieldMapping('field_dependency:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_score', 'puntajecargo');
    $this->addFieldMapping('field_date_position', 'fechacargo');
    $this->addFieldMapping('field_date_last_score', 'fechaultimopuntaje');

    if (!$this->insert) {
      $this->systemOfRecord = Migration::DESTINATION;
    }
  }
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $user = user_load_by_mail($row->correo);
    // Inserta, pero el usuario existe
    if ($this->insert && $user !== FALSE) {
      return FALSE;
    }
    // Actualiza
    elseif (!$this->insert) {
      if ($user === FALSE) {
        return FALSE;
      }
      $row->uid = $user->uid;
    }
    // Estado: Activo o vacío
    $row->estado = (strtolower($row->estado) === 'activo' ? 1 : 0);
    // Rol: TECNICO, INVESTIGADOR o vacío
    $role = user_role_load_by_name(strtolower($row->rol));
    $row->rol = NULL;
    if ($role !== FALSE) {
      $row->rol = array($role->rid);
    }
    $row->tipodocumento = 'cc';
    // Nombres: Nombres, separados por espacio, mayúscula por palabra
    $row->nombres = trim($row->nombres);
    $row->apellidos = trim($row->apellidos);
    // Firma: Tejada-Guevara, Carlos Eduardo
    // $row->firma = $row->apellidos . ', ' .$row->nombres;
    // Tipo de documento: CC, etc [List (text)]
    $row->tipo_documento = strtolower($row->tipo_documento);
    // Género: FEM o MAS [List (text)]
    $row->genero = (strtolower($row->genero) === 'Femenino' ? 'female' : 'male');
    // Ciudad: Nombre [Term reference]
    $term = taxonomy_get_term_by_name($row->ciudad, 'cities');
    $row->ciudad = NULL;
    if (!empty($term)) {
      $term = array_shift($term);
      $row->ciudad = $term->tid;
    }
    // Cargo: Nombre [Term reference]
    $term = taxonomy_get_term_by_name($row->cargo, 'cargos');
    $row->cargo = NULL;
    if (!empty($term)) {
      $term = array_shift($term);
      $row->cargo = $term->tid;
    }
    // Departamento: Nombre [Term reference]
    $term = taxonomy_get_term_by_name($row->departamento, 'dependencies');
    $row->departamento = NULL;
    if (!empty($term)) {
      $term = array_shift($term);
      $row->departamento = $term->tid;
    }
    // Fecha de ingreso al banco: m/d/yyyy [Unix]
    $row->ingreso = explode('/', $row->ingreso);
    if ($row->ingreso[0] < 10) {
      $row->ingreso[0] = '0' . $row->ingreso[0];
    }
    if ($row->ingreso[1] < 10) {
      $row->ingreso[1] = '0' . $row->ingreso[1];
    }
    $row->ingreso[] = array_shift($row->ingreso);
    $row->ingreso[] = array_shift($row->ingreso);
    $row->ingreso = strtotime(implode('-', $row->ingreso));

    // Fecha de ingreso al cargo: m/d/yyyy [POR_DEFINIR]
    $row->fechacargo = explode('/', $row->fechacargo);
    if ($row->fechacargo[0] < 10) {
      $row->fechacargo[0] = '0' . $row->fechacargo[0];
    }
    if ($row->fechacargo[1] < 10) {
      $row->fechacargo[1] = '0' . $row->fechacargo[1];
    }
    $row->fechacargo[] = array_shift($row->fechacargo);
    $row->fechacargo[] = array_shift($row->fechacargo);
    $row->fechacargo = strtotime(implode('-', $row->fechacargo));

    // Fecha del último puntaje: d-mm-yyyy [POR_DEFINIR]
    $row->fechaultimopuntaje = explode('-', $row->fechaultimopuntaje);
    $row->fechaultimopuntaje = $row->fechaultimopuntaje[2] . '-' . $row->fechaultimopuntaje[1] . '-' . $row->fechaultimopuntaje[0];

    return TRUE;
  }
}
