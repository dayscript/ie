<?php $show_the_field_perfil = __maybe_show_the_field('field_perfil', $user_data['uid']); ?>
<?php if(isset($user_data['field_perfil'])): ?>
	<div class="portlet portlet-sortable light bordered" id="perfil">
	 <div class="portlet-body">
	    <div class="scroller"  data-rail-visible="1" data-rail-color="yellow" data-handle-color="#a1b2bd">
	       	<?php global $language; ?>
          <?php if($language->language == 'es'): ?>
            <p><?php echo decode_entities($user_data['field_perfil']); ?></p>
          <?php else: ?>
            <p><?php echo decode_entities($user_data['field_perfil_ingles']); ?></p>
          <?php endif; ?>
	    </div>
	 </div>
	</div>
<?php endif; ?>
