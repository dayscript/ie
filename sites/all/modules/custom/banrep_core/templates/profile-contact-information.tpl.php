<?php
   $show_the_field_dependency = __maybe_show_the_field('field_dependency', $user_data['uid']);
   $show_the_field_email_corporate = __maybe_show_the_field('field_email_corporate', $user_data['uid']);
   $show_the_field_email_personal = __maybe_show_the_field('field_email_personal', $user_data['uid']);
   $show_the_field_research_lines = __maybe_show_the_field('field_research_lines', $user_data['uid']);
   $show_contact_button = 0;
?>

<?php if($show_the_field_dependency || $show_the_field_email_corporate || $show_the_field_email_personal || $show_the_field_research_lines): ?>
    <div class="portlet portlet-sortable light bordered contact-information" id="contact-information">
     <div class="portlet-title">
        <div class="caption font-green-sharp">
           <i class="icon-speech font-green-sharp"></i>
           <span class="caption-subject bold uppercase"> <?php echo t('Contact information'); ?></span>
        </div>
     </div>
     <div class="portlet-body">
        <div class="user-info">
    		<ul class="list-inline list-unstyled">
                <?php if($show_the_field_dependency): ?>
                	<li>
                	 	<strong><?php echo t('Group or Dependency'); ?>:</strong> <span><?php echo $user_data['field_dependency']; ?></span>
                	</li>
                <?php endif; ?>


                <?php if( (!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate) || (!empty($user_data['field_email_personal']) && $show_the_field_email_personal)): ?>
                	<li>
                	 	<strong><?php echo t('Contact'); ?>:</strong> <span>
                        <?php if(!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate): ?>
                        <a href="mailto:<?php echo $user_data['field_email_corporate']; ?>"><?php echo t('Institutional'); ?></a>
                        <?php $show_contact_button = 1;?>
                    <?php endif; ?>

                    <?php if(!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate && !empty($user_data['field_email_personal']) && $show_the_field_email_personal): ?>/<?php endif; ?>
                    <?php if(!empty($user_data['field_email_personal']) && $show_the_field_email_personal): ?>
                        <a href="mailto:<?php echo $user_data['field_email_personal']; ?>"><?php echo t('Personal'); ?></a>
                        <?php $show_contact_button = 1;?>
                    <?php endif; ?>
                    </span>
                	</li>
                <?php endif; ?>
                <?php if($show_contact_button == 0): ?>
                    <li>
                        <strong><?php echo t('Contact'); ?>:</strong><br><button type="button" class="btn btn-warning" data-remodal-target="contact-modal"><?php echo t('Leave message'); ?></button>

                    </li>
                    <div class="remodal" data-remodal-id="contact-modal">
                      <a data-remodal-action="close" class="remodal-close"></a>

                      <?php
                        $send_mail = (!empty($user_data['field_email_corporate'])) ? $user_data['field_email_corporate'] : (!empty($user_data['field_email_personal']) ? $user_data['field_email_personal'] : $user_data['mail']);
                        $form_send = drupal_get_form('_user_send_mail_custom', $send_mail);
                        print render($form_send);
                      ?>
                    </div>
                <?php endif; ?>
            	<li>
            	 	<strong><?php echo t('City'); ?>:</strong> <span><?php echo $user_data['field_city']; ?></span>
            	</li>
                <?php if($show_the_field_research_lines  && isset($user_data['field_research_lines'])): ?>
                    <?php if(is_array($user_data['field_research_lines'])): ?>
                    	<li>
                    	 	<strong><?php echo t('Research Lines'); ?>:</strong> <div class="research-lines"><?php echo implode("<br/>", $user_data['field_research_lines']); ?></div>
                    	</li>
                    <?php else: ?>
                        <li>
                            <strong><?php echo t('Research Lines'); ?>:</strong> <div class="research-lines"><?php echo $user_data['field_research_lines']; ?></div>
                        </li>
                    <?php endif; ?>
                <?php endif; ?>
            </ul>
        </div>
     </div>
    </div>
<?php endif; ?>
