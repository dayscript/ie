(function ($) {
    'use strict';
  
    Drupal.behaviors.banrep_redemption = {
      attach: function(context, settings) {
        var select = $('select[name="field_studies_carried_out[und][0][field_req_formacion_desempeno][und][0][field_formacion_y_desarrollo][und][hierarchical_select][selects][0]"]');
        var elements = [
          '#edit-field-studies-carried-out-und-0-field-titulo',
          '#edit-field-studies-carried-out-und-0-field-tipo-posgrado',
          '#edit-field-studies-carried-out-und-0-field-nivel-estudio',
          '#edit-field-studies-carried-out-und-0-field-lugar-posgrado',
          '#edit-field-studies-carried-out-und-0-field-university'
        ];

        if(select.val() == settings.banrep_redemption.REQ_FORMATION_ID_DESEMPEÑO){
          hidden(elements);
        } 
        select.change(function(){
            if($(this).val() == settings.banrep_redemption.REQ_FORMATION_ID_DESEMPEÑO){
              hidden(elements);
            }else{
              show(elements);
            }
        })
      },
    };

    function hidden(elemets){
      elemets.forEach(element => {
        $(element).css('display','none');  
      });
    }

    function show(elemets){
      elemets.forEach(element => {
        $(element).css('display','inline-block');
      });
    }
  
  }(jQuery));