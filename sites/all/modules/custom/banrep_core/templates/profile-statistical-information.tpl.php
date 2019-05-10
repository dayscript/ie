<?php $show_the_field_likes = __maybe_show_the_field('field_likes', $user_data['uid']); ?>
<div class="portlet portlet-sortable light bordered statistical-information" id="statistical-information">
 <div class="portlet-title">
    <div class="caption font-green-sharp">
       <i class="icon-speech font-green-sharp"></i>
       <span class="caption-subject bold uppercase"> <?php echo t('Bibliometric Indicators'); ?></span>
    </div>
 </div>
 <div class="portlet-body">
	<ul class="list-inline list-statistical">
		    <li>
	    		<div class="statistical-item"><span class="left-icon citaciones"></span><div class="right-item"><strong>260</strong><br/>Citaciones</div></div>
        	</li>
		    <li>
	    		<div class="statistical-item"><span class="left-icon descargas"></span><div class="right-item"><strong>10</strong><br/>Descargas</div></div>
        	</li>
		    <li>
	    		<div class="statistical-item"><span class="left-icon vistas"></span><div class="right-item"><strong>50</strong><br/>Vistas</div></div>
        	</li>
        	<?php if($show_the_field_likes): ?>
			    <li>
			       <?php
				       	$field_likes = 0;
				       	if(isset($user_data['field_likes']) && !empty($user_data['field_likes'])){
							$field_likes = $user_data['field_likes'];
				       	}
			        ?>
		    		<div class="statistical-item likes-click" data-uid="<?php echo $user_data['uid']; ?>"><span class="left-icon me-gusta"></span><div class="right-item"><strong><?php echo $field_likes; ?></strong><br/>Me Gusta</div></div>
	        	</li>
        	<?php endif; ?>
        </ul>
 </div>
</div>
