(function ($) {
    Drupal.behaviors.cree = {
        attach: function (context, settings) {
            const path = window.location.pathname;
            if(path.indexOf('cree') >= 0) {
                $( "#cree_grupo_acordion" ).accordion({
                    heightStyle: "content",
                });
            }
            $('#edit-centros', context).change(function () {
                if($(this).val().length > 0) {
                    window.open($(this).val(), '_blank');
                }
            });
        }
    };
}(jQuery))