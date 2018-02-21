<?php

/*
 *  Funcion que ccar
 */

function get_requirements($scale,$route){

  $query = db_select('field_data_field_ruta_plan_carrera', 'r'); 
  $query->addField('r','entity_id','nid');
  $query->join('field_data_field_escalafon_actual', 's', 's.entity_id = r.entity_id');
  $query->condition('r.field_ruta_plan_carrera_tid',$route, '=');
  $query->condition('s.field_escalafon_actual_tid',$scale, '=');
  $result = $query->execute()->fetchObject();

  if (isset($result->nid) && is_numeric($result->nid) && $result->nid > 0) {
      $node = node_load($result->nid);
      $requirements = array();
      $requirements['publications'] = get_publications_requirements($node->field_requisitos_publicaciones['und']);
      $requirements['time']         = get_time_requirements($node->field_requisitos_tiempo['und']);
      $requirements['training']     = get_training_requirements($node->field_req_formacion_desempeno['und']);
      return $requirements;
  }
  else {

      return false;
  }


}

function get_time_requirements($items){
  $requirements =  array();

  foreach ($items as $item) {
     $rule = field_collection_item_load($item['value']);
     $requirements[$rule->field_pcr_tipo_tiempo['und'][0]['value']] = $rule->field_pcr_tiempo['und'][0]['value'];
  }

  return $requirements;


}

function get_publications_requirements($items){
    $requirements =  array();
    $cont_group = 0;    
    foreach ($items as $group) {
       $item       = field_collection_item_load($group['value']);
       $operator_g = isset($item->field_operador['und'][0]['value'])?$item->field_operador['und'][0]['value']:'';
       $conditions = $item->field_condicion['und'];
       $cont_condition = 0;
       $requirements[$cont_group]['operator'] = $operator_g;
       foreach ($conditions as $condition) {
             $rule = field_collection_item_load($condition['value']);
             $type = $rule->field_tipo_requisito['und'][0]['value'];
             switch ($type) {
                 case 'CANTIDAD':
                     if (isset($rule->field_serie['und'][0]['target_id'])){
                        $requirements[$cont_group]['conditions'][$cont_condition]['serie'] = $rule->field_serie['und'][0]['target_id'];
                     }
                     $concept = array();
                     foreach ($rule->field_concept_type['und'] as $taxonomy) {
                        $concept[] = $taxonomy['tid'];
                     }
                     $requirements[$cont_group]['conditions'][$cont_condition]['concept']  = implode(',', $concept);
                 break;
             }
             $requirements[$cont_group]['conditions'][$cont_condition]['operator'] = $rule->field_operador['und'][0]['value'];
             $requirements[$cont_group]['conditions'][$cont_condition]['type']     = $type;
             $requirements[$cont_group]['conditions'][$cont_condition]['value']    = $rule->field_cantidad_puntaje['und'][0]['value'];
             $cont_condition++;
       }
       $cont_group++;
    }

    return $requirements;
}

function get_training_requirements($items){
  $requirements =  array();
  $cont = 0;
  foreach ($items as $item) {
     $rule = field_collection_item_load($item);
     $requirements[$cont]['operator'] = NULL;
     if ($cont > 0){
         $requirements[$cont]['operator'] = 'O';
     }
     $cont_condition = 0;
     foreach ($rule->field_formacion_y_desarrollo['und'] as $key => $value) {
        $requirements[$cont][$cont_condition]=$value['tid'];
        $cont_condition++;
     }
     $cont++;
  }

  return $requirements;
  
}


function _get_concept_publications($tids){
    $tids  = explode(',', $tids);
    $terms = taxonomy_term_load_multiple($tids);
    $name  = '';
    foreach ($terms as $key => $term) {
         if (!empty($name)){
             $name .=' - '.$term->name;
         }
         else {
             $name = $term->name;   
         }
    }

    return $name;

}

function _get_time_user($uid,$type){
  $usuario = user_load($uid);
  $experiencia = 0;
  foreach ($usuario->field_studies_carried_out['und'] as $value) {
       $rule = field_collection_item_load($value['value']);

        switch ($type) {
          case 'A':
          case 'B':
              $query = db_select('field_data_field_fecha_inicio_estudio', 'fi'); 
              $query->addField('fi','field_fecha_inicio_estudio_value','fecha_inicio');
              $query->addField('ff','field_fecha_fin_estudio_value','fecha_fin');
              $query->addExpression('TIMESTAMPDIFF(YEAR,FROM_UNIXTIME(fi.field_fecha_inicio_estudio_value),FROM_UNIXTIME(ff.field_fecha_fin_estudio_value))','experiencia');
              $query->join('field_data_field_fecha_fin_estudio', 'ff', 'ff.entity_id = fi.entity_id');
              $query->condition('ff.entity_id', $value['value'],'=');
              if ($type == 'B') {
                  $query->join('field_data_field_lugar_posgrado', 'l', 'l.entity_id = fi.entity_id');
                  $query->condition('l.field_lugar_posgrado_value', 'COLOMBIA','=');
              }
              $result = $query->execute()->fetchObject();
              if (isset($result->experiencia) && !is_null($result->experiencia)){
                 $experiencia = $experiencia +  $result->experiencia;
              }
            break;
          case 'C':
            break;
          case 'D':
            break;
        }

   } 

  return $experiencia;



}
