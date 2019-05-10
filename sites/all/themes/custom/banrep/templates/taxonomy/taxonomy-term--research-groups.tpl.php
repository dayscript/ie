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
global $language;

hide($content['field_image']);
hide($content['description']);
hide($content['field_address']);
hide($content['field_phone']);
hide($content['field_email']);
hide($content['field_members']);
hide($content['field_color']);
hide($content['field_city']);

$address = '';
if(isset($content['field_address'][0]['#markup'])){
	$address = $content['field_address'][0]['#markup'];
}
$phone = '';
if(isset($content['field_phone'][0]['#markup'])){
	$phone = $content['field_phone'][0]['#markup'];
}
$email = '';
if(isset($content['field_email'][0]['#markup'])){
	$email = ' '.$content['field_email'][0]['#markup'];
}
$color = 'transparent';
if(isset($content['field_color'][0]['#markup'])){
	$color = '#'.$content['field_color'][0]['#markup'];
}
$city = '';
if(isset($content['field_city'][0]['#lineage'][0]['#markup'])){
	$city = $content['field_city'][0]['#lineage'][0]['#markup'];
}

?>

<?php if($view_mode == 'full'): ?>
	<?php
		$edit_link = '';
		foreach ($term->field_members['und'] as $key => $member) {
	    if($member['target_id'] == $user->uid && user_has_role(ADMIN_GRUPO_RID)){
	        $edit_link = ' <span class="edit-group"><i class="fa fa-pencil-square-o" aria-hidden="true"></i> <a href="/es/profile/group/'.$term->tid.'/edit">'.t('Edit Group').'</a></span>';
	    }
	  }
	?>
	<?php
		$view = new stdClass();
		if($term->tid != 181){
			$view = views_get_view('blog');
			$view->set_display('block_blog_entries');
			$response = $view->preview('block_blog_entries');
		}
		else {
			$view->result = NULL;
		}

		$view1 = new stdClass();
		$view1 = views_get_view('blog');
		$view1->set_display('block_articles_entries');
		$response1 = $view1->preview('block_articles_entries');
	?>
	<div class="top-header <?php print $classes; ?> taxonomy-term-<?php print $term->tid; ?>" id="gr-info">
		<h1 class="page-title"><?php print render($term->name) . $edit_link; ?></h1>
		<div class="row">
			<div class="col-lg-8">
	    	  <div class="featured-image">
	    	  	<?php print render($content['field_image']); ?>
	    	  </div>
	    		<?php print render($content['description']); ?>
			</div>
			<div class="col-lg-4">
				<div class="contact-info">
					<h3><?php echo t('Contact information'); ?></h3>
					<p><i class="fa fa-map-marker" aria-hidden="true"></i> <?php echo $address; ?></p>
	      	<p><i class="fa fa-phone-square" aria-hidden="true"></i> <?php echo $phone; ?></p>
					<p><span style="color:<?php echo $color; ?>;"><?php echo get_term_name_by_tid($term->field_city['und'][0]['tid']); ?></span></p>
	      	<p><?php
	      	$likes = (isset($term->field_likes['und'][0]['value'])) ? $term->field_likes['und'][0]['value'] : '0';echo '<a class="btn-like" href="#" onclick="myModule_ajax_load('.$term->tid.')"><i class="fa fa-thumbs-up" aria-hidden="true"></i> '.t('I like').' <span id="ajax-target"> (' . $likes . ')</span> </a>';?></p>
	      	<script>
				  function myModule_ajax_load($tid) { jQuery("#ajax-target").load("/term/get/ajax/"+$tid);}
				 </script>
				</div>

				<div class="menu-info">
					<h3><?php echo t('Menu'); ?></h3>
					<ul>
						<li><a href="#gr-info"><i class="fa fa-info-circle" aria-hidden="true"></i> <?php echo t('Group information'); ?></a></li>
						<li><a href="#gr-publications"><i class="fa fa-file-text" aria-hidden="true"></i> <?php echo t('Publications'); ?></a></li>
						<li><a href="#gr-members"><i class="fa fa-users" aria-hidden="true"></i> <?php echo t('Members'); ?></a></li>
						<?php if(!empty($view->result)): ?>
							<li><a href="#gr-blog"><i class="fa fa-book" aria-hidden="true"></i> Blog</a></li>
						<?php endif; ?>
						<?php if(!empty($view1->result)): ?>
							<li><a href="#gr-articles"><i class="fa fa-book" aria-hidden="true"></i> <?php echo t('News'); ?></a></li>
						<?php endif; ?>
					</ul>
				</div>
			</div>
		</div>
	</div>
	<div class="bloques">
		<div class="row" id="componente">
			<div class="col-lg-12">
				<div class="publications gr-block" id="gr-publications">
					<?php echo theme('banrep_core_research_group_recent_publications', array('term' => $term)); ?>
				</div>
				<div class="members gr-block" id="gr-members">
					<?php echo theme('banrep_core_research_group_members_info', array('term' => $term, 'content' => $content, 'color' => $color)); ?>
				</div>
				<?php if(!empty($view->result)): ?>
					<div class="blog gr-block" id="gr-blog">
						<div class="blog-grupo">
							<h2 class="block__title color-white"><?php echo t('BLOG');?></h2>
	    				<?php print $response; ?>
    				</div>
					</div>
				<?php endif; ?>

				<?php if(!empty($view1->result)): ?>
					<div class="blog gr-block" id="gr-articles">
						<div class="blog-grupo">
							<h2 class="block__title color-white"><?php echo t('NEWS');?></h2>
	    				<?php print $response1; ?>
    				</div>
					</div>
				<?php endif; ?>

			</div>
		</div>
	</div>
<?php elseif($view_mode == 'teaser_research_group'): ?>
  <div class="row">
      <div class="col-lg-4">
        <div class="imagen"><?php print render($content['field_image']); ?></div>
      </div>
      <div class="col-lg-8">
        <div class="titulo"><a href="<?php echo $term_url; ?>"><?php print $term_name; ?></a></div>
        <div class="resumen">
        	<?php
	    			$description = '';
	    			if(isset($content['description']['#markup'])){
	    				$description = _banrep_recorte_palabras($content['description']['#markup'], 200);
	    			}
	    			print $description;
	    		?>
        </div>
	      <div class="text-group txt-<?php print quitar_tildes($city); ?>"><?php print $city; ?></div>
	      <?php if($address): ?>
	      <p class="dato-contacto"><i class="fa fa-map-marker" aria-hidden="true"></i> <strong><?php echo t('Address'). ':</strong> ' . $address; ?></p>
	      <?php endif; ?>

	      <?php if($phone): ?>
	      <p class="dato-contacto"><i class="fa fa-phone-square" aria-hidden="true"></i> <strong><?php echo t('Phone'). ':</strong> ' . $phone; ?></p>
	      <?php endif; ?>

	      <?php if($email): ?>
	      	<p class="dato-contacto"><i class="fa fa-envelope" aria-hidden="true"></i> <strong><?php echo t('Email'). ':</strong> ' . $email; ?></p>
	    	<?php endif; ?>
      </div>
  </div>
<?php endif; ?>

