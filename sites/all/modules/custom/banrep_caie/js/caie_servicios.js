(function ($) {
  Drupal.behaviors.exampleModule = {
    attach: function (context, settings) {
      $('.back').click(function(e) {
          e.preventDefault();
          history.back();
      });
    }
  };
}(jQuery));
