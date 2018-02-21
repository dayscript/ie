var PortletDraggable = function() {
  var sortable_portlets_id = '#sortable_portlets';
  return {
    //main function to initiate the module
    init: function() {
      if (jQuery.fn.tabs) {
        jQuery('#tabs').tabs({
          heightStyle: 'content',
        });
      }
      if (jQuery.fn.accordion) {
        jQuery('#pubs_perfil_acordion').accordion({
          heightStyle: 'content',
        });
      }
      if (!jQuery.fn.sortable) {
        return;
      }
    },
    disable: function() {
      jQuery(sortable_portlets_id).sortable('disable');
    },
    enable: function() {
      jQuery(sortable_portlets_id).sortable('enable');
    }
  };
}();

jQuery(function() {
    PortletDraggable.init();
});

(function ($) {
  Drupal.behaviors.tooltips = {
    attach: function (context, settings) {
      $('.ver-prf').click(function(e) {
        e.preventDefault();
        $('.prf-academicos li').removeClass('hidden');
        $(this).addClass('hidden');
      });
    }
  }
}(jQuery));
