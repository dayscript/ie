<?php
$view = views_get_view('blog');
$view->set_display('block_blog_entries');
$response = $view->preview('block_blog_entries');
?>
<?php if(!empty($view->result)): ?>
<div class="blog-grupo" id="blog">
    <h2 class="block__title color-white"><?php echo t('BLOG');?></h2>
    <?php print $response; ?>
</div>
<?php endif; ?>
