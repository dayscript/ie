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
      var type_concept = $('#edit-query-content-type-accumulated').val();
      if (type_concept.length > 0 &&  type_concept == 15350){
        $('.form-item-query-content-type-concept-formation').show();  
      }
      else {
        $('.form-item-query-content-type-concept-formation').hide();  
      }
      

      $('#edit-query-content-type-accumulated').change(function(){
         var concept = $('#edit-query-content-type-accumulated').val();
         if (concept.length > 0 &&  concept == 15350) {
            $('.form-item-query-content-type-concept-formation').show();
         }
         else {
            $('.form-item-query-content-type-concept-formation').hide();
         }
      });
    }
  }
})(jQuery);

