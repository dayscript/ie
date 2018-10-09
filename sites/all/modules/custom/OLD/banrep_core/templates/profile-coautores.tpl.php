<?php if (is_array($user_data['co_authors'])) : ?>
  <div class="portlet-autores" id="coautores">
    <?php foreach ($user_data['co_authors'] as $uid) : ?>
        <?php print(get_user_info_format($uid)); ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>
