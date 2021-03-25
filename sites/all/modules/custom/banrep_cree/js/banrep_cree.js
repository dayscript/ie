(function ($) {
    Drupal.behaviors.cree = {
        attach: function (context, settings) {
            $( "#cree_grupo_acordion" ).accordion({
                heightStyle: "content",
            });
        }
    };
}(jQuery))