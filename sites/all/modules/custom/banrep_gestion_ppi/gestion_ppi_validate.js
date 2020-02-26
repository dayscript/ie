/*
 * @file
 * JavaScript for User Add tercero.
 */
(function($){
  // add drupal behavior
  Drupal.behaviors.plan_carrera_validate = {
    attach: function (context, settings) {
      var form = $("#banrep-gestion-ppi-form");
      $('#banrep-gestion-ppi-form input[type="checkbox"]').click(function(){
          $(this).parent().next().find('textarea').addClass('validar');
      });
      $('#banrep-gestion-ppi-form .form-submit').click(function(event){
        event.preventDefault();
        var validate_rules = {};
        var validate_messages = {};
        $('.validar').each(function() {
            var nombre = $(this).attr('name');
            validate_rules[nombre] = {required:true};
        });
        var validator = form.validate({
          rules: validate_rules,
          messages: validate_messages,
        });
        $.validator.messages.required = 'Campo requerido.';
        $.validator.messages.validarAutocompletar = 'Entidad no existe.';
        $.validator.messages.validarCupo = 'El valor execede el cupo de credito.';
        $.validator.messages.validarVolumen = 'Campo requerido.';
        if(form.valid()){
          form.submit();
        }
      });
      $('a.pub_dropdown').click(function(){
        $content = $('div.pub_dropdown_'+this.id);
        if ($content.hasClass('active')) {
          $content.css("display", "none");
          $content.removeClass( "active" );
        }else {
          $content.css("display", "block");
          $content.addClass( "active" );          
        }
      });
    }
  }
})(jQuery);
