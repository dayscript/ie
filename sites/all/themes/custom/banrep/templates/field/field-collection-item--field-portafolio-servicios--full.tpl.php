<?php

/**
 * @file
 * Default theme implementation for field collection items.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) field collection item label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-field-collection-item
 *   - field-collection-item-{field_name}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */

$field_caie_description = isset($content['field_caie_description'][0]['#markup']) ? $content['field_caie_description'][0]['#markup'] : '' ;
$field_titulo = isset($content['field_titulo'][0]['#markup']) ? $content['field_titulo'][0]['#markup'] : '' ;

$machine_service_name = human_to_machine($field_titulo);

?>
<h3><?php print $field_titulo; ?></h3>
<div>
	<?php print $field_caie_description; ?>
	<?php if(user_is_logged_in()): ?>
		<a href="javascript:void(0);" class="show-formulario button-primary form-submit" data-service="<?php echo $machine_service_name; ?>"> + <?php echo t('New Request'); ?></a>
		<div class="form-request-<?php echo $machine_service_name; ?> form-request " data-service="<?php echo $machine_service_name; ?>" style="display: none;">
   			<?php print render($content['field_formulario']); ?>
   		</div>
   	<?php endif; ?>
</div>
