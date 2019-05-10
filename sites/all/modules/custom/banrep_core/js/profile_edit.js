jQuery(document).ready(
	function(){
		jQuery( "#tabs" ).tabs().addClass( "ui-tabs-vertical ui-helper-clearfix" );
   	    jQuery( "#tabs li" ).removeClass( "ui-corner-top" ).addClass( "ui-corner-left" );
        jQuery('.profile-edit-group .image-widget-data .form-submit').hide();

		Drupal.ajax.prototype.commands.responseProfileDescriptionForm = function (ajax, response, status) {
			var res = response.data;
            if(res.success){
            	var id = '#tabs-description';
            	jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
			    jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }

		Drupal.ajax.prototype.commands.responseInvestigationLinesForm = function (ajax, response, status) {
			var res = response.data;
            if(res.success){
            	var id = '#tabs-investigation-lines';
            	jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
			    jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }
  		
		Drupal.ajax.prototype.commands.responseSocialNetworksForm = function (ajax, response, status) {
			var res = response.data;
            if(res.success){
            	var id = '#tabs-social-networks';
            	jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
			    jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }

        Drupal.ajax.prototype.commands.responseFormationForm = function (ajax, response, status) {
            var res = response.data;
            if(res.success){
                var id = '#tabs-formation';
                jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
                jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }

        Drupal.ajax.prototype.commands.responseAcademicProfilesForm = function (ajax, response, status) {
            var res = response.data;
            if(res.success){
                var id = '#tabs-academic-profiles';
                jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
                jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }

		Drupal.ajax.prototype.commands.responseRecommendedLinksForm = function (ajax, response, status) {
			var res = response.data;
            if(res.success){
            	var id = '#tabs-recommended-links';
            	jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
			    jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }
        
		Drupal.ajax.prototype.commands.responseProfileAccessDataForm = function (ajax, response, status) {
			var res = response.data;
            if(res.success){
            	var id = '#tabs-access-data';
            	jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
			    jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }

        Drupal.ajax.prototype.commands.responseWorkInProgressForm = function (ajax, response, status) {
            var res = response.data;
            if(res.success){
                var id = '#tabs-work-in-progress';
                jQuery("#tabs .messages").addClass('hide');
                jQuery(id + " .messages pre").html(res.message);
                jQuery(id + " .messages").removeClass('hide');
                jQuery('html, body').animate({scrollTop: jQuery(id).offset().top}, 1000);
            }
        }
	}
);