/*
 * @file
 * JavaScript for User Add tercero.
 */
(function($) {
    // add drupal behavior
    Drupal.behaviors.plan_carrera_validate = {
        attach: function(context, settings) {
            var form = $("#banrep-gestion-ppi-form");
            $('#banrep-gestion-ppi-form input[type="checkbox"]').click(function() {
                $(this).parent().next().find('textarea').addClass('validar');
            });
            $('#banrep-gestion-ppi-form .form-submit').click(function(event) {
                event.preventDefault();
                var validate_rules = {};
                var validate_messages = {};
                $('.validar').each(function() {
                    var nombre = $(this).attr('name');
                    validate_rules[nombre] = { required: true };
                });
                var validator = form.validate({
                    rules: validate_rules,
                    messages: validate_messages,
                });
                $.validator.messages.required = 'Campo requerido.';
                $.validator.messages.validarAutocompletar = 'Entidad no existe.';
                $.validator.messages.validarCupo = 'El valor execede el cupo de credito.';
                $.validator.messages.validarVolumen = 'Campo requerido.';
                if (form.valid()) {
                    form.submit();
                }
            });
            $('a.pub_dropdown').click(function() {
                $content = $('div.pub_dropdown_' + this.id);
                if ($content.hasClass('active')) {
                    $content.css("display", "none");
                    $content.removeClass("active");
                } else {
                    $content.css("display", "block");
                    $content.addClass("active");
                }
            });
            sortTable('table-201');
            sortTable('table-206');
            sortTable('table-211');
            sortTable('table-2951');
            sortTable('table-21204');
            sortTable('draggableviews-table-dashboard-mis-publicaciones-block');

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
                            x = rows[i].getElementsByTagName("TD")[1];
                            y = rows[i + 1].getElementsByTagName("TD")[1];
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
    Drupal.behaviors.dashboard_mis_publicaciones = {
        attach: function(context, settings) {

        }
    }
})(jQuery);