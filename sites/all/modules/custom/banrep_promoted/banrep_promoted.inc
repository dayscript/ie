<?php

function _verificate_users_requiremets_completed(){
    global $language;
    $language = $language->language;
    $message = '';
    $type = 'banrep_promoted';

    $entity_type = 'user';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user')
          ->propertyCondition('uid',0,'<>')
        //   ->propertyCondition('uid',19,'=');
         ->fieldCondition('field_estado_plan_carrera', 'value', 'MARCADO_PARA_ REVISION', '!=');
    $users = $query->execute()['user'];
       
    foreach($users as $uid => $user){
        
        $user_entity = entity_metadata_wrapper($entity_type, $user->uid);
        dpm( $user_entity->name->value(), 'Validando usuario' );
        $message = 'Validating :'. $user_entity->name->value();
        watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        if(_validate_user_requirements($user_entity)){
            for ($i=1; $i < 6 ; $i++) { 
                $to[] = variable_get('banrep_promoted_mail_'.$i);
            }
            drupal_mail('banrep_promoted', 'user_promoted', implode(',',$to), $language, $params = [ 'user' => $user_entity ], $from = NULL, $send = TRUE);
            $user_entity->field_estado_plan_carrera = 'MARCADO_PARA_ REVISION';
            $user_entity->save();
        }
    }
}

 
function _validate_user_requirements($user_entity){

    /* Variables*/
    $message = '';
    $type = 'banrep_promoted';
    

    if( $user_requiremets = _load_requirements_for_user($user_entity)){
        
        /*Validate requiremets of points*/
        
        if(!_validate_requiremets_points( $user_entity,$user_requiremets) ){
            $message = 'user entity points requirement is not succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
            return false;
        }else{
            $message = 'user entity points requirement is succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        }

        /* Validate Requirements of time*/

        if(!_validate_requiremets_of_time($user_entity,$user_requiremets)){
            $message = 'user entity time requirement is not succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
            return  false;
        }else{
            $message = 'user entity time requirement is succesfull';
            watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        }


        // if(!_validate_requirements_of_publications($user_entity,$user_requiremets)){
        //     $message = 'user entity publications requirement is not succesfull';
        //     watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        //     return false;
        // }else{
        //     $message = 'user entity publications requirement is succesfull';
        //     watchdog($type, $message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL); 
        // }
        
        return true;
    }

    return false;

}

function _validate_requirements_of_publications($user_entity,$user_requiremets){
    $validate = true;
    $entity_type = 'field_collection_item';
    $field_collection_requirements_publications = $user_requiremets->field_requisitos_publicaciones->value();
    if( !empty( $field_collection_requirements_publications ) ){
        foreach( $field_collection_requirements_publications as $key => $requirement_publication ){
            $publication_requirement = entity_metadata_wrapper('field_collection_item', $requirement_publication->item_id );
            $operator = $publication_requirement->field_operador->value();
            dpm($operator, 'operador');
            foreach($publication_requirement->field_condicion->value() as $key => $condition){
                $item_condition = entity_metadata_wrapper('field_collection_item', $condition->item_id );
                // only debug purposes
                $conditions[$key]['field_operador'] = $item_condition->field_operador->value();
                $conditions[$key]['field_tipo_requisito'] = $item_condition->field_tipo_requisito->value();
                $conditions[$key]['field_concept_type'] = $item_condition->field_concept_type->value();
                $conditions[$key]['field_serie'] =  $item_condition->field_serie->value();
                $conditions[$key]['field_cantidad_puntaje'] = $item_condition->field_cantidad_puntaje->value();
                
                $validate = _calc_results_of_condition($user_entity,$item_condition);
            }
            dpm($conditions,'conditions');

        }        
    
    }

    return $validate;
}

function _validate_requiremets_of_time($user_entity,$user_requiremets){
    /* Variables*/
    $validate = true;
    $entity_type = 'field_collection_item';
    $field_collection_requirements = $user_requiremets->field_requisitos_tiempo->value();
    
    if( !empty( $field_collection_requirements ) ){
        foreach( $field_collection_requirements as $key => $requirement ){
            $time_requirement = entity_metadata_wrapper('field_collection_item', $requirement->item_id );
            $type = $time_requirement->field_pcr_tipo_tiempo->value();
            $time = $time_requirement->field_pcr_tiempo->value();
            switch ($type) {
                case 'A': // years of experience
                    // dpm($type);
                    // dpm($time);
                    //get diference in years
                    $query_studies = new EntityFieldQuery();
                    $query_studies->entityCondition('entity_type', 'entityform')
                            ->entityCondition('bundle','user_training')
                            ->propertyCondition('uid', $user_entity->uid->value() ,'=');
                    $result = $query_studies->execute();
                    if( !empty( $result['entityform'] ) ) {
                        foreach($result['entityform'] as $key => $entity){
                            $study = entity_metadata_wrapper('entityform', $entity->entityform_id)->field_studies_carried_out->value();
                            $study = entity_metadata_wrapper('field_collection_item', $study[0]->item_id);
                            // only validate study approved
                            if( $study->field_aprobado->value() ){
                                $now_diference = ( time() - $study->field_fecha_fin_estudio->value() ) / 31556926 % 12;
                                
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
                    // dpm($type);
                    // dpm($time);
                    $now_diference = ( time() - $user_entity->created->value() ) / 31556926 % 12; 
                    if( $now_diference < $time ){
                        $validate = false;
                    }
                    break;
                case 'C': //years of experience from last points
                    // dpm($type);
                    // dpm($time);
                    $now_diference = ( time() - $user_entity->field_date_last_score->value() ) / 31556926 % 12;
                    if( $now_diference < $time ){
                        $validate = false;
                    }
                    break;
                case 'D': //years of experience from penultimate points
                    // dpm($type);
                    // dpm($time);
                    $now_diference = ( time() - $user_entity->field_fecha_penultimo_puntaje->value() ) / 31556926 % 12;
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
    // dpm($validate);
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

function _calc_results_of_condition($user_entity,$item_condition){
    $validate = true;
    $user_points = 0;
    // $item_condition->field_operador->value();
    // $item_condition->field_tipo_requisito->value();
    // $item_condition->field_concept_type->value();
    // $item_condition->field_serie->value();
    // $item_condition->field_cantidad_puntaje->value();

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle','pub_user')
        ->fieldCondition('field_user_reference','target_id',$user_entity->uid->value(),'=');
    $result = $query->execute();
    $user_pubs = array_keys($result['node']);

    switch ($item_condition->field_tipo_requisito->value()) {
        case 'CANTIDAD':
            foreach($user_pubs as $key => $nid){
                $query = db_query( 'SELECT * FROM 
                                    { field_data_field_concept_type } concept 
                                    where concept.entity_id = :nid 
                                    and field_concept_type_tid = :tid', array(':nid' => $nid, ':tid' => $item_condition->field_concept_type->value()[0]->tid ));
                  
                if( $query->rowCount() < $item_condition->field_cantidad_puntaje->value() ){
                    return false;
                }
            }
            break;
        
        case 'PUNTAJE':
            foreach($user_pubs as $key => $nid){
                $query = db_query( 'SELECT * FROM 
                                    { field_data_field_concept_type } concept 
                                    where concept.entity_id = :nid 
                                    and field_concept_type_tid = :tid', array(':nid' => $nid, ':tid' => $item_condition->field_concept_type->value()[0]->tid ));
                  
                if( $query->fetchObject() ) {
                    $pub_user_requiremnt = entity_metadata_wrapper('node', $nid );
                    $user_points += $pub_user_requiremnt->field_puntaje->value();
                }
            }

            if($user_points <= $item_condition->field_cantidad_puntaje->value() ){
                return false;
            }

            break;
        
        default:
            # code...
            break;
    }    


    return $validate;
}

function _banrep_promoted_mails_form($form_state, $variable){

    
    for ($i=1; $i < 6; $i++) { 
        $form['current_posts_max']['banrep_promoted_mail_'.$i] = array(
            '#type' => 'textfield',
            '#title' => t('Direccion de correo No '.$i),
            '#default_value' => variable_get('banrep_promoted_mail_'.$i, null),
            '#size' => 50,
            '#maxlength' => 50,
            '#description' => t('Escriba una direccion de correo electronico'),
            '#required' => FALSE,
          );
    }
    return system_settings_form($form);

}