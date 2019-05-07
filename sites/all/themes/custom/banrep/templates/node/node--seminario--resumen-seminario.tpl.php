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

$color = "";
if(isset($content['field_research_group']['#items'][0]['taxonomy_term']->field_color['und'][0]['value'])){
	$color = '#'.$content['field_research_group']['#items'][0]['taxonomy_term']->field_color['und'][0]['value'];
};

$mes = '';
$dia = '';
if(isset($content['field_event_date']['#items'][0]['value'])){
	$timestamp = $content['field_event_date']['#items'][0]['value'];
	$mes = substr(date("F", $timestamp), 0, 3);
	$dia = date("j", $timestamp);
}
?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix item-event" <?php print $attributes; ?>>
  <?php if(!empty($color)): ?><div class="research_group_color" style="background-color: <?php echo $color; ?>"></div><?php endif; ?>
  <div class="item-info clearfix">
  	<div class="info-left"><span class="mes"><?php echo $mes; ?></span><span class="dia"><?php echo $dia; ?></span></div>
  	<div class="info-right">
		<?php if ($title): ?>
			 <span class="date"><?php print render($content['field_event_date']); ?></span>
			 <h1<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h1>
		<?php endif; ?>
    <span class="city"><?php echo $content['field_place'][0]['#markup']; ?></span>
    </div>
  </div>
</article>
