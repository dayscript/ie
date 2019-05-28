(function ($) {
    $(window).load(function(){
        console.log('cargo el js');
     $('.test-link').on( 'click',function(event){
        event.preventDefault();
         $(this).next().toggleClass('hidden');
     });
  });
  }(jQuery));