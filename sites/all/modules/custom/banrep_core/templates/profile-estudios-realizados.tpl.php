<?php if($user_data['field_studies_carried_out']): ?>
  <div id="estudios-realizados">
      <div class="user-info">
  		<ul class="list-unstyled">
        <?php if(!empty($user_data['field_studies_carried_out']['field_titulo'])): ?>
          <li>
          <div class="estudio"><strong><?php echo $user_data['field_studies_carried_out']['field_titulo']; ?>,</strong> <?php echo $user_data['field_studies_carried_out']['field_university']; ?>, <?php echo $user_data['field_studies_carried_out']['field_year']; ?></div>
          </li>
        <?php else: ?>
        <?php foreach ($user_data['field_studies_carried_out'] as $key => $item):?>
  	     <li>
      		<div class="estudio"><strong><?php echo $item['field_titulo']; ?>,</strong> <?php echo $item['field_university']; ?>, <?php echo $item['field_year']; ?></div>
        	</li>
        <?php endforeach; ?>
        <?php endif; ?>
          </ul>
      </div>
  </div>
<?php endif; ?>
