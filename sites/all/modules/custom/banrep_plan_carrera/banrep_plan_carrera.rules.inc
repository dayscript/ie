<?php

function calculo_prof_experto_375(){
    // Tres artículos publicados en la serie de Borradores de Economía
    
    
    //o en la serie Documentos de Economía Regional 
    
    //o 7 puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera. 
    

    // Acumular un total de 15 puntos BR de acuerdo con el listado de puntajes aprobado para el plan de carrera.

    // Los dos anteriores requisitos rigen desde el momento en que fue nombrado en el cargo de Profesional Especializado. 

    // Contar con título de maestría en el país o en el exterior. 

    // El tiempo acumulado de experiencia desde su nombramiento como profesional debe ser mínimo de 5 años sin contar con los años de estudio en el exterior.


}

function prof_lider_430(){
    //Cuatro artículos publicados en la serie de Borradores de Economía 
    
    //o en la serie Documentos de Economía Regional 
    
    //o 14 puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera. 
    
    //El puntaje de estas publicaciones será asignado según los criterios del plan de carrera.


    //Acumular un total de 30 puntos BR de acuerdo con el listado de puntajes aprobado para el plan de carrera.

    // Los dos requisitos anteriores rigen desde el momento en que fue nombrado en el cargo de Profesional Experto. 

    // El tiempo acumulado de experiencia desde su nombramiento como Profesional debe ser mínimo 7 años sin contar con los años de estudio en el exterior.
}

function invs_junior_494_(){

    // Inmediatamente tenga el título de doctorado en Economía.

    // Acumular 30 puntos, de los cuales al menos 20 deben corresponder a puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera.

    // El tiempo acumulado de experiencia desde su nombramiento como Profesional deber ser mínimo de 9 años sin contar con los años de estudio en el exterior. 
}

function invs_568(){
    // 3 años en el cargo de Investigador Júnior.

    //Acumular 40 puntos. Al menos 14 deben corresponder a puntos BR.
}

function invs_ppal_654(){
    // 5 años en el cargo de Investigador

    // Acumular 100 puntos: 
    ////Al menos 50 deben ser BR 

    //// Por lo menos 30 académicos por publicaciones en revistas de alto impacto (Grupos ISI 1, 2 y 3). Los cuales se acumulan desde el su nombramiento como Investigador Júnior 

}

function paso_ruta_tec_A_ruta_invs(){

    // Acumular 30 puntos, de los cuales al menos 20 deben corresponder a puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera. 

    //El tiempo acumulado de experiencia desde su nombramiento como Profesional deber ser mínimo de 9 años sin contar con los años de estudio en el exterior.



}

function prof_expert_375(){
    // Tres artículos publicados en la serie de Borradores de Economía
    // o en la serie Documentos de Economía Regional 
    //o 7 puntos académicos por publicaciones en revistas incluidas en el listado oficial del plan de carrera.
    
    //El puntaje de estas publicaciones será asignado según los criterios del plan de carrera. 

    //Acumular un total de 15 puntos BR de acuerdo con el listado de puntajes aprobado para el plan de carrera. 

    //Los dos anteriores requisitos rigen desde el momento en que fue nombrado en el cargo de Profesional Especializado. 

    //Contar con título de maestría en el país o en el exterior. 

    // El tiempo acumulado de experiencia desde su nombramiento como profesional debe ser mínimo de 5 años 
    //sin contar con los años de estudio en el exterior.


}

function contar_articulos($uid, $num, $type){
    $response = FALSE;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'article')
    ->fieldCondition('field_user_reference', 'target_id', $uid)
    ->fieldCondition('field_estado_publicaci_n', 'value', APROBADO)
    ->fiedlCondition('field_concept_type', 'value', $type);

    $result = $query->execute()->rowCount();

    if($result >= $num){
        $response = TRUE;
    }

    return $response;
  
}