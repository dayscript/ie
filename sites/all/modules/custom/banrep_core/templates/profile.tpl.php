<?php
	global $language;

	$show_the_field_studies_carried_out = __maybe_show_the_field('field_studies_carried_out', $user_data['uid']);
	$show_estudios_realizados = FALSE;
	if($show_the_field_studies_carried_out && isset($user_data['field_studies_carried_out']) && !empty($user_data['field_studies_carried_out'])){
		$show_estudios_realizados = TRUE;
	}

	if(user_is_logged_in() && !isset($user_data['only_personal_information'])){
		global $user;
		if($user_data['uid'] == $user->uid){
			$sort = '<span class="sort-action pull-right"><a class="action-link" href="/' . $language->language . '/profile/edit"><span class="icon-usuario"></span> ' . t('Edit profile') . '</a></span>';
		}
	}
?>
<div class="row">
	<div class="col-lg-12">
		<?php echo theme('banrep_core_profile_profile-info', array('user_data' => $user_data)); ?>
<?php if (!isset($user_data['only_personal_information'])) {?>
		
		<div id="tabs">
			<ul>
					<li><a href="#tabs-1"><?php echo t('Publications'); ?></a></li>
					<?php if($show_estudios_realizados): ?><li><a href="#tabs-2"><?php echo t('Academic formation'); ?></a></li><?php endif; ?>

					<?php
					$r = get_other_publications($user_data['uid']);
					if(!empty($r)): ?>
					<li><a href="#tabs-3"><?php echo t('Other academic activities'); ?></a></li>
				<?php endif; ?>

				<?php if(!empty($user_data['co_authors']) || !empty($user_data['otros_coautores'])): ?>
					<li><a href="#tabs-4"><?php echo t('Co-authors'); ?></a></li>
				<?php endif; ?>
				<?php $mis_enlaces_recomendados = get_mis_enlaces_recomendados( $user_data['uid'], 'publico' );
				if($mis_enlaces_recomendados != FALSE): ?>
				<li><a href="#tabs-5"><?php echo t('Recommended'); ?></a></li>
			<?php endif; ?>
		</ul>

		<div id="tabs-1">
			<div class="tabs-wrapper" id="pubs_perfil_acordion">
				<?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_destacados', $user_data['uid']);
					$result = count($view);
					if ($result):
				?>
				<h3><?php echo t('Selected '); ?></h3>
				<div>
					<?php
						print views_embed_view(
							'publicaciones_perfil_usuario',
							'perfil_pubs_destacados',
							$user_data['uid']
						);
					?>
				</div>
				<?php endif; ?>
				<?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_articulos', $user_data['uid']);
					$result = count($view);
					if ($result):
				?>
				<h3><?php echo t('Articles'); ?></h3>
				<div>
					<?php
					echo views_embed_view('publicaciones_perfil_usuario', 'perfil_pubs_articulos', $user_data['uid']);
					?>
				</div>
				<?php endif; ?>
				<?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_libros', $user_data['uid']);
					$result = count($view);
					if ($result):
				?>
				<h3><?php echo t('Books'); ?></h3>
				<div>
					<?php
					print views_embed_view(
						'publicaciones_perfil_usuario',
						'perfil_pubs_libros',
						$user_data['uid']
					);
					?>
				</div>
				<?php endif; ?>
				<?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_capitulos_libros', $user_data['uid']);
					$result = count($view);
					if ($result):
				?>
				<h3><?php echo t('Book chapters'); ?></h3>
				<div>
					<?php
					print views_embed_view(
						'publicaciones_perfil_usuario',
						'perfil_pubs_capitulos_libros',
						$user_data['uid']
					);
					?>
				</div>
				<?php endif; ?>
				<?php $view = views_get_view_result('publicaciones_perfil_usuario', 'perfil_pubs_documentos_trabajo', $user_data['uid']);
					$result = count($view);
					if ($result):
				?>
				<h3><?php echo t('Working Papers'); ?></h3>
				<div>
					<?php
					print views_embed_view(
						'publicaciones_perfil_usuario',
						'perfil_pubs_documentos_trabajo',
						$user_data['uid']
					);
					?>
				</div>
				<?php endif; ?>
			</div>
		</div>
		<?php if($show_estudios_realizados): ?>
			<div id="tabs-2">
				<div class="tabs-wrapper">
					<?php echo theme('banrep_core_profile_estudios-realizados', array('user_data' => $user_data)); ?>
				</div>
			</div>
		<?php endif; ?>
		<?php if($r): ?>
			<div id="tabs-3">
				<div class="tabs-wrapper">
				<?php echo theme('banrep_core_profile_otras_actividades_academicas', array('user_data' => $user_data)); ?>
				</div>
			</div>
		<?php endif; ?>
		<?php if(!empty($user_data['co_authors']) || !empty($user_data['otros_coautores'])): ?>
			<div id="tabs-4">
				<div class="tabs-wrapper">
					<div class="row">
						<div class="col-lg-12">
							<?php echo theme('banrep_core_profile_coautores', array('user_data' => $user_data)); ?>
							<?php echo theme('banrep_core_profile_otros_coautores', array('user_data' => $user_data)); ?>
						</div>

					</div>
				</div>
			</div>
		<?php endif; ?>
		<?php if(isset($user_data['uid'])):
			if($mis_enlaces_recomendados != FALSE): ?>
			<div id="tabs-5">
				<div class="tabs-wrapper">
					<div class="block-mis-enlaces-recomendados">
						<?php $user_favorites = module_invoke('banrep_investigador', 'block_view', 'user_favorites'); ?>
						<?php print $user_favorites['content']; ?>
					</div>
				</div>
			</div>
			<?php endif; ?>
		<?php endif; ?>
		</div>
	</div>
</div>

<?php } ?>
