(function ($) {
  Drupal.behaviors.redemption = {
    attach: function (context, settings) {
      $(document).ajaxComplete(function(){
        $('.hierarchical-select select').each(function(){
          var element = $(this);
          $(element).find('option').each(function(){
            if (!in_array($(this).val(), Drupal.settings.redemption.tids)){
              $(this).remove();
            }
          });
        });
      });
    }

  };
}(jQuery));

function in_array(needle, haystack) {
    for(var i in haystack) {
        if(haystack[i] == needle) return true;
    }
    return false;
}
