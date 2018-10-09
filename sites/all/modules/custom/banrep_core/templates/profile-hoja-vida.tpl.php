<?php $show_the_field_cv_file = __maybe_show_the_field('field_cv_file', $user_data['uid']); ?>
<?php if($show_the_field_cv_file && isset($user_data['field_cv_file']['uri'])): ?>
	<div class="portlet portlet-sortable light bordered" id="hoja-vida">
		 <div class="portlet-title">
		    <div class="caption font-green-sharp">
		       <i class="icon-speech font-green-sharp"></i>
		       <span class="caption-subject bold uppercase"> <?php echo t('Hoja de Vida'); ?>:</span>
		    </div>
		 </div>
		 <div class="portlet-body">
		    <div class="user-info">
				<a class="btn blue" target="_blank" href="<?php echo file_create_url($user_data['field_cv_file']['uri']); ?>"><?php echo t('Hoja de Vida'); ?></a>
		    </div>
		 </div>
	</div>
<?php endif; ?>