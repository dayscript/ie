/*
 * @file
 */
(function ($) {
  $(document).ready(function () {
    Drupal.ajax.prototype.commands.responsePublicationsAddForm = function (ajax, response, status) {
      var res = response.data;
      if(res.success){
        window.location.href = '/dashboard/manage/publications';
      }else{
        form_publication.valid();
      }
      console.log(res);
    }
    /* END Publications */
    /* BEGIND Concepts */
    var form_concept_id = '#custom-concept-add-form';
    var form_concept = $(form_concept_id);
    var validate_rules = {
      'name': {
        minlength: 2,
        required: true
      },
      'isbn': {
        number: true
      },
      'vinculo[fieldset][url]': {
        url: true
      }
    };
    var validate_messages = {
      'name':{
        required: 'Ingresa el Nombre del Concepto.',
        minlength: 'Ingresa el Nombre del Concepto'
      },
      'isbn':{
        number: 'Ingresa un ISBN valido.'
      },
      'vinculo[fieldset][url]': {
        url: 'Ingresa una Url valida.'
      }
    };
    form_concept.validate({
      rules: validate_rules,
      messages: validate_messages
    });
    Drupal.ajax.prototype.commands.responseConceptAddForm = function (ajax, response, status) {
      var res = response.data;
      if(res.success){
        var pubType = getPubType();
        var selector = '';
        switch (pubType) {
          case Drupal.settings.banrep_core.PUB_TYPE_ARTICLE:
            selector = 'input.query-article-name';
            break;
          case Drupal.settings.banrep_core.PUB_TYPE_BOOK:
            selector = 'input.query-book-name';
            break;
          case Drupal.settings.banrep_core.PUB_TYPE_BOOK_CHAPTER:
            selector = 'input.query-book-chapter-name';
            break;
          case Drupal.settings.banrep_core.PUB_TYPE_CONFERENCE_DOCUMENT:
            selector = 'input.query-conference-document-name';
            break;
          case Drupal.settings.banrep_core.PUB_TYPE_WORK_DOCUMENT:
            selector = 'input.query-work-document-name';
            break;
          case Drupal.settings.banrep_core.PUB_TYPE_OTHER_DOCUMENT:
            selector = 'input.query-other-document-name';
            break;
        }
        if (selector != '') {
          $(selector).val(res.label).change();
        }
        $('div .remodal-is-opened a.remodal-close').trigger('click');
        $('#custom-concept-add-form').trigger('reset');
      }
      else {
        form_concept.valid();
      }
    }
    /* END Concepts */
    /* BEGIND Autor Externo */
    var form_autor_externo_id = '#autor-externo-add-form';
    var form_autor_externo = $(form_autor_externo_id);
    var validate_rules = {
      'full_name': {
        minlength: 2,
        required: true
      }
    };
    var validate_messages = {
      'full_name':{
        required: 'Ingresa el Nombre completo.',
        minlength: 'Ingresa el Nombre completo'
      }
    };
    form_autor_externo.validate({
      rules: validate_rules,
      messages: validate_messages
    });
    Drupal.ajax.prototype.commands.responseAutorExternoAddForm = function (ajax, response, status) {
      var res = response.data;
      if(res.success){
        $('.other-co-author-fieldset-wrapper .fieldset-wrapper .form-item input[type=text]:last')
        .val(res.name)
        ;
        $('div .remodal-is-opened a.remodal-close').trigger('click');
        $('#autor-externo-add-form').trigger('reset');
      }else{
        form_autor_externo.valid();
      }
    }
    /* END Autor Externo */
    function getPubType() {
      var pubType = $('#edit-query-right-column-pub-type option:selected').val();
      return pubType;
    }
    var ids = [
      '#edit-query-right-column-pub-type',
      '#edit-query-right-column-fieldset-publication-articulos-article-type',
      '#edit-query-right-column-fieldset-publication-books-book-type',
      '#edit-query-right-column-fieldset-publication-conference-documents-conference-document-type'
    ];
    $.each(ids, function(index, id) {
      if (id == '#edit-query-right-column-pub-type') {
        $(id).on('change', function() {updateConceptModalOptions();});
      }else{
        $(id).on('change', function() {updateConceptModalOptions();});
      }
    });

    var isIE = /*@cc_on!@*/false || !!document.documentMode;

    if(isIE) {
      $('#edit-query-right-column-pub-type').change(function () {
        $('.form-type-textfield').hide();
        if($(this).val() === '201' ) {
          $('#edit-query-right-column-fieldset-publication-articulos').find('.form-type-textfield').first().show();
        }
        if($(this).val() === '1') {
          $('#edit-query-right-column-fieldset-publication-book-chapters').find('.form-type-textfield').first().show();
        }
      });
      $('#edit-query-right-column-fieldset-publication-articulos-concept-type').change(function () {
        $('.form-type-textfield').hide();
        $('.form-item-query-right-column-fieldset-publication-articulos-article-' + $(this).val()).show();
      });
      $('#edit-query-right-column-fieldset-publication-book-chapters-concept-type').change(function () {
        $('.form-type-textfield').hide();
        $('.form-item-query-right-column-fieldset-publication-book-chapters-book-chapter-' + $(this).val()).show();
      });
    }

    /**
    * Update Concept modal options
    */
    function updateConceptModalOptions(){
      var pubType = getPubType();
      var concept_type_child = '';
      $('.visible-on-article').addClass('hidden');
      $('.visible-on-book').addClass('hidden');
      switch (pubType) {
        case Drupal.settings.banrep_core.PUB_TYPE_ARTICLE:
          concept_type_child =
            $(
              '#edit-query-right-column-fieldset-publication-articulos-article-type'+
              ' '+
              'option:selected'
            )
            .val()
          ;
          $('.visible-on-article').removeClass('hidden');
          break;
        case Drupal.settings.banrep_core.PUB_TYPE_BOOK:
        case Drupal.settings.banrep_core.PUB_TYPE_BOOK_CHAPTER:
          concept_type_child =
            $(
              '#edit-query-right-column-fieldset-publication-books-book-type'+
              ' '+
              'option:selected'
            )
            .val()
          ;
          $('.visible-on-book').removeClass('hidden');
          break;
        case Drupal.settings.banrep_core.PUB_TYPE_CONFERENCE_DOCUMENT:
          concept_type_child =
            $(
              '#edit-query-right-column-fieldset-publication-conference-documents-conference-document-type'+
              ' '+
              'option:selected'
            )
            .val()
          ;
          break;
      }
      $('input.concept_type_parent').val(pubType).change();
      if (concept_type_child != '') {
        $('input.concept_type_child').val(concept_type_child).change();
      }
    }
    $('#edit-query-right-column-rol-within-publication').change(function(){

    });
  });
  Drupal.behaviors.formPub = {
    attach: function (context, settings) {
      $('form', context).delegate('input.form-file', 'change', function() {
        $(this).next('input[type="submit"]').mousedown();
      });
    }
  };
  Drupal.behaviors.banrepCoreRoleWithinPublication = {
    attach: function (context, settings) {
      // var cambiarTextos = function(){
      //   var $roleWithinPublication = $('#rol-within-publication');
      //   var roleId = $roleWithinPublication.val();
      //   if (roleId === '-1' || !$roleWithinPublication.is(':visible')) {
      //     roleId = '219'; // Autor libro completo
      //   }
      //   var role =
      //     $roleWithinPublication
      //     .find('option[value=' + roleId + ']')
      //     .text()
      //     .split(' ')[0]
      //   ;
      //   var $authorsFieldset =
      //     $('#co-author-fieldset-wrapper-author-complete-book')
      //   ;
      //   $authorsFieldset.find('span.variable-title').html(role+'es');
      //   $authorsFieldset.find('label').each(function (index) {
      //     var label;
      //     if (index === 0) {
      //       label = role + ' principal';
      //     }
      //     else {
      //       label = 'Co-' + role.toLowerCase();
      //     }
      //     this.childNodes[0].nodeValue = label+' ';
      //   });
      // };
      // $('#edit-query-right-column-pub-type,#rol-within-publication')
      // .once('banrepCoreRoleWithinPublication')
      // .on('change', cambiarTextos)
      // cambiarTextos();
    }
  };
  Drupal.behaviors.formPubValidate = {
    attach: function (context, settings) {
      var form_publication = $("#publications-add-form");
      var validate_rules = {
        'query[left_column][title]': {
          minlength: 2,
          required: true
        },
        'query[left_column][url]': {
          required: true,
          url: true
        }
      };
      var validate_messages = {
        'query[left_column][title]': {
          required: 'Ingresa el Título de la publicación.',
          minlength: 'Ingresa el Título de la publicación'
        },
        'query[left_column][url]': {
          required: 'Ingresar Url de la publicación.',
          url: 'Ingresar Url de la publicación.'
        }
      };
      form_publication.validate({
        rules: validate_rules,
        messages: validate_messages
      });
    }
  };
})(jQuery);
