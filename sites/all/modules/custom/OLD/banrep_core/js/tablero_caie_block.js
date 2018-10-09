(function ($) {
  Drupal.behaviors.dashboard = {
    attach: function (context, settings) {
      $( "#accordion" ).accordion({ autoHeight: false, heightStyle: "content" });

      $( "a.view-response" ).click(function(event) {
        var msg = $(this).find('.status-message').html();
        $('.remodal .msg').html(msg);
        $(form_selector).slideToggle( "slow", function() {});
      });

    }
  }
}(jQuery));
