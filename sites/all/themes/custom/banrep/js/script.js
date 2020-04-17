/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function($, Drupal, window, document) {

    'use strict';

    // To understand behaviors, see https://drupal.org/node/756722#behaviors
    Drupal.behaviors.my_custom_behavior = {
        attach: function(context, settings) {
            var path = window.location.pathname;
            $('.language-switcher-locale-url .en a').html('EN');
            $('.language-switcher-locale-url .en span').html('EN');
            $('.language-switcher-locale-url .es a').html('ES');
            $('.language-switcher-locale-url .es span').html('ES');

            $('input:radio[name="seminarFilter"]').change(function() {
                if ($(this).val() == 1) {
                    $("#sbSS button").attr('onclick', 'searchSeminars(1); return false;');
                    $("#seminartitle").removeAttr('checked');
                    $(this).attr('checked', 'true');
                } else {
                    $("#sbSS button").attr('onclick', 'searchSeminars(2); return false;');
                    $("#seminaryear").removeAttr('checked');
                    $(this).attr('checked', 'true');
                }
            });
            $('input:radio[name="caieFilter"]').change(function() {
                if ($(this).val() == 1) {
                    $("#sbSC button").attr('onclick', 'searchCaieServices(1); return false;');
                } else {
                    $("#sbSC button").attr('onclick', 'searchCaieServices(2); return false;');
                }
            });

            if (path.indexOf('caie') == -1) {
                var search_type = 'body_value';
                var params = '';
                $('#direct-search').on('submit', function(e) {
                    if ($('#ebscohostsearchtext').val().length <= 0) {
                        e.preventDefault();
                        $('#ebscohostsearchtext').css({
                            '-webkit-box-shadow': '2px -2px 26px 16px rgba(255,0,0,0.7)',
                            '-moz-box-shadow': '2px -2px 26px 16px rgba(255,0,0,0.7)',
                            'box-shadow': '2px -2px 26px 16px rgba(255,0,0,0.7)'
                        });
                        $('#alert-text').empty();
                        $('#alert-text').text('Por favor ingrese el texto a buscar');
                    }
                });
                $('input:radio[name="category1"]').change(function() {
                    var text = $('#ebscohostsearchtext').val();
                    if (text.length > 0) {
                        params = '=' + text;
                    }
                    switch ($(this).val()) {
                        case '0':
                            $("#direct-search-button").attr('onclick', 'DirectSearch(1); return false;');
                            search_type = 'body_value';
                            $("#direct-search").attr('action', '/busqueda-general/texto-destacado?' + ((params.length > 0) ? search_type + params : ''));
                            break;
                        case '1':
                            $("#direct-search-button").attr('onclick', 'DirectSearch(2); return false;');
                            search_type = 'titulo';
                            $("#direct-search").attr('action', '/busqueda-general/titulo?' + ((params.length > 0) ? search_type + params : ''));
                            break;
                        case '2':
                            $("#direct-search-button").attr('onclick', 'DirectSearch(3); return false;');
                            search_type = 'keyword';
                            $("#direct-search").attr('action', '/busqueda-general/keyword?' + ((params.length > 0) ? search_type + params : ''));
                            break;
                        case '4':
                            $("#direct-search-button").attr('onclick', 'DirectSearch(4); return false;');
                            search_type = 'autor';
                            $("#direct-search").attr('action', '/busqueda-general/autores?' + ((params.length > 0) ? ('autor' + params + '&coautor' + params) : ''));
                            break;
                        case '5':
                            $("#direct-search-button").attr('onclick', 'DirectSearch(5); return false;');
                            search_type = 'jel';
                            $("#direct-search").attr('action', '/busqueda-general/jel?' + ((params.length > 0) ? search_type + params : ''));
                            break;
                    }
                });

                $('#ebscohostsearchtext').change(function() {
                    var old_attr = $("#direct-search").attr('action');
                    if (params.length <= 0) {
                        if (search_type == 'autor') {
                            $("#direct-search").attr('action', old_attr + 'autor' + '=' + $(this).val() + '&coautor=' + $(this).val());
                        } else {
                            $("#direct-search").attr('action', old_attr + search_type + '=' + $(this).val());
                        }

                    }
                });
            }

            var form_search_sbss_id = "#sbSS"
            var form_search_sbss = $(form_search_sbss_id);
            var validate_rules = {
                'ebscohostsearchtext': {
                    number: {
                        depends: function(element) {
                            return $('#seminaryear').is(':checked');
                        }
                    }
                },
            };
            var validate_messages = {
                'ebscohostsearchtext': {
                    number: 'El año es numérico. Ej. 2010',
                },
            };
            form_search_sbss.validate({
                rules: validate_rules,
                errorPlacement: function(error, element) {
                    var name = $(element).attr("ebscohostsearchtext");
                    error.appendTo($(".error-wrapper"));
                },
                messages: validate_messages
            });

            $('#sbSS input.ebscohostsearchtext').on('keyup blur', function() { // fires on every keyup & blur
                if ($('#sbSS').valid()) { // checks form for validity
                    $('#sbSS button').prop('disabled', false); // enables button
                } else {
                    $('#sbSS button').prop('disabled', 'disabled'); // disables button
                }
            });
        }
    };

    Drupal.behaviors.LoginFormSwitch = {
        attach: function(context, settings) {
            $('.user-login-pass').hide(0);
            $('#show-recover').click(function(e) {
                e.preventDefault();
                $('.banrep-user-login-form').addClass('hidden');
                $('.banrep-user-pass-form').removeClass('hidden');
            });
            $('#show-login').click(function(e) {
                e.preventDefault();
                $('.banrep-user-pass-form').addClass('hidden');
                $('.banrep-user-login-form').removeClass('hidden');
            });
            $('.open-login').click(function() {
                $(this).addClass('hidden');
                $('.close-login').removeClass('hidden');
                $("#user-login, #user-pass").trigger('reset');
                if ($('.banrep-user-login-form').hasClass('hidden')) {
                    $('.banrep-user-login-form').removeClass('hidden');
                    $('.banrep-user-pass-form').addClass('hidden');
                }
                $('.user-login-pass').slideDown('slow');
            });
            $('.close-login').click(function() {
                $(this).addClass('hidden');
                $('.open-login').removeClass('hidden');
                $('.user-login-pass').slideUp('slow');
            });
            /*$('.navbar__search_link a').click(function(e){
              e.preventDefault();
              $('.navbar__search_form').slideToggle('slow');
            });*/
            $('.like').click(function(e) {
                e.preventDefault();
                $(this).removeAttr('onclick');
            });
        }
    };


    Drupal.behaviors.collapse = {
        attach: function(context, settings) {
            $('.publicacion-teaser a.show-more').click(function() {
                var element = $(this).attr("href");
                if ($(element).hasClass('hidden')) {
                    $(element).removeClass('hidden');
                } else {
                    $(element).addClass('hidden');
                }
                return false;
            });
        }
    };



})(jQuery, Drupal, this, this.document);

jQuery(document).ready(function() {
    var path = window.location.pathname;

    if (jQuery().slicknav) {
        jQuery('nav.main-menu ul').slicknav({ prependTo: '.header .header__navbar .container .row1' });
    }

    if (path.indexOf('caie') >= 0) {
        jQuery('.header__navbar .navbar__search_form').css('background-color', '#7092be');
        jQuery('.header__navbar .navbar__search_link').css('background-color', '#7092be');
    }


    jQuery('.navbar__search_link a').click(function(e) {
        if (!jQuery('.front').length) {
            e.preventDefault();
        }
    });

    if (!jQuery('.front').length) {

        if (jQuery('.page-caie').length) {
            jQuery(".header__navbar .banrep-search-form .form-item-source select").val(1);
            jQuery(".tabs-x").hide();
            jQuery("#tabs-1").show();

        } else {

            if (jQuery('.section-espe').length) {

                // jQuery(".navbar__search_form" ).appendTo( ".region-content-bottom" );


                jQuery(".header__navbar .banrep-search-form .form-item-source select").val(8);

                jQuery("#espe_0").prop("checked", true);

                jQuery(".tabs-x").hide();
                jQuery("#tabs-8").show();

            } else {

                jQuery(".header__navbar .navbar__search_form").hide();

                jQuery(".navbar__search_link").click(function() {
                    jQuery(".header__navbar .navbar__search_form").toggle("normal");
                });

            }


        }



    }


    if (jQuery('.view-autor-investigacion').length) {

        jQuery('.user-profile a').each(function(index) {

            if (jQuery(this).attr('href') == "/es/profile/253") {
                jQuery(this).removeAttr('href');
            }

        });

    }




});