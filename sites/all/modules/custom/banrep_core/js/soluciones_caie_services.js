(function ($) {
  jQuery(document).ready(function($) {
    $( ".field_portafolio_servicios .field-name-field-portafolio-servicios .field-items" ).accordion({
          autoHeight: false,
          heightStyle: "content",
          header: ".field-item h3"
    });

    function cleanServicesOptions(){
      jQuery('.form-request').each(function() {
        var service = jQuery(this).attr('data-service');
        if(service != ''){
          jQuery('select.tipo_solicitud option', jQuery(this)).each(function() {
              if ( jQuery(this).val() != service ) {
                  jQuery(this).remove();
              }else{
                jQuery(this).attr('selected', 'selected');
              }
          });
          jQuery('select.tipo_solicitud', jQuery(this)).trigger("chosen:updated");
        }
      });
    }

    jQuery( ".show-formulario" ).click(function(event) {
      var field_portafolio_servicios = jQuery( ".field_portafolio_servicios" ).attr( "data-term-id" );
      var machine_service_name = jQuery(this).attr( "data-service" );
      var form_selector = '.form-request-' + machine_service_name;
      jQuery(form_selector).slideToggle( "slow", function() {});
    });

    cleanServicesOptions();

  });
}(jQuery));
