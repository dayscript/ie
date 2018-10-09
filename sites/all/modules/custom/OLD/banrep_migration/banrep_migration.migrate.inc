<?php

/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/**
 * Implements of hook migrate_api().
 */
function banrep_migration_migrate_api() {
  $translate_mapping = new MigrateFieldMapping('translate', NULL);
  $translate_mapping->defaultValue(0);

  $api = array(
    'api' => 2,
    'groups' => array(
      'seminars' => array(
        'title' => t('Importar Contenido Tipo Evento (Seminario) '),
      ),
      // 'jel' => array(
      //   'title' => t('Importar Códigos JEL '),
      // ),
      // 'externos' => array(
      //   'title' => t('Importar Usuarios Externos'),
      // ),
      // 'concepts' => array(
      //   'title' => t('Importar Contenido Tipo Concepto'),
      // ),
      // 'publications' => array(
      //   'title' => t('Importar Publicaciones Investigadores'),
      // ),
      // 'users' => array(
      //   'title' => t('Importar Usuarios'),
      // ),
    ),
    'migrations' => array(
      'Seminarios' => array(
        'class_name' => 'EventsSeminarNodeMigration',
        'group_name' => 'seminars'
      ),
      // 'JEL' => array(
      //   'class_name' => 'CodesJELTermMigration',
      //   'group_name' => 'jel'
      // ),
      // 'Externos' => array(
      //   'class_name' => 'ExternalUsersTermMigration',
      //   'group_name' => 'externos'
      // ),
      // 'Conceptos' => array(
      //   'class_name' => 'ConceptsNodeMigration',
      //   'group_name' => 'concepts'
      // ),
      // 'Publicaciones' => array(
      //   'class_name' => 'PublicacionesNodeMigration',
      //   'group_name' => 'publications'
      // ),
      // 'InsertarUsuarios' => array(
      //   'class_name' => 'UsersMigration',
      //   'group_name' => 'users'
      // ),
      // 'ActualizarUsuarios' => array(
      //   'class_name' => 'UsersMigration',
      //   'group_name' => 'users'
      // ),
    ),
  );
  return $api;
}
