var PortletDraggable = function() {
    var sortable_portlets_id = '#sortable_portlets';
    return {
        //main function to initiate the module
        init: function() {
        
            if (!jQuery().sortable) {
                return;
            }
                 
            jQuery(sortable_portlets_id).sortable({
                connectWith: ".portlet",
                items: ".portlet",
                opacity: 0.8,
                coneHelperSize: true,
                placeholder: 'portlet-sortable-placeholder',
                forcePlaceholderSize: true,
                tolerance: "pointer",
                helper: "clone",
                tolerance: "pointer",
                forcePlaceholderSize: !0,
                helper: "clone",
                cancel: ".portlet-sortable-empty, .portlet-fullscreen", // cancel dragging if portlet is in fullscreen mode
                revert: 250, // animation in milliseconds
                update: function(b, c) {
                    if (c.item.prev().hasClass("portlet-sortable-empty")) {
                        c.item.prev().before(c.item);
                    }
                    var left_colum = [];
                    jQuery( "#sortable_portlets #left-column .portlet-sortable" ).each( function( index, element ){
                        left_colum.push(jQuery( element ).attr('id') );
                    });

                    var middle_colum = [];
                    jQuery( "#sortable_portlets #middle-column .portlet-sortable" ).each( function( index, element ){
                        middle_colum.push(jQuery( element ).attr('id') );
                    });        

                    var right_colum = [];
                    jQuery( "#sortable_portlets #right-column .portlet-sortable" ).each( function( index, element ){
                        right_colum.push(jQuery( element ).attr('id') );
                    });      

                    var group_boxes_order = {
                       left_column: left_colum,
                       middle_column: middle_colum,
                       right_column: right_colum
                    };

                    // POST to server using jQuery.post or jQuery.ajax
                    jQuery.ajax({
                        data: {'group_boxes_order':group_boxes_order, 'term_id':Drupal.settings.banrep_core.research_group},
                        type: 'POST',
                        dataType: "json",
                        url: Drupal.settings.basePath+'research-group/save-order',
                        success: function (msg) {
                           // console.log('group_boxes_order: ' + JSON.stringify(group_boxes_order));
                        },
                    });

                }
            });
        },
        disable: function() {
            jQuery(sortable_portlets_id).sortable("disable");
        },
        enable: function() {
            jQuery(sortable_portlets_id).sortable("enable");
        }
    };
}();

jQuery(function() {
    PortletDraggable.init();

    PortletDraggable.disable();

    jQuery('#switch-sort').change(function() {
        if (jQuery(this).is(":checked")) {
            PortletDraggable.enable();
        } else {
            PortletDraggable.disable();
            // Save order via Ajax
        }
    });

});