<?php
define('REQ_FORMATION_ID_DESEMPENO',15343);
define('REQ_FORMATION_ID_FORMACION',15339);



function banrep_training_get_user_requiremets($scale,$route){
    $requiremets = [];

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'requirements')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_ruta_plan_carrera', 'tid', $route, '=')
        ->fieldCondition('field_escalafon_actual', 'tid', $scale, '=');
    $result_escalafon_actual = $query->execute();
    
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'requirements')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_ruta_plan_carrera', 'tid', $route, '=')
        ->fieldCondition('field_escalafon_final', 'tid', $scale, '=');

    $result_escalafon_final = $query->execute();

    if(!is_null($result_escalafon_actual['node'])){
        $requiremets[] = $result_escalafon_actual['node'][key($result_escalafon_actual['node'])];
    }
    if(!is_null($result_escalafon_final['node'])){
        $requiremets[] = $result_escalafon_final['node'][key($result_escalafon_final['node'])];
    }
    return $requiremets;
}

