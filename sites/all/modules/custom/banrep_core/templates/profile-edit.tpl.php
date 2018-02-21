<?php $iconsuccess = '<div class="messages__icon"><svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="24" height="24" viewBox="0 0 64 64"><path d="M54 8l-30 30-14-14-10 10 24 24 40-40z" fill="#000000"></path></svg></div>'; ?>
<div class="ui-tab-profile-edit">
	<div id="tabs">
	  <ul>
	    <li><a href="#tabs-description"><?php echo t('Description'); ?></a></li>
	    <li><a href="#tabs-investigation-lines"><?php echo t('Investigation Lines'); ?></a></li>
	    <li><a href="#tabs-social-networks"><?php echo t('Social networks'); ?></a></li>
	    <li><a href="#tabs-recommended-links"><?php echo t('Recommended Links'); ?></a></li>
	    <li><a href="#tabs-access-data"><?php echo t('Access Data'); ?></a></li>
	    <li><a href="#tabs-work-in-progress"><?php echo t('Work in progress'); ?></a></li>
	    <li><a href="#tabs-cv"><?php echo t('Curriculum Vitae'); ?></a></li>
	    <?php
	    	global $user;
	    	$r_inv = user_role_load_by_name('investigador');
	    	if (user_has_role($r_inv->rid)) {
	    		print '<li><a href="#tabs-formation">' . t('Formation') . '</a></li>';
	    		print '<li><a href="#tabs-academic-profiles">' . t('Academic Profiles') . '</a></li>';
	    	}
	    ?>
	  </ul>
	  <div id="tabs-description">
	    <h3 class="tab-title"><?php echo t('Description'); ?></h3>
	    <div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_description_form = drupal_get_form('profile_description_form', $account);
			$profile_description_form_box = drupal_render($profile_description_form);
		?>
	    <?php echo $profile_description_form_box; ?>
	  </div>
	  <div id="tabs-investigation-lines">
	  	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_investigation_lines_form = drupal_get_form('profile_investigation_lines_form', $account);
			$profile_investigation_lines_form_box = drupal_render($profile_investigation_lines_form);
		?>
	    <?php echo $profile_investigation_lines_form_box; ?>
	  </div>
	  <div id="tabs-social-networks">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_social_networks_form = drupal_get_form('profile_social_networks_form', $account);
			$profile_social_networks_form_box = drupal_render($profile_social_networks_form);
		?>
	    <?php echo $profile_social_networks_form_box; ?>
	  </div>
      <?php if (user_has_role($r_inv->rid)) { ?>

	  <div id="tabs-formation">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_formation_form = drupal_get_form('profile_formation_form', $account);
			$profile_formation_form_box = drupal_render($profile_formation_form);
		?>
	    <?php echo $profile_formation_form_box; ?>
	  </div>

	  <div id="tabs-academic-profiles">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_academic_profiles_form = drupal_get_form('profile_academic_profiles_form', $account);
			$profile_academic_profiles_form_box = drupal_render($profile_academic_profiles_form);
		?>
	    <?php echo $profile_academic_profiles_form_box; ?>
	  </div>
	  
      <?php } ?>

	  <div id="tabs-access-data">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
	    <h3 class="tab-title"><?php echo t('Access Data'); ?></h3>
		<?php
			$profile_access_data_form = drupal_get_form('profile_access_data_form', $account);
			$profile_access_data_form_box = drupal_render($profile_access_data_form);
		?>
	    <?php echo $profile_access_data_form_box; ?>
	  </div>
	  <div id="tabs-cv">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?></div>
	 	<?php
			$profile_cv_form = drupal_get_form('profile_cv_form', $account);
			$profile_cv_form_box = drupal_render($profile_cv_form);
			echo $profile_cv_form_box;
		?>
	  </div>
	  <div id="tabs-recommended-links">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_recommended_links_form = drupal_get_form('profile_recommended_links_form', $account);
			$profile_recommended_links_form_box = drupal_render($profile_recommended_links_form);
		?>
	    <?php echo $profile_recommended_links_form_box; ?>
	  </div>
	  <div id="tabs-work-in-progress">
	 	<div class="messages status hide"><h2 class="element-invisible">Status Message</h2><?php echo $iconsuccess; ?><pre></pre></div>
		<?php
			$profile_work_in_progress_form     = drupal_get_form('profile_work_in_progress_form', $account);
			$profile_work_in_progress_form_box = drupal_render($profile_work_in_progress_form);
		?>
	    <?php echo $profile_work_in_progress_form_box; ?>
	  </div>
	</div>
</div>
