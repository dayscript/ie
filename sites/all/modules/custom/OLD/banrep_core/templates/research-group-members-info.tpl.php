<div class="members-info clearfix" id="members-info">
  <h2 class="block__title"><?php echo t('MEMBERS');?></h2>
    <?php if(isset($content['field_members']['#items'])): ?>
	 	<?php foreach ($content['field_members']['#items'] as $key => $user): ?>
	 			<?php if($user['entity']->status): ?>
	 	    	<?php print(user_info_format_full($user['target_id'], $format = 'full', $color)); ?>
	 	  <?php endif; ?>
	 	<?php endforeach; ?>
	<?php endif; ?>
</div>
