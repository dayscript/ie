(function($) {
    Drupal.behaviors.dashboard = {
        attach: function(context, settings) {
            $("#accordion").accordion({ autoHeight: false, heightStyle: "content" });

            $("a.view-response").click(function(event) {
                var msg = $(this).find('.status-message').html();
                $('.remodal .msg').html(msg);
                $(form_selector).slideToggle("slow", function() {});
            });
            $(document).ready(function() {
                sortTable('draggableviews-table-dashboard-mis-publicaciones-block');
            });

            $('.view-id-dashboard_mis_publicaciones').ajaxComplete(function(event, xhr, settings) {
                sortTable('draggableviews-table-dashboard-mis-publicaciones-block');
            });

            /* Basado en https://www.w3schools.com/howto/howto_js_sort_table.asp */
            function sortTable(tableId = null) {
                let table, rows, switching, i, x, y, shouldSwitch;
                table = document.getElementById(tableId);
                switching = true;
                while (switching) {
                    switching = false;
                    if (table !== null) {
                        rows = table.rows;
                        for (i = 1; i < (rows.length - 1); i++) {
                            shouldSwitch = false;
                            x = rows[i].getElementsByTagName("TD")[5];
                            y = rows[i + 1].getElementsByTagName("TD")[5];
                            let x_parts = x.innerText.split('/');
                            let y_parts = y.innerText.split('/');
                            let x_date = new Date(x_parts[2], x_parts[1], x_parts[0]);
                            let y_date = new Date(y_parts[2], y_parts[1], y_parts[0]);
                            if (Date.parse(x_date) !== NaN && Date.parse(y_date) != NaN) {
                                if (Date.parse(x_date) < Date.parse(y_date)) {
                                    shouldSwitch = true;
                                    break;
                                }
                            }
                        }
                        if (shouldSwitch) {
                            rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
                            switching = true;
                        }
                    }
                }
            }
        }
    }
}(jQuery));