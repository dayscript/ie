<?php

$show_the_field_academics_profiles = __maybe_show_the_field('field_academics_profiles', $user_data['uid']); ?>
<?php if($show_the_field_academics_profiles && isset($user_data['field_academics_profiles']) && !empty($user_data['field_academics_profiles'])): ?>
  <div class="portlet portlet-sortable light bordered perfiles-academicos" id="perfiles-academicos">
   <div class="portlet-title keep-title">
      <div class="caption font-green-sharp">
         <i class="icon-speech font-green-sharp"></i>
         <span class="caption-subject bold uppercase"> <?php echo t("Academic Profiles"); ?>:</span>
      </div>
   </div>
   <div class="portlet-body">
        <div class="user-info">
    		<ul class="list-unstyled">
           <?php if(isset($user_data['field_academics_profiles']['field_academic_profile'])): ?>
              <?php if(isset($user_data['field_academics_profiles']['field_url']['url']) && ($user_data['field_academics_profiles']['field_academic_profile']->name)): ?>
                  <li>
                      <a href="<?php echo$user_data['field_academics_profiles']['field_url']['url']; ?>"><?php echo $user_data['field_academics_profiles']['field_academic_profile']->name; ?></a>
                  </li>
              <?php endif; ?>
           <?php else: ?>
      		    <?php foreach ($user_data['field_academics_profiles'] as $key => $academics_profile): ?>
      		    	<?php if(isset($academics_profile['field_url']['url']) && ($academics_profile['field_academic_profile']->name)): ?>
      			    	<li>
      			    		<a href="<?php echo $academics_profile['field_url']['url']; ?>"><?php echo $academics_profile['field_academic_profile']->name; ?></a>
      	            	</li>
                 <?php endif; ?>
      		    <?php endforeach; ?>
            <?php endif; ?>
        </ul>
        </div>
   </div>
  </div>
<?php endif; ?>
