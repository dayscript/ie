<?php

$data = json_decode(file_get_contents('http://investiga.local/nodes-list.json'));

$fields = array(
  "Título destacado" => 'field_titulo' ,
  "Título destacado (inglés)" => 'field_titulo_destacado_ingles' ,
  "Materias" => 'field_materias',
  "materias ingles" => 'field_materias_ingles',
  "texto destacado"  => 'body',
  "Fecha de publicacion" => 'field_date',
);



foreach( $data as $key => $item){


    $node = node_load($item->Nid);
    echo $node->nid . "\n";
    echo $node->title . "\n";
    $node = entity_metadata_wrapper('node', $node);
    echo "\n";
    echo "Actualizando nodo";


    $node->field_titulo->set($item->{'Título destacado'});
    $node->field_titulo_destacado_ingles->set($item->{'Título destacado (inglés)'});

    $tax = explode(',',$item->{'Materias'});
    if( count($tax) != 0):
      $terms = [];
      foreach( $tax as $key => $value ){
      // $term = taxonomy_get_term_by_name($value, $vocabulary = NULL);
        $terms[] = create_term($value,'materias', 27)->tid ;
      }
      $node->field_materias->set($terms);
    endif;

    $tax_en = explode(',',$item->{'materias ingles'});

    if( count($tax_en) != 0):
      foreach ($tax_en as $key => $value) {
          $terms_en[] = create_term($value,'materias_en', 28)->tid ;

      }
      $node->field_materias_ingles->set($terms_en);
    endif;

    $node->body->set(array('value' => $item->{'texto destacado'}));

    $date = new DateTime(str_replace('/','-',$item->{'Fecha de publicacion'}));
    $node->field_date->set( $date->getTimestamp() );

    echo 'Nodo Guardado'."\n";
    if( $node->save() ) echo "Nodo: " .  $node->nid . "OK\n";
    echo "\n";
}


function create_term( $name, $vocabulary, $vid ){
  if( count(taxonomy_get_term_by_name(trim($name), $vocabulary)) == 0 ){

      taxonomy_term_save( (object) array(
        'name' => trim($name),
        'vid' => $vid,
        )
      );
  }

  $term = taxonomy_get_term_by_name(trim($name), $vocabulary);

  return $term[key($term)];
}


?>
