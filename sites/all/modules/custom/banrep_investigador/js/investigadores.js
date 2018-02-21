(function ($) {
  Drupal.behaviors.investigadores = {
    attach: function (context, settings) {
      $(".view-investigadores .profile-image img").removeAttr('title');
      var linea = GetURLParameter('linea');
      $("#edit-linea").val(linea);
    }
  }

  function GetURLParameter(sParam) {
      var sPageURL = window.location.search.substring(1);
      var sURLVariables = sPageURL.split('&');
      for (var i = 0; i < sURLVariables.length; i++)
      {
          var sParameterName = sURLVariables[i].split('=');
          if (sParameterName[0] == sParam)
          {
              return sParameterName[1];
          }
      }
  }
}(jQuery));
