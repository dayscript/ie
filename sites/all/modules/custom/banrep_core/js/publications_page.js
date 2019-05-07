/*
 * @file
 */
(function ($) {
    $(document).ready(function () {
        $( "#accordion" ).accordion({
          heightStyle: "content",
          collapsible: false,
          active: false,
          disabled: true,
        });
        $('#accordion .ui-accordion-content').show();
    });
})(jQuery);
