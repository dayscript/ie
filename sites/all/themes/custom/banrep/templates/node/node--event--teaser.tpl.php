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
hide($content['field_event_date']);
$url = '';
if(isset($content['field_url_archivo_historial'])){
	$url = $content['field_url_archivo_historial']['#items'][0]['url'];
}
$mes = '';
$dia = '';
if(isset($content['field_event_date']['#items'][0]['value'])){
	$timestamp = $content['field_event_date']['#items'][0]['value'];
	$mes = substr(date("F", $timestamp), 0, 3);
	$dia = date("j", $timestamp);
}

?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix item-event" <?php print $attributes; ?>>
  <div class="item-info clearfix">
  	<div class="info-left"><span class="mes"><?php echo $mes; ?></span><span class="dia"><?php echo $dia; ?></span></div>
  	<div class="info-right">
		<?php if ($title): ?>
			 <h3<?php print $title_attributes; ?>>
			 <a href="/node/<?php print $node->nid; ?>" target="_blank">
			 	<?php print $title; ?>
			 </a>
			 </h3>
		<?php endif; ?>
    </div>
  </div>
</article>
