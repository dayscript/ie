<?php
/**
 * @file
 * Returns HTML for a picture configured for the user's account.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728110
 */
$user_picture = str_replace("/users/", "/profile/", $user_picture);
?>
<?php if ($user_picture): ?>
  <span class="user-picture">
    <?php print $user_picture; ?>
  </span>
<?php endif; ?>
