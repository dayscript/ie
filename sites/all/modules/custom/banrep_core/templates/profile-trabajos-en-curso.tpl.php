<div class="user-info">
	<ul class="list-inline list-unstyled">
	<?php foreach ($user_data['field_trabajos_en_curso'] as $key => $work_in_progress): ?>
		<?php if($work_in_progress['field_estado_trabajo'] == 'publico'): ?>
		<li>
		    <div class="col-lg-4">
		    	<strong>Proyecto</strong><br>
		    	<p><?php echo $work_in_progress['field_titulo_trabajo'];?></p>
		    </div>
		    <div class="col-lg-4">
		    	<strong>Áreas Temáticas</strong><br>
		    	<ul>
		    	<?php foreach ($work_in_progress['field_areas_tematicas'] as $key => $tags): ?>
		    		<li>
						<p><?php echo $tags->name;?></p>
		    		</li>
		    	<?php endforeach; ?>
		    	</ul>
		    </div>
		    <div class="col-lg-4">
		    	<strong>Objetivo</strong><br>
				<p><?php echo $work_in_progress['field_objetivo_trabajo'];?></p>
			</div>
		</li>
		<?php endif; ?>
	<?php endforeach; ?>
	</ul>
</div>