<?php

/**
 * @file
 * Default theme implementation to display a term.
 *
 * Available variables:
 * - $name: (deprecated) The unsanitized name of the term. Use $term_name
 *   instead.
 * - $content: An array of items for the content of the term (fields and
 *   description). Use render($content) to print them all, or print a subset
 *   such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $term_url: Direct URL of the current term.
 * - $term_name: Name of the current term.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - taxonomy-term: The current template type, i.e., "theming hook".
 *   - vocabulary-[vocabulary-name]: The vocabulary to which the term belongs to.
 *     For example, if the term is a "Tag" it would result in "vocabulary-tag".
 *
 * Other variables:
 * - $term: Full term object. Contains data that may not be safe.
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $page: Flag for the full page state.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the term. Increments each time it's output.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_taxonomy_term()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php echo banrep_soluciones_caie($term); ?>

<div class="row">
	<div class="col-lg-8">
		 <div class="field_portafolio_servicios" data-term-id="<?php echo $term->tid;?>">
		 	<h2 class="block__title">Portafolio de servicios</h2>
			<?php print render($content['field_portafolio_servicios']); ?>
		 </div>
	</div>
	<div class="col-lg-4">
		 <div class="field_responsable">
		 	<h2 class="block__title"><?php echo t('Collaborators'); ?></h2>
		 		<?php $colaborador = taxonomy_term_load($content['field_responsable']['#items'][0]['tid']); ?>
				<div class="field-item">
					<div class="profile-image">
						<?php echo theme('image_style', array('style_name' => 'user_picture_60x60', 'path' => $colaborador->field_imagen['und'][0]['uri'])); ?>
					</div>
					<div class="user-info">
						<div class="full-name">
							<?php
								$colaborador = taxonomy_term_load($content['field_responsable']['#items'][0]['tid']);
								echo $colaborador->name; ?>
						</div>
						<div class="position"><?php echo $content['field_responsable'][0]['description']['#markup']; ?></div>
					</div>
				</div>
		 </div>
	</div>
</div>
