<?php

function _verificate_users_requiremets_completed(){
    $message = '';
    $type = 'banrep_promoted';

    $entity_type = 'user';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user')
          ->propertyCondition('uid',0,'<>')
          ->propertyCondition('uid',19,'=');
    $users = $query->execute()['user'];
       
    foreach($users as $uid => $user){
        
        $user_entity = entity_metadata_wrapper($entity_type, $user->uid);
        dpm( $user_entity->name->value(), 'Validando usuario' );
        $message = 'Validating :'. $user_entity->name->value();
        watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        if(_validate_user_requirements($user_entity)){

        }
    }


}


function _validate_user_requirements($user_entity){

    /* Variables*/
    $message = '';
    $type = 'banrep_promoted';
    $validate = true;

    if( $user_requiremets = _load_requirements_for_user($user_entity)){
        
        /*Validate requiremets of points*/
        
        if(!_validate_requiremets_points( $user_entity,$user_requiremets) ){
            $message = 'user entity points requirement is not succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
            $validate = false;
        }else{
            $message = 'user entity points requirement is succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        }

        /* Validate Requirements of time*/

        if(_validate_requiremets_of_time($user_entity,$user_requiremets)){

        }

        
        return $validate;
    }

    return false;

}

function _validate_requiremets_of_time($user_entity,$user_requiremets){
    /* Variables*/
    $validate = true;
    $entity_type = 'field_collection_item';
    $field_collection_requirements = $user_requiremets->field_requisitos_tiempo->value();
    dpm($field_collection_requirements);
    if( !empty( $field_collection_requirements ) ){
        foreach( $field_collection_requirements as $key => $requirement ){
            $time_requirement = entity_metadata_wrapper('field_collection_item', $requirement->item_id );
            $type = $time_requirement->field_pcr_tipo_tiempo->value();
            $time = $time_requirement->field_pcr_tiempo->value();
            switch ($type) {
                case 'A': // years of experience
                    dpm($type);
                    dpm($time);
                    //get diference in years
                    $query_studies = new EntityFieldQuery();
                    $query_studies->entityCondition('entity_type', 'entityform')
                            ->entityCondition('bundle','user_training')
                            ->propertyCondition('uid', $user_entity->uid->value() ,'=');
                    $result = $query_studies->execute();
                    if( !empty( $result ) ) {
                        foreach($result as $key => $entity){
                            $study = entity_metadata_wrapper('entityform', $entity->item_id);
                            dpm($study);
                            // only validate study approved
                            if( $study->field_aprobado->value() ){
                                $now_diference = ($study->field_fecha_fin_estudio->value() - time()) / 31556926 % 12;
                                dpm($now_diference);
                                if( $now_diference < $time ){
                                    $validate = false;
                                }
                            }
                        }
                    }else{
                        $validate = false;
                    }
                    break;
                case 'B': // years of experience without external studies
                    dpm($type);
                    dpm($time);
                    $now_diference = ($user_entity->created->value() - time()) / 31556926 % 12; 
                    if( $now_diference < $time ){
                        $validate = false;
                    }
                    break;
                case 'C': //years of experience from last points
                    dpm($type);
                    dpm($time);
                    $now_diference = ( $user_entity->field_date_last_score->value() - time()) / 31556926 % 12;
                    if( $now_diference < $time ){
                        $validate = false;
                    }
                    break;
                case 'D': //years of experience from penultimate points
                    dpm($type);
                    dpm($time);
                    $now_diference = ( $user_entity->field_fecha_penultimo_puntaje->value() - time()) / 31556926 % 12;
                    if( $now_diference < $time ){
                        $validate = false;
                    }
                    break;
                default:
                    # code...
                    break;
            }
        }
    }
    dpm($validate);
    return $validate;
}


function _validate_requiremets_points($user_entity,$user_requiremets){
    $validate = true;

    if( $user_entity->field_puntaje_acumulado->value() < $user_requiremets->field_puntaje_acumulado->value() ){
        $validate = false;
    }

    if( $user_entity->field_puntaje_br->value() < $user_requiremets->field_puntaje_br->value() ){
        $validate = false;
    }

    if( $user_entity->field_acumulado_general->value() < $user_requiremets->field_acumulado_general->value() ){
        $validate = false;
    }

    return $validate;
}





function _load_requirements_for_user($user_entity){
    /*variables*/
    $entity_type = 'node';
    $scale = $user_entity->field_usr_escalafon->value()->tid;
    $route = $user_entity->field_ruta->value()->tid;


    if(!$scale || !$route){
        $message = 'user entity '.$user_entity->name->value().' is not configurated';
        $type = 'banrep_promoted';
        watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        return false;
    }       
    
     /* Search requirement for field_escalafon_actual*/
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle','requirements')
          ->fieldCondition('field_ruta_plan_carrera','tid', $route,'=')
          ->fieldCondition('field_escalafon_actual','tid', $scale,'=');
    $result = $query->execute();
    
    /* Return requirement object*/
    if(isset($result['node'])){
        
       return entity_metadata_wrapper($entity_type, key($result['node']));
    }
    
    /* Search requirement for field_escalafon_actual*/
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle','requirements')
          ->fieldCondition('field_ruta_plan_carrera','tid', $route,'=')
          ->fieldCondition('field_escalafon_final','tid', $scale,'=');
    $result = $query->execute();
    
     /*Return requirement object*/
    if(isset($result['node'])){
        return entity_metadata_wrapper($entity_type, key($result['node']));
    }

    return false;

} 