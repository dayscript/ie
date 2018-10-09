(function ($) {
  Drupal.behaviors.plan_carreras_fields = {
    attach: function (context, settings) {
      var elemento_fecha_ini = "#profile-formation-form #edit-fieldset-formation-formation-0-container-fecha-inicio";
      var elemento_fecha_fin = "#profile-formation-form #edit-fieldset-formation-formation-0-container-fecha-fin";
      $(elemento_fecha_ini).find('div.description').remove();
      $(elemento_fecha_fin).find('div.description').remove();
      $('#profile-formation-form .container-inline-date').removeClass('container-inline-date');
    }
  }
}(jQuery));
