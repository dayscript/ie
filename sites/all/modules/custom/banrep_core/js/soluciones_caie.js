(function ($) {
  jQuery(document).ready(function($) {
    jQuery( ".slideToggle" ).click(function() {
        jQuery( "span.tab-name" ).removeClass('active-item');
        jQuery(this).next( "span.tab-name" ).addClass("active-item");
        var id = jQuery(this).attr('data-tab');
        jQuery( ".solutions-descriptions .solution:not(#"+id+")" ).slideUp();
        jQuery( ".solutions-descriptions #"+id ).slideToggle( "slow", function() {});
    });

    jQuery( "#mis-soluciones-caie .dark-blue-box .row .col-md-9 .col-md-2:first-child .slideToggle" ).trigger( "click" );

    var owl = $(".soluciones-caie .view-content");
    owl.owlCarousel({
        pagination:true,
    	  navigation:false,
        items : 1, //7 items above 1000px browser width
        itemsDesktop : [1000,1], //7 items between 1000px and 901px
        itemsDesktopSmall : [900,1], // betweem 900px and 601px
        itemsTablet: [600,1], //4 items between 600 and 0
        itemsMobile : false, // itemsMobile disabled - inherit from itemsTablet option
        dots: true,
        autoplay: true,
    });

    var owl = $(".espacios-caie .view-content");
    owl.owlCarousel({
        pagination:true,
        navigation:false,
        items : 1, //7 items above 1000px browser width
        itemsDesktop : [1000,1], //7 items between 1000px and 901px
        itemsDesktopSmall : [900,1], // betweem 900px and 601px
        itemsTablet: [600,1], //4 items between 600 and 0
        itemsMobile : false, // itemsMobile disabled - inherit from itemsTablet option
        dots: true,
        autoplay: true,
    });

  });
}(jQuery));


