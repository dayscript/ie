<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

$items = explode("|", $output);

?>
<?php if(isset($items[0]) && isset($items[1]) && ($items[0] == 'Aprobado') && (!in_array($items[1], drupal_get_promotes_publications()))): ?>
	<button type="button" class="btn btn-sm btn-blue promote-publication" data-nid="<?php echo $items[1]; ?>" >+ Destacar Publicación</button>
<?php endif; ?>