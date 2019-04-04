<?php

function fields_get_list($entity_type = NULL, $bundle_name = NULL){
    $fields = [];
    
    $fields_filter = ['field_puntaje_br','field_acumulado_general','field_puntaje_acumulado']; #In array fields only add the fields includes in this array
    
    $fields_info = field_info_instances($entity_type, $bundle_name);
    foreach ($fields_info[$entity_type] as $field_name => $value) {
        if(in_array($value['field_name'],$fields_filter)){
            $fields[$value['field_name']] = $value['label'];
        }
    }

    return $fields;
}
