(function ($) {
  Drupal.behaviors.seminary = {
    attach: function (context, settings) {
      const path = window.location.pathname;

      if($('.node-event').length >= 0) {
        $('#card-event', context).prepend('<div class="date-mini-card"></div>');
        //$('.field-name-field-event-date', context).addClass('date-mini-card');
        var text_date = $('#card-event', context).find('.date-display-single').text().split(',');
        if(text_date[0] !== undefined && text_date[1] !== undefined){
          var day = text_date[0];
          var date = text_date[1].split('-')[0];
          var hour = text_date[1].split('-')[1];
          date = date.split(' ');
          var month = date[2];
          var day_number = date[1];
          var year = date[3];
          $('.date-mini-card').append('<div class="day red-background">' + day + '</div>');
          $('.date-mini-card').append('<div class="complement-date black-background"></div>');
          $('.black-background').append('<div class="date-month">' + month.substring(0, 3) + '</div>');
          $('.black-background').append('<div class="date-day">' + day_number + '</div>');
          $('.black-background').append('<div class="date-year">' + year + '</div>');
          //$('.field-name-field-event-date', context).hide();
          //$('#card-event', context).append('<div class="event-time"><div><b>Horario:</b></div><div>' + hour + '</div></div>');
        }
        
        if(Drupal.settings.node !== undefined && Drupal.settings.node.type === 'event') {
          const enlace_evento = Drupal.settings.enlace_evento.is_visible;
          const inscripcion = Drupal.settings.inscripcion.is_visible;
          const modalidad = Drupal.settings.modalidad.value;

          $('.field-name-field-inscripcion').hide();
          $('.field-name-field-link-de-acceso').hide();

          if(inscripcion && modalidad === 'Presencial') {
            $('.field-name-field-inscripcion').show();
          }

          if(enlace_evento) {
            $('.field-name-field-enlace-evento').show();
          }

          /* if(link_de_acceso) {
            $('.field-name-field-link-de-acceso').show();
          } */
        }
      }

      if(path.indexOf('seminarios') >= 0) {
        const event_type = $('.modalidad', context).find('.field-items').find('.field-item').first().text();
        if(event_type === 'Virtual') {
          $('.enlace-evento').show();
          $('.inscripcion').hide();
        } else {
          $('.enlace-evento').hide();
          $('.inscripcion').show();
        }
      }

      $('#edit-field-modalidad-und', context).change(function () {
        if($(this).val() === 'Presencial') {
          $('#edit-field-place').show();
          $('#edit-field-inscripcion').show();
          $('#edit-field-link-de-acceso').hide();
          $('#edit-field-enlace-evento').hide();
        } else {
          $('#edit-field-place').hide();
          $('#edit-field-inscripcion').hide();
          $('#edit-field-link-de-acceso').show();
          $('#edit-field-enlace-evento').show();
        }
      });

      $('#edit-field-color-boton-und', context).change(function () {
        if($(this).val() === '_none') {
          $(this).css({'background-color': '#FFF', 'color':'#000'});
        } else {
          $(this).css({'background-color': $(this).val(), 'color':'#FFF'});
        }
      });

    }
  };
  Drupal.ajax.prototype.commands.reloadPage = function() {
    //window.location.reload();
    location.href = '/seminarios-new';
  }

  window.onload = function () {
    //$('.remodal-close').click();
  };
}(jQuery));
