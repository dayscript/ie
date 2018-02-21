<ul class="list-inline list-dotted">
	<?php foreach($rows as $row): ?>
		<li class="editorial-resource">
			<?php
			$image_file = "";
			if(isset($row['field_icon']['uri'])) {
				$image_file = $row['field_icon']['uri'];
			}
			$title = "";
			if(isset($row['field_url']['title'])) {
				$title = $row['field_url']['title'];
			}
			$url = "";
			if(isset($row['field_url']['url'])) {
				$url = $row['field_url']['url'];
			}
			?>
			<a href="<?php echo $url; ?>">
			  <div class="field_url">
			     <?php echo $title; ?>
			  </div>
			  <div class="field_icon pull-right">
			    <img src="<?php echo image_style_url('original', $image_file); ?>" alt="<?php echo $title; ?>">
			  </div>
			</a>
		</li>
	<?php endforeach; ?> 
</ul>
                
