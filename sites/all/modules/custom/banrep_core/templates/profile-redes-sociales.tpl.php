<?php $show_the_field_social_networks = __maybe_show_the_field('field_social_networks', $user_data['uid']); ?>
<?php if($show_the_field_social_networks && isset($user_data['field_social_networks']) && !empty($user_data['field_social_networks'])): ?>
<?php
  $c = count($user_data['field_social_networks']);
  $es_unico = FALSE;
    if($c == 2) {
      if(isset($user_data['field_social_networks']['field_social_network'])){
        $es_unico = TRUE;
      }
      else {
        $es_unico = FALSE;
      }
    }
    else {
      $es_unico = FALSE;
    }
?>
  <div class="portlet portlet-sortable light bordered redes-sociales" id="redes-sociales">
   <div class="portlet-body">
      <div class="user-info">
    		<ul class="list-inline list-unstyled">
          <?php if($es_unico): ?>
  			    	<li>
  			    		<a href="<?php echo $user_data['field_social_networks']['field_social_network']->field_url['url']; ?>"><span class="icon-<?php echo strtolower($user_data['field_social_networks']['field_social_network']->name); ?>"></span></a>
  	         </li>
          <?php else: ?>
            <?php foreach ($user_data['field_social_networks'] as $key => $social_network): ?>
              <?php if(isset($social_network['field_social_network']->name) && ($social_network['field_url']['url'])): ?>
                <li>
                  <a href="<?php echo $social_network['field_url']['url']; ?>"><span class="icon-<?php echo strtolower($social_network['field_social_network']->name); ?>"></span></a>
               </li>
              <?php endif; ?>
            <?php endforeach; ?>
          <?php endif; ?>
        </ul>
      </div>
   </div>
  </div>
  <?php endif; ?>
