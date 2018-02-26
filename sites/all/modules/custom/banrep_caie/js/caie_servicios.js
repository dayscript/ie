(function ($) {
  Drupal.behaviors.caieModule = {
    attach: function (context, settings) {
      $('.back').click(function(e) {
          e.preventDefault();
          history.back();
      });
    }
  };
}(jQuery));
