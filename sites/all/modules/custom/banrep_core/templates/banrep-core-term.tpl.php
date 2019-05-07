<?php $active_class = ""; ?>
<div class="soluciones-caie">
		<div class="col-lg-3">
			<h2><?php echo t('SOLUTIONS'); ?></h2>
		</div>
		<div class="col-lg-9">
			<ul class="solution-items">
				<?php if(isset($items)): ?>
					<?php foreach ($items as $key => $item): ?>
						<?php
							$c = $key + 1;
							$iconclass = isset($item->field_icono_class['und'][0]['value']) ? $item->field_icono_class['und'][0]['value'] : '' ;
							$url = url('taxonomy/term/' . $item->tid);
							$icon = '<span class="' . $iconclass . '"></span>';
							$active = ( (isset($current_term->tid)) && ($current_term->tid == $item->tid) ) ? 'active-item' : '' ;
							if(!empty($active)){
								$active_class = 'item-' . $c;
							}
						?>
						<li class="<?php echo $active; ?> item-<?php echo $c; ?>"> <a href="<?php echo $url; ?>" title="<?php echo $item->name; ?>"><?php echo $icon; ?><strong class="item-title"><?php echo $item->name; ?></strong></a></li>
					<?php endforeach; ?>
				<?php endif; ?>
			</ul>
		</div>
		<div class="col-lg-12 active-item-description <?php echo $active_class; ?>">
			<?php echo $current_term->description; ?>
		</div>
</div>
