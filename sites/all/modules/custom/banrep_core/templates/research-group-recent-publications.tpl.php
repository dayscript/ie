<?php
  $members = array();
  if(isset($term->field_members['und']) && is_array($term->field_members['und'])  && !empty($term->field_members['und'])){
    foreach ($term->field_members['und'] as $key => $member) {
      if(isset($member['target_id'])){
        $members[] = $member['target_id'];
      }
    }
  }
  $members = implode('+', $members);
?>
<div class="portlet no-padding clearfix transparent publicaciones-recientes portlet-sortable" id="recent-publications">
  <h2 class="block__title"><?php echo t('PUBLICATIONS');?></h2>
  <div id="pubs_grupo_acordion">
    <?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_destacados', $members);
      $result = count($view);
      if ($result):
    ?>
    <h3><?php echo t('Selected '); ?></h3>
    <div>
      <?php
      print views_embed_view(
        'publicaciones_perfil_usuario',
        'perfil_pubs_destacados',
        $members
      );
      ?>
    </div>
    <?php endif; ?>
    <?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_articulos', $members);
      $result = count($view);
      if ($result):
    ?>
    <h3><?php echo t('Articles'); ?></h3>
    <div>
      <?php
      print views_embed_view(
        'publicaciones_perfil_usuario',
        'perfil_pubs_articulos',
        $members
      );
      ?>
    </div>
    <?php endif; ?>
    <?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_libros', $members);
      $result = count($view);
      if ($result):
    ?>
    <h3><?php echo t('Books'); ?></h3>
    <div>
      <?php
      print views_embed_view(
        'publicaciones_perfil_usuario',
        'perfil_pubs_libros',
        $members
      );
      ?>
    </div>
    <?php endif; ?>
    <?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_capitulos_libros', $members);
      $result = count($view);
      if ($result):
    ?>
    <h3><?php echo t('Book chapters'); ?></h3>
    <div>
      <?php
      print views_embed_view(
        'publicaciones_perfil_usuario',
        'perfil_pubs_capitulos_libros',
        $members
      );
      ?>
    </div>
    <?php endif; ?>
    <?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_documentos_trabajo', $members);
      $result = count($view);
      if ($result):
    ?>
    <h3><?php echo t('Working Papers'); ?></h3>
    <div>
      <?php
      print views_embed_view(
        'publicaciones_perfil_usuario',
        'perfil_pubs_documentos_trabajo',
        $members
      );
      ?>
    </div>
    <?php endif; ?>
  </div>
</div>
