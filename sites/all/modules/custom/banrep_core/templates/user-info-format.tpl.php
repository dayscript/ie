<?php
	$profile_url = "";
    $profile_view_url = isset($user->uid)?$user->uid:'';
	if(isset($user->picture->uri) && file_exists($user->picture->uri)){
	    $uri = $user->picture->uri;
	    $style_name = '140x140';
	    $profile_url = image_style_url($style_name, $uri);
	}else{
		$profile_url = get_default_profile_image();
	}
?>
<div class="user-info">
    <a href="/profile/<?php echo $profile_view_url ; ?>">
        <?php if(!empty($profile_url)): ?>
        	<div class="profile-image">
        		<img alt="140x140" class="img-circle img-responsive" src="<?php echo $profile_url; ?>" data-holder-rendered="true" style="">
        	</div>
        <?php endif; ?>
        <div class="position-name">
            <ul class="list-inline list-unstyled">
                <?php if(isset($user->field_full_name['und'][0]['value'])): ?>
            		<li><span class="name"><?php echo $user->field_full_name['und'][0]['value']; ?></span></li>
            	<?php endif; ?>
            	<?php if(isset($user->field_position['und'][0]['value'])): ?>
            		<li><span class="position"><?php echo $user->field_position['und'][0]['value']; ?></span></li>
            	<?php endif; ?>
            </ul>
        </div>
    </a>
</div>
