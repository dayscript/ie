<?php $user_data['field_trabajos_en_curso'] = isset($user_data['field_trabajos_en_curso'][0]) ? $user_data['field_trabajos_en_curso'] : array($user_data['field_trabajos_en_curso']);
foreach ($user_data['field_trabajos_en_curso'] as $key => $work_in_progress): ?>
	<div class="row">
        <div class="col-lg-12 user-info">
			<?php if($work_in_progress['field_estado_trabajo'] == 'publico'): ?>
			    <div class="col-lg-4">
			    	<strong>Proyecto</strong><br>
			    	<p><?php echo $work_in_progress['field_titulo_trabajo'];?></p>
			    </div>
			    <div class="col-lg-4">
			    	<strong>Áreas Temáticas</strong><br>
			    	<ul>
			    	<?php foreach ($work_in_progress['field_areas_tematicas'] as $key => $tags): ?>
						<li><p><?php echo $tags->name;?></p></li>
			    	<?php endforeach; ?>
			    	</ul>
			    </div>
			    <div class="col-lg-4">
			    	<strong>Objetivo</strong><br>
					<p><?php echo $work_in_progress['field_objetivo_trabajo'];?></p>
				</div>
			<?php endif; ?>
	</div>
</div>
<?php endforeach; ?>