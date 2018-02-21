<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
global $language;
$term = $row->field_field_position[0]['raw']['taxonomy_term'];
$term = i18n_taxonomy_term_get_translation($term, $language->language);
$row->field_field_position[0]['rendered']['#markup'] = $term->name;
$user = $row->_field_data['uid']['entity'];
?>
<div class="profile-image"><a href="/en/profile/<?php echo $user->uid; ?>"><span class="user-picture"><?php echo theme('image_style', array('style_name' => 'teaser_profile', 'path' => $user->picture->uri)); ?></span></a></div>
<div class="user-info">
<div class="full-name"><a href="/en/profile/<?php echo $user->uid; ?>"><?php echo $row->field_field_surnames[0]['rendered']['#markup']; ?>, <?php echo $row->field_field_names[0]['rendered']['#markup']; ?></a></div>
<div class="position"><?php echo $row->field_field_position[0]['rendered']['#markup']; ?></div>
<div class="text-group txt-<?php echo $row->field_field_city[0]['rendered']['#markup']; ?>"><?php echo $row->field_field_city[0]['rendered']['#markup']; ?></div>
</div>
