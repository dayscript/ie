/*
 * @file
 * JavaScript for User Add tercero.
 */
(function($){
  // add drupal behavior
  Drupal.behaviors.plan_carrera_validate = {
    attach: function (context, settings) {

        var form = $("#banrep-plan-carrera-form");
        $('#banrep-plan-carrera-form input[type="checkbox"]').click(function(){
            $(this).parent().next().find('textarea').addClass('validar');
        });
        $('#banrep-plan-carrera-form .form-submit').click(function(event){
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

    /*    var validate_messages = {
        };

        var validator = form.validate({
            rules: validate_rules,
            messages: validate_messages,
        });

        $.validator.messages.required = 'Campo requerido.';
        $.validator.messages.validarAutocompletar = 'Entidad no existe.';
        $.validator.messages.validarCupo = 'El valor execede el cupo de credito.';
        $.validator.messages.validarVolumen = 'Campo requerido.';*/

   }
 }

})(jQuery);
