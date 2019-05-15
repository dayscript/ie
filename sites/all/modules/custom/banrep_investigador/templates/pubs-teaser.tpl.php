<?php
module_load_include('inc', 'banrep_investigador', 'banrep_investigador.functions');
$pubs = $variables['pubs'];
$coauthors = $year = $serie = $page = $editorial = NULL;
dpm($pubs);
foreach ($pubs as $pub) {
  if ($pub->co_authors) {
    $coauthors =
      '<span class="coauthors">' .
        banrep_investigador_authors_to_apa($pub ->co_authors) .
      '</span>, '
    ;
  }
  if ($pub->field_url_url) {
    $titulo =
      '<span class="titulo">' .
        l(
          $pub->title,
          $pub->field_url_url,
          array('html' => TRUE, 'attributes' => array('target' => '_blank'))
        ) .
      '</span>. '
    ;
  }
  else {
    $titulo = '<span class="titulo">' . $pub->title . '</span>. ';
  }
  if ($pub->field_publication_year_value) {
    $year =
      '<span class="year">(' .
        $pub->field_publication_year_value .
      ')</span>. '
    ;
  }
  if($pub->field_pub_serie_value) {
    $serie =
      '<span class="serie">' .
        '<em>' .
          $pub->field_pub_serie_value .
        '</em>' .
      '</span> '
    ;
  }
  $teaser = $coauthors . $year . $titulo . $serie;
  if ($pub->field_pub_type_value == 201) {
    if($pub->field_number_value){
      $number = $pub->field_number_value;
      $teaser = $teaser . $number;
    }
    if($pub->field_page_value){
      $page = '(' . $pub->field_page_value . ')';
      $teaser = $teaser . $page;
    }
  }
  elseif ($pub->field_pub_type_value == 206) {
    if($pub->field_editorial_value){
      $editorial = '(' . $pub->field_editorial_value . ')';
      $teaser = $teaser . $editorial;
    }
  }
  elseif ($pub->field_pub_type_value == 2951) {
    //
  }
  ?>
  <div class="publicacion-teaser">
    <h3 class="teaser"><?php echo $teaser; ?></h3>
  </div>
  <?php
}
?>
