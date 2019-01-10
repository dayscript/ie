jQuery(function() {
  
  jQuery( ".slideToggle" ).click(function() {
      jQuery( "span.tab-name" ).removeClass('active-item');
      jQuery(this).next( "span.tab-name" ).addClass("active-item");
      var id = jQuery(this).attr('data-tab');
      jQuery( ".solutions-descriptions .solution:not(#"+id+")" ).slideUp();
      jQuery( ".solutions-descriptions #"+id ).slideToggle( "slow", function() {});
  });
  
  jQuery( "#mis-soluciones-caie .dark-blue-box .row .col-md-9 .col-md-2:first-child img.slideToggle" ).trigger( "click" );

});

