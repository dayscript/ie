<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
  $members = array();
  if(!empty($node->field_members['und']) AND is_array($node->field_members['und'])){
    foreach ($node->field_members['und'] AS $key => $member) {
      if(isset($member['target_id'])) {
        $members[] = $member['target_id'];
      }
    }
  }
  $members = implode('+', $members);
  drupal_add_library('system', 'ui.accordion');
?>

<div class="row cree-center">
  <div class="col-lg-8 margin-bottom-20px">
    <div class="cree-item"><img src="<?= image_style_url('full_group', $node->field_image['und'][0]['uri']) ?>" /></div>
    <div class="cree-item"><p><?= $node->body['und'][0]['value'] ?></p></div>
    <div class="portlet no-padding clearfix transparent publicaciones-recientes portlet-sortable" id="recent-publications">
      <h2 class="block__title"><?= t('PUBLICATIONS');?></h2>
      <div id="cree_grupo_acordion">
        <?php 
          $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_articulos', $members);
          $result = count($view);
        ?>
        <?php if ($result): ?>
          <h3><?= t('Articles'); ?></h3>
          <div>
            <?= views_embed_view('publicaciones_perfil_usuario', 'perfil_pubs_articulos', $members); ?>
          </div>
        <?php endif; ?>
        <?php 
          $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_libros', $members);
          $result = count($view);
        ?>
        <?php if ($result): ?>
          <h3><?= t('Books'); ?></h3>
          <div>
            <?= views_embed_view('publicaciones_perfil_usuario', 'perfil_pubs_libros', $members); ?>
          </div>
        <?php endif; ?>
        <?php 
          $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_capitulos_libros', $members);
          $result = count($view);
        ?>
        <?php if ($result): ?>
          <h3><?= t('Book chapters'); ?></h3>
          <div>
            <?= views_embed_view('publicaciones_perfil_usuario', 'perfil_pubs_capitulos_libros', $members); ?>
          </div>
        <?php endif; ?>
        <?php 
          $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_documentos_trabajo', $members);
          $result = count($view);
        ?>
        <?php if ($result): ?>
          <h3><?= t('Working Papers'); ?></h3>
          <div>
            <?= views_embed_view('publicaciones_perfil_usuario', 'perfil_pubs_documentos_trabajo', $members); ?>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="col-lg-4 margin-bottom-22px">
    <div class="informacion-contacto">
      <div class="section-title"><h3><?= t('Información de Contacto') ?></h3></div>
      <div class="cree-item"><p><i class="fa fa-map-marker"></i><?= $node->field_address['und'][0]['value'] ?></p></div>
      <div class="cree-item"><p><i class="fa fa-phone"></i><?= $node->field_phone['und'][0]['value'] ?></p></div>
      <div class="cree-item"><p><i class="fa fa-envelope"></i><?= $node->field_email['und'][0]['value'] ?></p></div>
      <div class="cree-item"><p><?= !empty($node->field_city) ? $node->field_city['und'][0]['taxonomy_term']->name : null ?></p></div>
      <div class="cree-item">
      <!--<?php 
        $likes = (!empty($node->field_likes['und'][0]['value'])) ? $node->field_likes['und'][0]['value'] : '0';
        echo '<a class="btn-like" href="#" onclick="myModule_ajax_load('.$node->nid.')"><i class="fa fa-thumbs-up" aria-hidden="true"></i> '.t('I like').' <span id="ajax-target"> (' . $likes . ')</span> </a>';
      ?>-->
      
      </div>
    </div>
    <div class="cree-menu">
      <div class="section-title"><h3><?= t('Menú') ?></h3></div>
      <div class="cree-menu-link-container"><a href="#" class="cree-menu-link"><i class="fa fa-info-circle"></i>Información del grupo</a></div>
      <div class="cree-menu-link-container"><a href="#" class="cree-menu-link"><i class="fa fa-file-text"></i>Publicaciones</a></div>
      <div class="cree-menu-link-container"><a href="#" class="cree-menu-link"><i class="fa fa-users"></i>Miembros</a></div>
    </div>    
  </div>
</div>
