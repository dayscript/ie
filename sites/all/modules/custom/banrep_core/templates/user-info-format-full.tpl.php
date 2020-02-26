<?php
  global $language;
  if($language->language == 'es'){
    $prf = '/es';
  }
  else {
   $prf = '/en';
  }
	$profile_url = "";
	if(isset($user->picture->uri) && file_exists($user->picture->uri)){
	    $uri = $user->picture->uri;
	    $style_name = '140x140';
	    $profile_url = image_style_url($style_name, $uri);
	}else{
		$profile_url = get_default_profile_image();
	}

?>
<div class="col-lg-4 member-info">
  <div class="row">
    <?php if(!empty($profile_url)): ?>
    <div class="col-lg-4">
      <div class="profile-image">
        <img alt="profile" class="img-responsive" src="<?php echo $profile_url; ?>" data-holder-rendered="true">
      </div>
    </div>
    <?php endif; ?>
    <div class="col-lg-8">
      <div class="position-name">
            <?php if(isset($user->field_full_name['und'][0]['value'])): ?>
            <p class="name"><a href="<?php echo $prf; ?>/profile/<?php echo $user->uid; ?>" class=""><?php echo $user->field_full_name['und'][0]['value']; ?></a></p>
          <?php endif; ?>
          <?php if(isset($user->field_position['und'][0]['tid'])): ?>
            <p class="position"><?php echo get_term_name_by_tid($user->field_position['und'][0]['tid']); ?></p>
          <?php endif; ?>
      </div>
    </div>
  </div>
</div>
