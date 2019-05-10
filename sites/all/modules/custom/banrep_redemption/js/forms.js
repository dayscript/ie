(function ($) {
    'use strict';
  
    Drupal.behaviors.banrep_redemption = {
      attach: function(context, settings) {
        var select = $('select[name="field_studies_carried_out[und][0][field_req_formacion_desempeno][und][0][field_formacion_y_desarrollo][und][hierarchical_select][selects][0]"]');
        if(select.val() == settings.banrep_redemption.REQ_FORMATION_ID_DESEMPEÑO){
          hidden();
        } 
        select.change(function(){
            if($(this).val() == settings.banrep_redemption.REQ_FORMATION_ID_DESEMPEÑO){
              hidden();
            }else{
              show();
            }
        })
      },
    };


    function hidden(){
      $('#edit-field-studies-carried-out-und-0-field-titulo').css('display','none');
      $('#edit-field-studies-carried-out-und-0-field-tipo-posgrado').css('display', 'none');
      $('#edit-field-studies-carried-out-und-0-field-nivel-estudio').css('display', 'none');
      $('#edit-field-studies-carried-out-und-0-field-lugar-posgrado').css('display', 'none');
      $('#edit-field-studies-carried-out-und-0-field-university').css('display', 'none');
    }

    function show(){
      $('#edit-field-studies-carried-out-und-0-field-titulo').css('display','inline-block');
      $('#edit-field-studies-carried-out-und-0-field-tipo-posgrado').css('display', 'inline-block');
      $('#edit-field-studies-carried-out-und-0-field-nivel-estudio').css('display', 'inline-block');
      $('#edit-field-studies-carried-out-und-0-field-lugar-posgrado').css('display', 'inline-block');
      $('#edit-field-studies-carried-out-und-0-field-university').css('display', 'none');
    }
  
  }(jQuery));