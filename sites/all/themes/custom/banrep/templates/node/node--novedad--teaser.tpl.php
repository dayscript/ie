<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>

<?php
// We hide the comments and links now so that maybe we can render them later.
hide($content['comments']);
hide($content['links']);
hide($content['field_revista_imagen']);
hide($content['body']);
hide($content['field_autor']);

$autor = '';
if($content['field_autor']['#items'][0]['value']){
  $autor = $content['field_autor']['#items'][0]['value'];
}

?>

<?php if (isset($content['field_revista_imagen']["#items"][0]["uri"])): ?>
  <?php $uri = $content['field_revista_imagen']["#items"][0]["uri"]; ?>
  <?php $style_name = 'thumbnail_100x67'; ?>
  <?php $image_url = image_style_url($style_name, $uri); ?>
<?php endif; ?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix item" <?php print $attributes; ?>>
  <div class="item-info">
  	<img class="info-left" src="<?php echo $image_url; ?>" alt="">
  	<div class="info-right">	
		<?php if ($title): ?>
			 <h1<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h1>
		<?php endif; ?>
		<?php if($content['body']['#items'][0]['value']): ?>
			<div class="summary">
				<?php print render($content['body']); ?>
			</div>
		<?php endif; ?>
    </div>
	<?php if(!empty($autor)): ?>
		<span class="autor grey-text"> <strong>Autor:</strong> <?php echo $autor; ?> </span>
	<?php endif; ?>
  </div>
</article>