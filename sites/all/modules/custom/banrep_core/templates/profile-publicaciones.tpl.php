<?php if(isset($user_data['uid'])): ?>
	<div class="portlet portlet-sortable light bordered" id="publicaciones">
	 <div class="portlet-body dos">
	    <?php print views_embed_view('publicaciones', 'perfil_publicaciones', $user_data['uid']); ?>
	    <div class="rss-researcher clearfix">
	      <a href="/profile/<?php echo $user_data['uid']; ?>/rss.xml" class="feed-icon" title="Suscribirse a Publicaciones" target="_blank"><img typeof="foaf:Image" src="/misc/feed.png" width="16" height="16" alt="Suscribirse a Publicaciones"></a>
	    </div>
	 </div>
	</div>
<?php endif; ?>
