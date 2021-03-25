(function($, Drupal) {
    Drupal.behaviors.banrep_seminary_register = {
        attach: function (context, settings) { 
            $('#edit-id-number, #edit-phone').on('change', function() {
                var input = $(this).val();
                regex = /[0-9]/g;
                if (!regex.exec(input)) {
                    return false;        
                }
            });
            $('#edit-id-number, #edit-phone').on('keypress', function(e) {
                keys = ['0','1','2','3','4','5','6','7','8','9','.']
                return keys.indexOf(e.key) > -1
            });
            $('#edit-correo, #edit-confirm-correo').on('change', function() {
                var mail = $(this).val();
                var id = $(this).attr('id');
                regex = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
                if (!regex.exec(mail)) {
                    $(this).parent().addClass('has-error');
                    $(this).parent().find('.red-alert').remove();
                    $(this).parent().append("<span role='alert' class='red-alert'>El formato del correo es erróneo, debe ser \"ejemplo@mail.com\"</span>");
                } else {
                    $(this).parent().find('.red-alert').remove();
                    $(this).parent().removeClass('has-error');
                }
                if(id === 'edit-confirm-correo') {
                    if($(this).val() !== $('#edit-correo').val()) {
                        $(this).parent().addClass('has-error');
                        $(this).parent().find('.red-alert').remove();
                        $(this).parent().append("<span role='alert' class='red-alert'>Los correos no coinciden</span>");
                    } else {
                        $(this).parent().find('.red-alert').remove();
                        $(this).parent().removeClass('has-error');
                    }       
                }
            });
        }
    };
    
}(jQuery, Drupal));