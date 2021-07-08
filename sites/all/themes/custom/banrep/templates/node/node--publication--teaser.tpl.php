<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 *
 * Artículos:
 * Autor principal, Coautor 1, Coautor 2, Coautor 3, Coautor 4 (Año). Título de la publicación. Concepto,
 * Volumen(Número), Páginas.
 * Libros:
 * Autor principal, Coautor 1, Coautor 2, Coautor 3, Coautor 4 (Año). Título de la publicación. Ciudad: Editorial.
 * Documentos de Trabajo:
 * Autor principal, Coautor 1, Coautor 2, Coautor 3, Coautor 4 (Año). Título de la publicación. Serie No. Número.
 * Capítulo de libro:
 * Autor principal, Coautor 1, Coautor 2, Coautor 3, Coautor 4 (Año). Título del capítulo. En Autor principal,
 * Coautor 1, Coautor 2, Coautor 3, Coautor 4, Título del libro (pp. Páginas). Ciudad: Editorial
 */

module_load_include('inc', 'banrep_investigador', 'banrep_investigador.functions');
hide($content['comments']);
hide($content['links']);
/**
 * 201|Artículo
 * 206|Libro
 * 1|Capitulo de libro
 * 2951|Documento de trabajo
 */
$concepts_articulos = array(201,202,203,204,205);
$concepts_libros = array(206,207,208,209);
$concepts_workpapers = array(2951);
$concepts_revista_espe =  array(20685);
$concept_type = $node->field_pub_type['und'][0]['value'];
$concept_name = NULL;
if(isset($node->field_concept['und'][0]['target_id'])){
  $concept_name = get_node_title($node->field_concept['und'][0]['target_id']);
}

if (!empty($node->field_role_within_publication[LANGUAGE_NONE])) {
  $tid_role_edition = $node->field_role_within_publication[LANGUAGE_NONE][0]['tid'];
}
$co_authors = array();
if ($node->field_main_author_reference['und']) {
  foreach ($node->field_main_author_reference['und'] as $key_main => $main_author) {
    $full_name = array(
      array(
        'names' => _banrep_core_obtener_nombres_autor($main_author['tid']),
        'surnames' => _banrep_core_obtener_apellidos_autor($main_author['tid'])
      )
    );
    $co_authors[$main_author['tid']]['full_name'] = $full_name;
    $co_authors[$main_author['tid']]['name_format'] = banrep_investigador_authors_to_apa($full_name);
  }
}
if ( isset($node->field_other_co_authors['und']) ) {
  // if ($node->field_other_co_authors['und'] && $tid_role_edition) {
  if ($node->field_other_co_authors['und']) {
    foreach ($node->field_other_co_authors['und'] as $key_other => $co_author) {
      $full_name = array(
        array(
          'names' => _banrep_core_obtener_nombres_autor($co_author['tid']),
          'surnames' => _banrep_core_obtener_apellidos_autor($co_author['tid']),
        )
      );
      $co_authors[$co_author['tid']]['full_name'] = $full_name;
      $co_authors[$co_author['tid']]['name_format'] = banrep_investigador_authors_with_role_editor_to_apa($full_name, $tid_role_edition);
    }
  }
}

?>
<article
  class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix item"
    <?php print $attributes; ?>
>
  <?php

  $limit = 3;
  $visible_authors = '';
  // foreach (array_slice($co_authors, 0, $limit) as $key_vis => $info_autor_vis) {
  //   $visible_authors .= $info_autor_vis['name_format'] . ', ';
  // }
  
  foreach ($co_authors as $key_vis => $info_autor_vis) {
    $visible_authors .= $info_autor_vis['name_format'] . ', ';
  }

  $hidden_authors = '';
  if (count($co_authors) > $limit) {
    foreach (array_slice($co_authors, $limit) as $key_hidd => $info_autor_hidd) {
      $hidden_authors .= $info_autor_hidd['name_format'] . ', ';
    }
    $hidden_authors =
      '<a href="#last-coauthors-'.$node->nid.'" class="show-more">' .
        'Ver más' .
      '</a> ' .
      '<span id="last-coauthors-'.$node->nid.'" class="hidden">' .
        $hidden_authors .
      '</span>'
    ;
  }
  $authors =
    '<span class="coauthors">' .
      $visible_authors .
      ($hidden_authors?' '.$hidden_authors:'') .
    '</span>'
  ;



  if (isset($node->field_url['und'][0]['url'])) {
    $title =
      '<span class="titulo">' .
        l(
          $node->title,
          $node->field_url['und'][0]['url'],
          array('html'=>TRUE, 'attributes'=>array('target'=>'_blank'))
        ) .
      '</span>.'
    ;
  }
  else {
    $title = '<span class="titulo">' . $node->title . '</span>.';
  }
  $year = '';
  if (isset($node->field_publication_year['und'][0]['value'])) {
    $year =
      '<span class="year">' .
        '(' . $node->field_publication_year['und'][0]['value'] . ')' .
      '</span>.'
    ;
  }
  $concepto = '';
  if (in_array($concept_type, $concepts_articulos) || $concept_type == 2951) {
    if ($concept_name) {
      $concepto =
        '<span class="concepto">' .
          '<em>' .
            $concept_name .
          '</em>' .
        '</span>'
      ;
    }
  }
  if (in_array($concept_type, $concepts_revista_espe)) {
      $concepto =
        '<span class="concepto">' .
	 //'<em>' . t('Espe Magazine', array(), array('langcode' => 'es')) . '</em>' .
	  '<em>' .
	     $concept_name .
	  '</em>' .
        '</span>'
      ;
  }

  $ciudad = '';
  $editorial = '';
  if (in_array($concept_type, $concepts_libros)) {
    if (isset($node->field_pub_city['und'][0]['value'])) {
      $ciudad =
        '<span class="ciudad">' .
          '<em>' .
            $node->field_pub_city['und'][0]['value'] .
          '</em>' .
        '</span>'
      ;
    }
    if (isset($node->field_editorial['und'][0]['value'])) {
      $editorial = ': ' . $node->field_editorial['und'][0]['value'];
    }
  }

  $number = '';
  if (isset($node->field_number['und'][0]['value'])) {
    if(!empty($node->field_number['und'][0]['value'])){
      $number = '(' . $node->field_number['und'][0]['value'] . ')';
      if ($concept_type == 2951) {
        $number = $node->field_number['und'][0]['value'];
      }
    }
  }
  $volumen = '';
  if (in_array($concept_type, $concepts_articulos)) {
    $volumen =
      (isset($node->field_volumen['und'][0]['value'])) ?
      $node->field_volumen['und'][0]['value'] :
      ''
    ;
  }

  $page = '';
  if (in_array($concept_type, $concepts_articulos)) {
    if (isset($node->field_page['und'][0]['value'])) {
      $page = $node->field_page['und'][0]['value'];
    }
  }

  if (in_array($concept_type, $concepts_revista_espe)) {
    $volumen =
      (isset($node->field_volumen['und'][0]['value'])) ?
      $node->field_volumen['und'][0]['value'] :
      ''
    ;
  }

  if (in_array($concept_type, $concepts_revista_espe)) {
    if (isset($node->field_page['und'][0]['value'])) {
      $page = $node->field_page['und'][0]['value'];
    }
  }

  $teaser_book = '';
  if($concept_type == 1){
    if($node->field_concept['und'][0]['target_id']){
      $book_data = array();
      $query = db_select('field_data_field_book_related','b');
      $query->fields('b', array('field_book_related_target_id'));
      $query->condition('b.bundle', 'concept');
      $query->condition('b.entity_id', $node->field_concept['und'][0]['target_id']);
      $book_id = $query->execute()->fetchField();
      //Autor principal, Coautor 1, Coautor 2, Coautor 3, Coautor 4, Título del libro (pp. Páginas). Ciudad: Editorial
      if($book_id){
        $book_data = _banrep_core_obtener_libro_de_capitulo($book_id);
      }

      if(count($book_data)){
        $limit = 3;
        $visible_authors_book = '';
        foreach (array_slice($book_data['authors_role_edition'], 0, $limit) as $key_vis_book => $info_autor_vis_book) {
          $visible_authors_book .= $info_autor_vis_book['name_format'] . ', ';
        }
        $hidden_authors_book = '';
        if (count($book_data['authors_role_edition']) > $limit) {
          foreach (array_slice($book_data['authors_role_edition'], $limit) as $key_hidd_book => $info_autor_hidd_book) {
            $hidden_authors_book .= $info_autor_hidd_book['name_format'] . ', ';
          }
          $hidden_authors_book =
            '<a href="#last-coauthors-'.$book_id.'" class="show-more">' .
              'Ver más' .
            '</a> ' .
            '<span id="last-coauthors-'.$book_id.'" class="hidden">' .
              $hidden_authors_book .
            '</span>'
          ;
        }
        $authors_book =
          '<span class="coauthors">' .
            $visible_authors_book .
            ($hidden_authors_book?' '.$hidden_authors_book:'') .
          '</span>'
        ;


        if (isset($book_data['url'])) {
          $title_book =
            '<span class="titulo">' .
              l(
                $book_data['title'],
                $book_data['url'],
                array('html'=>TRUE, 'attributes'=>array('target'=>'_blank'))
              ) .
            '</span>'
          ;
        }
        else {
          $title_book = '<span class="titulo">' . $book_data['title'] . '</span>';
        }
        $page_cap = '';
        if (isset($node->field_page['und'][0]['value'])) {
          $page_cap = $node->field_page['und'][0]['value'];
        }
        $teaser_book =
          'En ' . $authors_book .
          ($title_book?' '.$title_book:'') .
          ($page_cap?'<span class="coauthors"> (pp. '.$page_cap . ').</span>':'') .
          ($book_data['city']?' '.$book_data['city']:'') .
          ($book_data['editorial']?': '.$book_data['editorial']:'');
      }
    }
  }
  
  $teaser =
    $authors .
    ($year?' '.$year:'') .
    ($title?' '.$title:'') .
    ($concepto?' '.$concepto:'') .
    ($ciudad?' '.$ciudad:'') .
    ($volumen?' '.$volumen:'') .
    ($number?' '.$number:'') .
    ($editorial?''.$editorial:'') .
    ($page?' '.$page:'') .
    ($teaser_book?' '.$teaser_book:'') . '.'
  ;

  ?>
  <div class="publicacion-teaser">
    <h3 class="teaser"><?php echo $teaser; ?></h3>
  </div>
</article>
