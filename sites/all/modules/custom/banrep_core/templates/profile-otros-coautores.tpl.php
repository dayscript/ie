<?php module_load_include('inc', 'banrep_core', 'banrep_core.functions.inc'); ?>
<?php if (is_array($user_data['otros_coautores'])) : ?>
	<ul class="portlet-autores" id="otros_coautores">
	 	<?php foreach ($user_data['otros_coautores'] as $key => $coautor): ?>
	 		<?php
	 		  $url = '';
	 		  $url = 'http://www.banrep.gov.co';
	 		  $title = '';
	 		  $title = get_other_co_author_name($coautor);
	 		?>
	 		<?php if(!empty($title)): ?>
	 			<div class="user-info">
	 				<div class="profile-image">
        		<img alt="profile" class="img-circle img-responsive" src="/sites/all/themes/custom/banrep/images/user-profile.png" data-holder-rendered="true">
        	</div>
	 				<div class="position-name">
	 					<span class="name"><?php echo $title; ?></span>
	 				</div>
	 			</div>
	 		<?php endif; ?>
	 	<?php endforeach; ?>
	</ul>
<?php endif; ?>
