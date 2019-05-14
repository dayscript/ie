(function ($) {
    'use strict';
  
    Drupal.behaviors.banrep_redemption = {
      attach: function(context, settings) {
        var select = $('#edit-field-beneficios-und');
        var br = $('#edit-field-descuento-puntos-br-und-0-value');
        var academico = $('#edit-field-descuento-puntos-academico-und-0-value');
        var general = $('#edit-field-descuento-puntos-general-und-0-value');
        var max_value_br = parseInt($('#edit-field-puntaje-br-und-0-value').val());
        var max_academico = parseInt($('#edit-field-puntaje-acumulado-und-0-value').val());
        var max_general = parseInt($('#edit-field-puntaje-und-0-value').val());


        select.change(function(){
            var tid = $(this).val();
            if( tid != '_none'){
                $(br).val(settings.banrep_redemption.beneficios[tid].field_puntaje_br.und["0"].value);
                $(academico).val(settings.banrep_redemption.beneficios[tid].field_puntaje_acumulado.und["0"].value);
                $(general).val(settings.banrep_redemption.beneficios[tid].field_puntaje.und["0"].value);
            }else{
                $(br).val(0);
                $(academico).val(0);
                $(general).val(0);
            }
        })

        br.change(function(){
            if( parseInt($(this).val()) > max_value_br ){
                $(this).val(0)
            }
        })

        academico.change(function(){
            if( parseInt($(this).val()) > max_academico ){
                $(this).val(0)
            }
        })
        
        general.change(function(){
            if( parseInt($(this).val()) > max_general ){
                $(this).val(0)
            }
        })

      },
    };
 
  }(jQuery));