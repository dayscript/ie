(function ($) {
  Drupal.behaviors.seminary = {
    attach: function (context, settings) {
      if($('.node-event').length >= 0) {
        $('#card-event', context).prepend('<div class="date-mini-card"></div>');
        //$('.field-name-field-event-date', context).addClass('date-mini-card');
        var text_date = $('#card-event', context).find('.date-display-single').text().split(',');
        if(text_date[0] !== undefined && text_date[1] !== undefined){
          var day = text_date[0];
          var date = text_date[1].split('-')[0];
          date = date.split(' ');
          var month = date[2];
          var day_number = date[1];
          var year = date[3];
          $('.date-mini-card').append('<div class="day red-background">' + day + '</div>');
          $('.date-mini-card').append('<div class="complement-date black-background"></div>');
          $('.black-background').append('<div class="date-month">' + month.substring(0, 3) + '</div>');
          $('.black-background').append('<div class="date-day">' + day_number + '</div>');
          $('.black-background').append('<div class="date-year">' + year + '</div>');
          $('.field-name-field-event-date', context).hide();
        }
        $('.modalidad-value').each(function () {
          //console.log($(this).text());
          if($(this).text().length > 0 && $(this).text() === 'Presencial') {
            $(this).closest('.other-info').find('.inscripcion').show();
            $(this).closest('.other-info').find('.enlace-evento').hide();
          } else {
            $(this).closest('.other-info').find('.enlace-evento').show();
            $(this).closest('.other-info').find('.inscripcion').hide();
          }
        });
      }

      const event_type = $('.field-name-field-modalidad', context).find('.field-items').find('.field-item').first().text();
      if(event_type === 'Virtual') {
        $('.field-name-field-enlace-evento').show();
        $('.field-name-field-inscripcion').hide();
      } else {
        $('.field-name-field-enlace-evento').hide();
        $('.field-name-field-inscripcion').show();
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
