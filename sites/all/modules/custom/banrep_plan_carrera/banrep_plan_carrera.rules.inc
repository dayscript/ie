
<?php

function prof_lider_430($uid){
    $response = FALSE;

    $entity_user = user_load($uid);
    //Cuatro artículos publicados en la serie de Borradores de Economía 
    $economy = contar_nodes($uid, 4, 'pub_user', 'Borradores de Economia');
    //o en la serie Documentos de Economía Regional 
    $regionalEcon = contar_nodes($uid, 4, 'pub_user', 'Ensayos Sobre Economía Regional (ESER)');
    //o 14 puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera. 
    $puntajeAcademico = user_points($entity_user->field_puntaje_acumulado, 14);
    //El puntaje de estas publicaciones será asignado según los criterios del plan de carrera.
    $puntajes = FALSE;
    if($economy || $regionalEcon || $puntajeAcademico){
        $puntajes = TRUE;
    }

    //Acumular un total de 30 puntos BR de acuerdo con el listado de puntajes aprobado para el plan de carrera.
    $puntajeBR = user_points($entity_user->field_puntaje_br, 30);
    // Los dos requisitos anteriores rigen desde el momento en que fue nombrado en el cargo de Profesional Experto. 

    // El tiempo acumulado de experiencia desde su nombramiento como Profesional debe ser mínimo 7 años sin contar con los años de estudio en el exterior.
    // ID 212 => Taxonomia => Profesional
    $time = calc_position_corp($entity_user, 212, 7);
    if($economy && $puntajes && $puntajeBR && $time){
        $response = TRUE;
    }
    return $response;
}
 
function invs_junior_494($uid){
    $response = FALSE;
    $entity_user = user_load($uid);
    // Inmediatamente tenga el título de doctorado en Economía.
    $degrees = degrees($entity_user->field_studies_carried_out, 'doctorado');
    // Acumular 30 puntos, de los cuales al menos 20 deben corresponder a puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera.
    $puntajeAcademico = user_points($entity_user->field_puntaje_acumulado, 30);
    // El tiempo acumulado de experiencia desde su nombramiento como Profesional deber ser mínimo de 9 años sin contar con los años de estudio en el exterior. 
    // ID 212 => Taxonomia => Profesional
    $time = calc_position_corp($entity_user, 212, 9);
    dpm($degrees,'a');
    dpm($puntajeAcademico,'b');
    dpm($time,'c');
    if($degrees && $puntajeAcademico && $time ){
        $response = TRUE;
    }
    return $response;
}

function invs_568($uid){
    $response = FALSE;
    $entity_user = user_load($uid);
    // 3 años en el cargo de Investigador Júnior.
    // 215 -> Taxonomia -> Investigador Junior
    $time = calc_position_corp($entity_user, 215, 3);
    
    //Acumular 40 puntos. Al menos 14 deben corresponder a puntos BR.
    $puntajeAcademico = user_points($entity_user->field_puntaje_acumulado, 26);
    $puntajeBR = user_points($entity_user->field_puntaje_br, 14);

    if($puntajeBR && $puntajeAcademico && $time ){
        $response = TRUE;
    }
    return $response;
}

function invs_ppal_654($uid){
    $response = FALSE;
    $entity_user = user_load($uid);
    // 5 años en el cargo de Investigador
    // 216 -> Taxonomia -> Investigador
    $time = calc_position_corp($entity_user, 216, 5);
    // Acumular 100 puntos: 
   
    ////Al menos 50 deben ser BR 
    $puntajeBR = user_points($entity_user->field_puntaje_br, 14);
    //// Por lo menos 30 académicos por publicaciones en revistas de alto impacto (Grupos ISI 1, 2 y 3). 
    $puntajeAcademico = user_points($entity_user->field_puntaje_acumulado, 26);

    //Los cuales se acumulan desde el su nombramiento como Investigador Júnior 
    //TODO

    if($puntajeBR && $puntajeAcademico && $time ){
        $response = TRUE;
    }
    return $response;
    
}

function prof_expert_375($uid){
    $response = FALSE;

    $entity_user = user_load($uid);
    // Tres artículos publicados en la serie de Borradores de Economía
    $economy = contar_nodes($uid, 3, 'pub_user', 'Borradores de Economia');
    // o en la serie Documentos de Economía Regional 
    $regionalEcon = contar_nodes($uid, 3, 'pub_user', 'Ensayos Sobre Economía Regional (ESER)');
    //o 7 puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera.
    $puntajeAcademico = user_points($entity_user->field_puntaje_acumulado, 7);
    //El puntaje de estas publicaciones será asignado según los criterios del plan de carrera. 
    $puntajes = FALSE;
    if($economy || $regionalEcon || $puntajeAcademico){
        $puntajes = TRUE;
    }

    //Acumular un total de 15 puntos BR de acuerdo con el listado de puntajes aprobado para el plan de carrera. 
    $puntajeBR = user_points($entity_user->field_puntaje_br, 15);
    //Los dos anteriores requisitos rigen desde el momento en que fue nombrado en el cargo de Profesional Especializado. 
    //TODO 

    //Contar con título de maestría en el país o en el exterior. 
    $degrees = degrees($entity_user->field_studies_carried_out, 'maestria');
    // El tiempo acumulado de experiencia desde su nombramiento como profesional debe ser mínimo de 5 años 
    // ID 212 => Taxonomia => Profesional
    $time = calc_position_corp($entity_user, 212, 5);
    //sin contar con los años de estudio en el exterior.
    //TODO

    if($puntajes && $puntajeBR && $degrees && $time ){
        $response = TRUE;
    }
    return $response;
}


function contar_nodes($uid, $num, $type, $filter) {
    $response = FALSE;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', $type)
    ->fieldCondition('field_user_reference', 'target_id', $uid)
    ->fieldCondition('field_estado_publicaci_n', 'value', APROBADO);
    // ->fiedlCondition('field_pub_type', 'value', $type)

    $result = $query->execute();
    $nids = array_keys($result['node']);
    $data = node_load_multiple($nids);
    
    $contador = 0;
    foreach ($data as $key => $value) {
        foreach ($value as $k => $v) {
            if ($k == 'field_publicacion') {
                $publi = node_load($v[LANGUAGE_NONE][0]['target_id']);
                foreach ($publi as $title => $valor) {
                    if($title == 'field_pub_serie'){
                        if ($valor[LANGUAGE_NONE][0]['value'] == $filter) {
                            $contador ++;
                        }
                    }
                }
            }
        }
    }

    if($contador >= $num){
        $response = TRUE;
    }
    return $response;
}

function user_points($field, $num) {
    $response = FALSE;

    if(isset($field[LANGUAGE_NONE])){
        if($field[LANGUAGE_NONE][0]['value'] >= $num){
            $response = TRUE;
        }
    }
    return $response;
}

function calculate_date($dateTimestamp, $num){
    $response = FALSE;
    $format = date("Y-m-d", $dateTimestamp);
    $newDate = New DateTime($format);
    $hoy = new DateTime();
    $annos = $hoy->diff($newDate);

    if($annos->y >= $num){
        $response = TRUE;
    } 
    return $response;
}

function degrees($field, $title){
    // doctorado|Doctorado
    // doctorado_c|Doctorado ( c )
    // maestria|Maestría
    // phd|Phd
    // especializacion|Especialización
    // pregrado|Pregrado
    // cursos|Cursos
    $response = FALSE;
    foreach ($field[LANGUAGE_NONE] as $key => $val) {
        $getField = field_collection_item_load($val['value']);
        if(isset($getField->field_nivel_estudio['und'])){
            if($getField->field_nivel_estudio['und'][0]['value'] == $title){
                $response = TRUE;
                break;
            }
        }

    }
    return $response;
    
}

function calc_position_corp($user_entity, $idTaxPos, $num){
    $response = FALSE;
    $isPosition = FALSE;
    // Calcula el cargo de la empresa
  
    if(isset($user_entity->field_position['und'])){
        foreach ($user_entity->field_position['und'] as $key => $val) {
            if($val['tid'] == $idTaxPos){
                $isPosition = TRUE;
                break;
            }
        }
    }

    // Calcula el tiempo 
    $isTime = FALSE;
    if($user_entity->field_date_position['und']){
        $isTime = calculate_date($user_entity->field_date_position['und'][0]['value'], $num);
    }
    
    if($isTime && $isPosition){
        $response = TRUE;
    }
    return $response;
}

function validate_change_state($uid){
    $response = FALSE;
    
    $entity_user = user_load($uid);
    if(!empty($entity_user->field_usr_escalafon['und'])){
        // Obtener el escalofon al que pertenece
        $escalafonUser = $entity_user->field_usr_escalafon['und'][0]['tid'];
        // Obtener el plan de carrera 
        $planUser = !empty($entity_user->field_ruta) ? $entity_user->field_ruta['und'][0]['target_id'] : null;
        //Buscar ese esfalafon en Requisitos
        $serchTo = getRequirements($escalafonUser, $planUser);
        if(!empty($serchTo)) {
            foreach ($serchTo[key($serchTo)] as $key => $value) {
                //Obtener el eslafon inicial de la busqueda realizada
                
                //foreach ($value as $k => $val) {
                if($key == 'field_escalafon_final'){
                    if (isset($val['und'])) {
                        $response = homologo_requirements($uid, $value['und'][0]['tid']);
                        break;
                    }
                }
                //}

            }
        }
        // Evaluar respuesta positiva 
        if($response){
            // Cambiar de estado en el usuario
            // MARCADO_PARA_ REVISION|MARCADO PARA REVISIÓN
            update_fields($entity_user, 'MARCADO_PARA_ REVISION', 'field_estado_plan_carrera');
            //Notificar email
            send_email($entity_user, 'sblancca@banrep.gov.co');

        }
    }
}

function getRequirements($idScal, $idPlan){
    $response = FALSE;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'requirements')
    ->fieldCondition('field_escalafon_actual', 'tid', $idScal)
    ->fieldCondition('field_ruta_plan_carrera', 'tid', $idPlan);
    

    $result = $query->execute();
    if(!empty($result)) {
        $nids = array_keys($result['node']);
        $data = node_load_multiple($nids);

        return $data;
    }
}

function homologo_requirements($uid, $idScal){
    $response = FALSE;

    // Nombre PN 494 - 568 -> Actual = 20663 -> Final = 20664
    // Nombre PN 568 - 654-> Actual = 20664 -> Final = 20666
    // Nombre PN 430 - 494-> Actual = 20665 -> Final = 20663
    // Nombre PN 375 - 430> Actual = 15349 -> Final = 20665
    // Nombre PN 327 - 375> Actual = 15348 -> Final = 15349
    // Nombre Ruta de investigación - 350> Actual = 15347 -> Final = 20665
    // Nombre PA 327-375 > Actual = 15348 -> Final = 15349
    // Nombre RT 568-654> Actual = 20664 -> Final = 20666
    // Nombre PPI - Investigador Ppal. = 20666 -> Final = 20666

    // Pasarlo por el escalafon correpondiente y vallidarlo
    dpm( 'idScal',$idScal );
    switch ($idScal) {
        case 20664:
            $response = invs_568($uid);
            break;
        case 20666:
            $response = invs_ppal_654($uid);
            break;
        case 20663:
            $response = invs_junior_494($uid);
            break;
        case 20665:
            $response = prof_lider_430($uid);
            break;
        case 15349:
            $response = prof_expert_375($uid);
            break;
    }
    return $response;
}

function send_email($user, $email){
    $message = 'El usuario ' . $user->name . ' ha cambiado de estado por que cumple con las reglas requeridas para un asenso. ';
    // Send the email.
    $params = array(
      'subject' => t('Notificacion Usuario para revision de estado'),
      'body' => check_markup(
        t($message),
        'plain_text'
      ),
    );
    drupal_mail('banrep_plan_carrera', 'email_change_state', $email, language_default(), $params);
}

function get_ids_all_user(){
    $response = FALSE;
    $query = 'SELECT DISTINCT(ur.uid)
    FROM {users_roles} AS ur
    WHERE ur.rid IN (:rids)';

    $result = db_query($query, array(':rids' => array(4,5)));
    $uids = $result->fetchCol();

    return $uids;
}
