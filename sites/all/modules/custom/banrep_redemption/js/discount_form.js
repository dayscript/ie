(function ($) {
    'use strict';
    Drupal.behaviors.banrep_discount = {
      attach: function(context, settings) {
        var select = $('#edit-field-usuario-und-0-target-id');
        select.change(function(){
            var tid = $(this).val().match(/\(([^()]*[^()]*)\)/)[1];
            var url = window.location.origin+"/profile/discount/add?id="+tid;
            window.location = url;
            window.location.replace(url);
        })
        
        $('#edit-field-descuento-puntos-general-und-0-value').change(function(){
            if( parseInt($(this).val()) > parseInt($('#edit-field-puntaje-und-0-value').val()) ){
                $(this).val(0);
            }
        })

        $('#edit-field-descuento-puntos-br-und-0-value').change(function(){
            if( parseInt($(this).val()) > parseInt($('#edit-field-puntaje-br-und-0-value').val()) ){
                $(this).val(0);
            }
        })

        $('#edit-field-descuento-puntos-academico-und-0-value').change(function(){
            if( parseInt($(this).val()) > parseInt($('#edit-field-puntaje-acumulado-und-0-value').val()) ){
                $(this).val(0);
            }
        })
      },
    };
}(jQuery));