<?php
global $language;
$show_the_field_dependency = __maybe_show_the_field('field_dependency', $user_data['uid']);
$show_the_field_email_corporate = __maybe_show_the_field('field_email_corporate', $user_data['uid']);
$show_the_field_email_personal = __maybe_show_the_field('field_email_personal', $user_data['uid']);
$show_the_field_research_lines = __maybe_show_the_field('field_research_lines', $user_data['uid']);
$show_contact_button = 1;

$show_the_field_academics_profiles = __maybe_show_the_field('field_academics_profiles', $user_data['uid']);
$show_the_field_social_networks = __maybe_show_the_field('field_social_networks', $user_data['uid']);
$show_the_field_cv_file = __maybe_show_the_field('field_cv_file', $user_data['uid']);
?>
<div class="user-info">
  <div class="col-lg-2 left-data">
    <?php
    $profile_url = '';
    if (isset($user_data['picture']->uri) && file_exists($user_data['picture']->uri)) {
        $uri = $user_data['picture']->uri;
        $style_name = '140x140';
        $profile_url = image_style_url($style_name, $uri);
    } else {
        $profile_url = get_default_profile_image();
    }
    ?>
    <?php if (!empty($profile_url)) : ?>
      <div class="profile-image text-center">
        <img
         alt="<?php echo $user_data['field_full_name']; ?>"
         class="img-normal"
         src="<?php echo $profile_url; ?>"
         data-holder-rendered="true"
         style=""
        >
      </div>
    <?php endif; ?>
    <ul class="list-unstyled text-center">
        <?php if ($show_the_field_cv_file && isset($user_data['field_cv_file']['uri'])) : ?>
        <li>
          <a
           class="btn blue hv"
           target="_blank"
           href="<?php echo file_create_url($user_data['field_cv_file']['uri']); ?>"
          >
            <i class="fa fa-download" aria-hidden="true"></i>
              <?php echo t('CV'); ?>
          </a>
        </li>
        <?php endif; ?>
      <!-- END Hoja de Vida -->

      <!-- BEGIN Redes Sociales -->
      <?php if($show_the_field_social_networks && isset($user_data['field_social_networks']) && !empty($user_data['field_social_networks'])): ?>
        <?php
        if (count($user_data['field_social_networks']) == 2 && isset($user_data['field_social_networks']['field_social_network'])) {
          $user_data['field_social_networks'] = array($user_data['field_social_networks']);
        }
        ?>
        <li class="label">
          <ul class="list-inline social-networks">
            <?php foreach ($user_data['field_social_networks'] as $social_network): ?>
              <?php if(isset($social_network['field_social_network']->name) && ($social_network['field_url']['url'])): ?>
                <?php
                $social_network_name = strtolower($social_network['field_social_network']->name);
                ?>
                <li>
                  <a href="<?php echo $social_network['field_url']['url']; ?>">
                    <span class="icon-<?php echo $social_network_name; ?>"></span>
                  </a>
               </li>
              <?php endif; ?>
            <?php endforeach; ?>
          </ul>
        </li>
      <?php endif; ?>
      <!-- END Redes Sociales -->
    </ul>
    <div class="row">
        <?php if($user_data['field_likes']): ?>
          <div class="col-lg-12 text-center">
            <div class="btn-like">
              <?php $likes = ($user_data['field_likes']) ? $user_data['field_likes'] : NULL; ?>
                <?php echo '<a class="like" title="Me gusta" href="#" onclick="myModule_ajax_load('.$user_data['uid'].')"><i class="fa fa-thumbs-up" aria-hidden="true"></i><span id="ajax-target"> ' . t('I like ') . '(' . $likes . ')</span> </a>';?>
              <script>
                function myModule_ajax_load($uid) {
                  jQuery("#ajax-target").load("/user/get/ajax/"+$uid);
                }
               </script>
            </div>
          </div>
        <?php endif; ?>
        <div class="col-lg-12 text-center">
          <?php if((!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate) || (!empty($user_data['field_email_personal']) && $show_the_field_email_personal)): ?>
          <div class="contacto">
            <strong>
              <?php echo t('Contact'); ?>:
            </strong>
            <span>
            <?php if(!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate): ?>
              <a href="mailto:<?php echo $user_data['field_email_corporate']; ?>">
                <?php echo t('Institutional'); ?>
              </a>
            <?php $show_contact_button = 1;?>
            <?php endif; ?>

            <?php if(!empty($user_data['field_email_corporate']) && $show_the_field_email_corporate && !empty($user_data['field_email_personal']) && $show_the_field_email_personal): ?>/<?php endif; ?>

              <?php if(!empty($user_data['field_email_personal']) && $show_the_field_email_personal): ?>
                <a href="mailto:<?php echo $user_data['field_email_personal']; ?>">
                  <?php echo t('Personal'); ?>
                </a>
                <?php $show_contact_button = 1; ?>
              <?php endif; ?>
            </span>
          </div>
        <?php endif; ?>

        <!-- BEGIN Dejar mensaje -->
        <?php if($show_contact_button == 0): ?>
          <div class="contact-msg">
            <a href="#" data-remodal-target="contact-modal" title="<?php echo t('Leave message'); ?>"><i class="fa fa-envelope" aria-hidden="true"></i>
            </a>
          </div>
          <div class="remodal" data-remodal-id="contact-modal">
            <a data-remodal-action="close" class="remodal-close"></a>
            <?php
              $send_mail = (!empty($user_data['field_email_corporate'])) ? $user_data['field_email_corporate'] : (!empty($user_data['field_email_personal']) ? $user_data['field_email_personal'] : $user_data['mail']);
              $form_send = drupal_get_form('_user_send_mail_custom', $send_mail);
              print render($form_send);
            ?>
          </div>
        <?php endif; ?>
        <!-- END Dejar mensaje -->
        </div>
      </div>
  </div>
  <div class="col-lg-10 right-data">
    <div class="position-name">
      <?php if(__maybe_show_the_field('field_full_name', $user_data['uid'])): ?>
        <div class="name">
          <?php global $user; ?>
          <?php if($user->uid == $user_data['uid']): ?>
            <?php
            echo
              $user_data['field_full_name'] .
              ' <span>' .
                l(t('Edit profile'), 'profile/edit') .
              '<span>'
            ;
            ?>
          <?php else: ?>
            <?php echo $user_data['field_full_name']; ?>
          <?php endif; ?>
        </div>
      <?php endif; ?>
    </div>
    <?php if($show_the_field_dependency || $show_the_field_email_corporate || $show_the_field_email_personal || $show_the_field_research_lines): ?>
      <div class="aditional-info">
        <!-- BEGIN Último nivel educativo -->
        <?php
        if (isset($user_data['field_studies_carried_out'])) {
          echo '<div>' . $user_data['field_studies_carried_out'][0]['field_titulo'] . '</div>';
        }
        ?>
        <!-- END Último nivel educativo -->
        <!-- BEGIN Lineas de Investigación -->
        <?php if($show_the_field_research_lines  && !empty($user_data['field_research_lines'])): ?>
          <?php if(is_array($user_data['field_research_lines'])): ?>
            <?php
              $lineas = _banrep_obtener_lineas_codigo($user_data['field_research_lines']);
              $lineas_tid = _banrep_obtener_lineas_tid($user_data['field_research_lines']);
            ?>
            <div class="lineas">
              <strong>
                <?php echo t('Research Lines'); ?>:
              </strong>
              <div class="research-lines">
                <ul>
                <?php foreach ($lineas as $key => $linea): ?>
                  <?php if($language->language == 'es'): ?>
                    <?php $url_linea = url( 'investigadores', array('query' => array('nombre' => '', 'linea' => $lineas_tid[$key], 'city' => 'All'))); ?>
                  <?php else: ?>
                    <?php $url_linea = url( 'researchers', array('query' => array('field_full_name_value' => '', 'linea' => $lineas_tid[$key], 'city' => 'All'))); ?>
                  <?php endif; ?>
                  <li><a href="<?php echo $url_linea; ?>"><?php echo trim($linea); ?></a></li>
                <?php endforeach; ?>
                </ul>
              </div>
            </div>
          <?php else: ?>
            <div class="lineas">
              <strong>
                <?php echo t('Research Lines'); ?>:
              </strong>
              <div class="research-lines">
                <?php echo $lineas; ?>
              </div>
            </div>
          <?php endif; ?>
        <?php endif; ?>
        <!-- END Lineas de Investigación -->

        <!-- BEGIN Perfiles academicos -->
        <?php if($show_the_field_academics_profiles && isset($user_data['field_academics_profiles']) && !empty($user_data['field_academics_profiles'])): ?>
          <?php $academics_profiles_order = get_academics_profiles_order(); ?>
          <div class="perfiles">
            <div class="font-green-sharp">
              <i class="icon-speech font-green-sharp"></i>
              <strong class="caption-subject bold uppercase">
                <?php echo t("Academic Profiles"); ?>:
              </strong>
            </div>
            <?php if(isset($user_data['field_academics_profiles']['field_academic_profile'])): ?>
              <ul class="list-inline sub-list-style-simple">
                <?php if(isset($user_data['field_academics_profiles']['field_url']['url']) && ($user_data['field_academics_profiles']['field_academic_profile']->name)): ?>
                  <li>
                    <a
                     href="<?php echo $user_data['field_academics_profiles']['field_url']['url']; ?>"
                     class="icono <?php echo $user_data['field_academics_profiles']['field_academic_profile']->field_css_class['und'][0]['value']; ?>"
                     target="_blank"
                    >
                      <?php echo $user_data['field_academics_profiles']['field_academic_profile']->name; ?>
                    </a>
                  </li>
                <?php endif; ?>
              </ul>
            <?php else: ?>
              <ul class="list-inline sub-list-style-simple ordered-items prf-academicos">
                <?php
                  foreach ($user_data['field_academics_profiles'] as $key => $perfil) {
                    $wg =
                      db_select('taxonomy_term_data', 't')
                      ->fields('t', array('weight'))
                      ->condition('tid', $perfil['field_academic_profile']->tid)
                      ->execute()
                      ->fetchField()
                    ;
                    $class =
                      db_select('field_data_field_css_class', 'c')
                      ->fields('c', array('field_css_class_value'))
                      ->condition('entity_id', $perfil['field_academic_profile']->tid)
                      ->execute()
                      ->fetchField()
                    ;
                    $perfiles[$wg] = array(
                      'titulo' => $perfil['field_academic_profile']->name,
                      'url' => $perfil['field_url']['url'],
                      'clase' => $class,
                    );
                  }
                  ksort($perfiles);
                  dpm($perfiles);
                  $ver_mas = NULL;
                  foreach ($perfiles as $key => $val) {
                    if ($key > 6) {
                      $class = ' hidden';
                      $ver_mas = '<a href="#" class="ver-prf">Ver todos</a>';
                    }
                    else {
                      $class = ' normal';
                    }
                    $profiles_array[] =
                      '<li class="item-' . $key . $class . '">' .
                        '<a' .
                        ' href="' . $val['url'] . '"' .
                        ' class="icono ' . $val['clase'] . '"' .
                        ' target="_blank"' .
                        '>' .
                          ' ' . $val['titulo'] .
                        '</a>' .
                      '</li>'
                    ;
                  }

                  $items = array();
                  foreach ($profiles_array as $key => $value) {
                    if (!empty($value)) {
                      $items[] = $value;
                    }
                  }
                  echo implode(' ', $items);
                  echo $ver_mas;
                ?>
              </ul>
            <?php endif; ?>
          </div>
        <?php endif; ?>
        <!-- END Perfiles academicos -->

        <?php
        // if (isset($user_data['field_scopus_author_author_id'])) {
        //   $author_id = $user_data['field_scopus_author_author_id'];
        //   $api_key = '933e9e90b2adcb997611146810dbbeb0';
        //   $url = url(
        //     'https://api.elsevier.com/content/author/author_id/' . $author_id,
        //     array(
        //       'query' => array(
        //         'view' => 'METRICS',
        //         'apiKey' => $api_key,
        //         'httpAccept' => 'application/json'
        //       )
        //     )
        //   );
        //   $request = drupal_http_request($url);
        //   if (property_exists($request, 'data')) {
        //     $response = drupal_json_decode($request->data);
        //     if (!empty($response['author-retrieval-response'])) {
        //       echo
        //         '<div class="scopus-box document-count">' .
        //           '<strong>Scopus</strong>' .
        //           ' &gt; ' .
        //           '<strong>' . t("Documents") . ':</strong>' .
        //           ' ' .
        //           $response['author-retrieval-response'][0]['coredata']['document-count'] .
        //           ' | ' .
        //           '<strong>' . t("Citations") . ':</strong>' .
        //           ' ' .
        //           $response['author-retrieval-response'][0]['coredata']['citation-count'] .
        //           ' ' .
        //           t("total citations by") .
        //           ' ' .
        //           $response['author-retrieval-response'][0]['coredata']['cited-by-count'] .
        //           ' ' .
        //           t('documents') .
        //           ' | ' .
        //           '<strong>' . t("h-index") . ':</strong>' .
        //           ' ' .
        //           $response['author-retrieval-response'][0]['h-index'] .
        //           ' | ' .
        //           '<strong>' . t("Co-authors") . ':</strong>' .
        //           ' ' .
        //           $response['author-retrieval-response'][0]['coauthor-count'] .
        //         '</div>'
        //       ;
        //     }
        //   }
        // }
        ?>

        <strong><?php echo t('Institutional affiliation'); ?>:</strong>
        <div class="filiacion">
        <?php if(__maybe_show_the_field('field_position', $user_data['uid']) && (isset($user_data['field_position']))): ?>
          <span class="cargo"><?php echo $user_data['field_position']; ?></span> -
        <?php endif; ?>
        <?php if ($show_the_field_dependency): ?>
          <span class="dependencia"><?php echo $user_data['field_dependency']; ?></span>
        <?php endif; ?>
        </div>
        <div class="ciudad">
          <span>
            <?php echo $user_data['field_city']; ?>
          </span>
        </div>
      </div>
    <?php endif; ?>
  </div>
  <div class="col-lg-12 bottom-data">
    <strong><?php echo t('Profile'); ?>:</strong>
    <?php if($language->language == 'es'): ?>
      <p><?php echo decode_entities($user_data['field_perfil']); ?></p>
    <?php else: ?>
      <p><?php echo decode_entities($user_data['field_perfil_ingles']); ?></p>
    <?php endif; ?>
  </div>

  <div class="col-lg-12 user-rgister-data">
          <?php $user_load = user_load($user_data['uid']) ?>
          <div class="col-lg-3">Puntaje Acomulado General: 
            <span class="text-red">
              <?php echo $user_load->field_acumulado_general['und'][0]['value'] ?> 
            </span>
          </div>
          <div class="col-lg-3">Puntaje Académico: 
            <span class="text-red">
              <?php echo $user_load->field_puntaje_acumulado['und'][0]['value'] ?> 
            </span>
          </div>
          <div class="col-lg-3">Puntaje BR: 
            <span class="text-red">
              <?php echo $user_load->field_puntaje_br[LANGUAGE_NONE][0]['value'] ?> 
            </span>
          </div>
          <div class="col-lg-3">Escalafón Actual: 
            <span class="text-red">
              <?php echo $user_load->field_usr_escalafon['und'][0]['tid'] ?> 
            </span>
          </div>

          <div class="col-lg-3">Fecha de Ingreso al Banco: 
            <br>
            <span class="text-red"> 
              <?php echo str_replace('- 0:00','',format_date($user_load->field_date_admission['und'][0]['value'], 'profile_investigator')) ?> 
            </span>
          </div>
          <div class="col-lg-3">Fecha Último Puntaje: 
            <br>
            <span class="text-red"> 
              <?php echo str_replace('- 0:00','',format_date($user_load->field_date_last_score['und'][0]['value'],'profile_investigator')) ?> 
            </span>
          </div>
          <div class="col-lg-3">Fecha Penúltimo Puntaje
            <br>
            <span class="text-red"> 
              <?php echo str_replace('- 0:00','',format_date($user_load->field_fecha_penultimo_puntaje['und'][0]['value'],'profile_investigator')) ?> 
            </span>
          </div>
  </div>
</div>
