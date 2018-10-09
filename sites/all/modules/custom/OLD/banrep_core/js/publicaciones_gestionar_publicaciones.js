jQuery(function() {
    jQuery( ".promote-publication" ).click(function(event) {
		event.preventDefault();
		var nid = jQuery(this).attr('data-nid');
	    // POST to server using jQuery.post or jQuery.ajax
	    jQuery.ajax({
	        data: {'nid':nid},
	        type: 'POST',
	        dataType: "json",
	        url: Drupal.settings.basePath+'publication/promote',
	        success: function (msg) {
	        	if(msg.response){
	        		var url = window.location.href;    
	        		window.location.href = url;		
	        	}
	        },
	    });
    });
});

