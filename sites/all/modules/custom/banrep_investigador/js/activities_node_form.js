/*
 * @file
 * JavaScript for User PQR consultation.
 */
(function ($) {
  Drupal.behaviors.formActivity = {
    attach: function (context, settings) {
      $(".form-item-query-content-start-date-date label").html('Fecha inicio');
      $(".form-item-query-content-end-date-date label").html('Fecha fin');
      $('form', context).delegate('input.form-file', 'change', function() {
        $(this).next('input[type="submit"]').mousedown();
      });
    }
  }
})(jQuery);

