
function isset () {
  //  discuss at: http://locutus.io/php/isset/
  // original by: Kevin van Zonneveld (http://kvz.io)
  // improved by: FremyCompany
  // improved by: Onno Marsman (https://twitter.com/onnomarsman)
  // improved by: Rafał Kukawski (http://blog.kukawski.pl)
  //   example 1: isset( undefined, true)
  //   returns 1: false
  //   example 2: isset( 'Kevin van Zonneveld' )
  //   returns 2: true

  var a = arguments
  var l = a.length
  var i = 0
  var undef

  if (l === 0) {
    throw new Error('Empty isset')
  }

  while (i !== l) {
    if (a[i] === undef || a[i] === null) {
      return false
    }
    i++
  }

  return true
}

/*
 * @file
 * JavaScript for User Search Form.
 */
(function ($) {
    $(document).ready(function () {
    	var form = $("#banrep-core-search-block-form");
        var validate_rules = {
            keys: {
                minlength: 2,
                required: true,
            },
        };
        var validate_messages = {
            keys:{
                required: 'Ingresa algún término de Búsqueda.',
                minlength: 'Ingresa algún término de Búsqueda Valido',
            },
        };
        form.validate({
            rules: validate_rules,
            messages: validate_messages,
            submitHandler: function(form) {
                if(isset(Drupal.settings.banrep_core.engines)){
                    var search = jQuery('#edit-keys').val();
                    var option_selected = jQuery( "#edit-source option:selected" ).text();
                    var engines = Drupal.settings.banrep_core.engines;
                    var formatid = '';
                    var name = '';
                    for (i = 0; i < engines.length; i++) { 
                        var pageid = engines[i].pageid;
                        if(pageid == option_selected){
                            formatid = engines[i].formatid;   
                            name = engines[i].name;     
                        }
                    }
                    window.location.href = formatid+'?'+name+'='+search;
                }
                return false;
            }
        });
    }); 	
})(jQuery);