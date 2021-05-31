jQuery(document).ready(function($) {
  var owl = $(".revistas-recientes .view-content");
  owl.owlCarousel({
      slideSpeed : 800,
      autoPlay: 3000,
  	  navigation:true,
      items : 7, //7 items above 1000px browser width
      itemsDesktop : [1000,7], //7 items between 1000px and 901px
      itemsDesktopSmall : [900,5], // betweem 900px and 601px
      itemsTablet: [600,4], //4 items between 600 and 0
      itemsMobile : false // itemsMobile disabled - inherit from itemsTablet option
  });

  jQuery('#block-views-autor-investigacion-block').find('a').each(function () {
    if(jQuery(this).attr('href') === '/es/profile') {
      jQuery(this).contents().unwrap();
    }
  });
});





















