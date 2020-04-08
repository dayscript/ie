<?php

/**
 * Implementa el menú de usuario con opciones específicas basadas en roles

  Roles:
  3:  administrator
  4:  Investigador
  5:  tecnico
  7:  adminitrador de grupo
  10: caie
  11: Admin GT

 */
function theme_banrep_user_top_zone($variables) {

  global $user, $language;
  $output = '';
  $item_redemption = "";
  $item_discount = '';

  $menu_investigador = "";
  $menu_admin_gt;

  
  if($user->uid > 0) {

    $user_info = user_load($user->uid);
    $route = isset($user_info->field_ruta['und'][0]['target_id']) ? $user_info->field_ruta['und'][0]['target_id'] : 0;
    $scale = isset($user_info->field_usr_escalafon[LANGUAGE_NONE][0]['tid']) ? $user_info->field_usr_escalafon[LANGUAGE_NONE][0]['tid'] : 0;
    if ($route == 15321 || $scale == 21243) {
      $item_redemption = '
      <li>
         <a href="/' . $language->language . '/profile/redemption/add">
         <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Redemption') .' </a>
      </li>';

    }

    $profile_url = "";
    if(isset($user_info->picture->uri) && file_exists($user_info->picture->uri)){
        $uri = $user_info->picture->uri;
        $style_name = '140x140';
        $profile_url = image_style_url($style_name, $uri);
    }else{
      $profile_url = get_default_profile_image();
    }

    $full_name = '';
    if(isset($user_info->field_full_name['und'][0]['value'])){
      $full_name = $user_info->field_full_name['und'][0]['value'];
    }

    $aditional_options = '';

    if(user_has_role(ADMIN_GRUPO_RID)){
      if(isset($user_info->field_research_group['und'][0]['tid']) && $user_info->field_research_group['und'][0]['tid'] > 0){
          $aditional_options .= '<li>
                                  <a href="/' . $language->language . '/profile/group/'.$user_info->field_research_group['und'][0]['tid'].'/edit">
                                    <i class="fa fa-cog" aria-hidden="true"></i> '. t('Manage Group') .'
                                  </a>
                                </li>';
      }
    }
    
    /**
    * 
    */
    if(user_has_role(3) || user_has_role(11) || user_has_role(10) ){
        $item_discount = '
        <li>
          <a href="/' . $language->language . '/profile/discount/add">
          <i class="fa fa-plus" aria-hidden="true"></i> '. t('Descuento por cambio de cargo') .' </a>
        </li>';
    }



    /**
     * Opciones Admin GT
     */
    if ( user_has_role(11) ) {
      $menu_admin_gt = '
                        <li>
                          <a href="/' . $language->language . '/admin/content/publicaciones-por-usuario">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Publicaciones por usuario') .' </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/content/gestion-actividad">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Gestionar Actividad
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/content/pub_usuariov">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Publicación por usuario
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/aprobacion-formacion">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Aprobación Formación
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/aprobacion-beneficio">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Aprobación Solicitud PPI
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/aprobacion-cambio-cargo">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Aprobación Descuento Cambio cargo
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/gestion-ascensos">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Gestión de Ascenso
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/content/gestion-ppi">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Gestión de PPI
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/people/gestionar-investigadores">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Gestionar investigadores
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/admin/aprobados-para-cambio-de-cargo">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Aprobado para cambio de cargo
                          </a>
                        </li>
                        <li>
                          <a href="/'.$language->language.'/admin/people/reporte-investigadores-por-puntos">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Listado control (tbd)
                          </a>
                        </li>
                        <li>
                          <a href="/' . $language->language . '/content/solicitudes-generales">
                          <i class="fa fa-angle-right" aria-hidden="true"></i> Solicitudes al CAIE
                          </a>
                        </li>';
    }

    /**
     * Opciones Investigador y Técnico
     */
     if ( user_has_role(4) || user_has_role(5) || user_has_role(10) ) {


      /**
      * Validación de usuario con rol de Investigador y escalafón 654 para habilitar la opción de Solicitud de beneficios PPI.
      */
      if(user_has_role(4) && taxonomy_term_load($user_info->field_usr_escalafon['und'][0]['tid'])->name == "654" ){
      $beneficios_ppi = '<li>
                          <a href="/' . $language->language . '/profile/redemption/add">
                          <i class="fa fa-plus" aria-hidden="true"></i> '. t('Solicitar Beneficios PPI') .' </a>
                        </li>';
      }



      $menu_investigador = '<li>
                             <a href="/' . $language->language . '/dashboard">
                             <i class="fa fa-bars" aria-hidden="true"></i> '. t('Dashboard') .' </a>
                          </li>
                          <li>
                             <a href="/' . $language->language . '/profile/'. $user->uid .'">
                             <i class="fa fa-user" aria-hidden="true"></i> '. t('Profile') .' </a>
                          </li>
                          <li>
                             <a href="/' . $language->language . '/profile/publications/add">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Publication') .' </a>
                          </li>
                          <li>
                             <a href="/' . $language->language . '/profile/activities/add">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Activity') .' </a>
                          </li>
                          <li>
                             <a href="/' . $language->language . '/profile/training/add">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Training') .' </a>
                          </li>' .
                          $item_discount .
                          $aditional_options .
                          '<li>
                             <a href="http://wdeppc1d:8080/sgee-proyectos/">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Project Management') .' </a>
                          </li>
                          <li>
                             <a href="http://repositorio.banrep.gov.co/">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Publish in Repository') .' </a>
                          </li>
                          <li>
                             <a href="/' . $language->language . '/content/solicitudes-generales">
                             <i class="fa fa-plus" aria-hidden="true"></i> '. t('Solicitudes al CAIE') .' </a>
                          </li>' . 
                          //$beneficios_ppi .
                          $item_redemption;
    }


    /**
     * Opciones CAIE
     */
     if ( user_has_role(10) ) {
//admin/content/publicaciones-por-usuario
      $menu_caie = '
                    <li>
                      <a href="/' . $language->language . '/admin/content/publicaciones-por-usuario">
                      <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Publicaciones por usuario') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/content/gestion-actividad">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Gestionar Actividad') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/content/pub_usuariov">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Publicación por usuario') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/aprobacion-formacion">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Aprobación Formación') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/aprobacion-beneficio">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Aprobación Solicitud PPI') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/aprobacion-cambio-cargo">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Aprobación Descuento Cambio cargo') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/gestion-ascensos">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Gestión de Ascenso') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/content/gestion-ppi">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Gestión de PPI') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/people/gestionar-investigadores">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Gestionar investigadores') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/content/gestionar-publicaciones">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Gestionar publicaciones') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/admin/aprobados-para-cambio-de-cargo">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Aprobado para cambio de cargo') .' </a>
                    </li>
                    <li>
                       <a href="/'.$language->language.'/admin/people/reporte-investigadores-por-puntos">
                       <i class="fa fa-angle-right" aria-hidden="true"></i> '. t('Listado control (tbd)') .' </a>
                    </li>';
    }



    /**
     * Construcción de las opciones del menú
     */
    
    $output = '<li class="dropdown dropdown-user">
                 <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown" data-close-others="true">
                    <span class="username username-hide-on-mobile"> '.$full_name.' </span>
                    <img alt="" class="img-circle" src="'.$profile_url.'">
                    <i class="fa fa-angle-down"></i>
                 </a>
                 <ul class="dropdown-menu dropdown-menu-default">';

    $output .= $menu_investigador;
    $output .= $menu_admin_gt;
    $output .= $menu_caie;

    $output .=  '<li>
                   <a href="/' . $language->language . '/user/logout">
                   <i class="fa fa-sign-out" aria-hidden="true"></i> '. t('Log out') .' </a>
                </li>
              </ul>
            </li>';

/*
    $output .= '<li class="dropdown dropdown-user">
                 <a href="#" class="dropdown-toggle" data-toggle="dropdown" data-hover="dropdown" data-close-others="true">
                    <span class="username username-hide-on-mobile"> '.$full_name.' </span>
                    <img alt="" class="img-circle" src="'.$profile_url.'">
                    <i class="fa fa-angle-down"></i>
                 </a>
                 <ul class="dropdown-menu dropdown-menu-default">
                    <li>
                       <a href="/' . $language->language . '/dashboard">
                       <i class="fa fa-bars" aria-hidden="true"></i> '. t('Dashboard') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/profile/'. $user->uid .'">
                       <i class="fa fa-user" aria-hidden="true"></i> '. t('Profile') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/profile/publications/add">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Publication') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/profile/activities/add">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Activity') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/profile/training/add">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Add Training') .' </a>
                    </li>';
        $output .= $item_discount;
        $output .=  $item_redemption . ' ' . $aditional_options . '
                    <li>
                       <a href="http://wdeppc1d:8080/sgee-proyectos/">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Project Management') .' </a>
                    </li>
                    <li>
                       <a href="http://repositorio.banrep.gov.co/">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Publish in Repository') .' </a>
                    </li>
                    <li>
                       <a href="/' . $language->language . '/content/solicitudes-generales">
                       <i class="fa fa-plus" aria-hidden="true"></i> '. t('Solicitudes al CAIE') .' </a>
                    </li>';
        $output .= $beneficios_ppi;
        $output .= $menu_admin_gt . '
                    <li>
                       <a href="/' . $language->language . '/user/logout">
                       <i class="fa fa-sign-out" aria-hidden="true"></i> '. t('Log out') .' </a>
                    </li>
                 </ul>
              </li>';

*/
  
  } // End if($user->uid > 0)
  else {
    $output = '<a href="#" class="btn-login open-login">' . t('Login as Research') . '</a>';
    $output .= '<a href="#" class="btn-login close-login hidden">' . t('Login as Research') . '</a>';
  }

  return $output;
}






function theme_home_dspace_block($variables) {
  $output = '<div class="articles ds-one">
  <div class="article clearfix">
    <div class="image-thumb">
      <img src="/sites/all/themes/custom/banrep/images/home-dspace.jpg" alt="">
    </div>
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <p class="lead">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</p>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <span class="date">09/10/2016</span>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <span class="date">09/10/2016</span>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <span class="date">09/10/2016</span>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <span class="date">09/10/2016</span>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
</div>';

  return $output;
}

function theme_home_koha_block($variables) {
  $output = '<div class="articles ds-two">
  <div class="article clearfix">
    <div class="image-thumb">
      <img src="/sites/all/themes/custom/banrep/images/home-koha1.jpg" alt="">
    </div>
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <p class="lead">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</p>
    </div>
  </div>
  <div class="article clearfix">
    <div class="image-thumb">
      <img src="/sites/all/themes/custom/banrep/images/home-koha2.jpg" alt="">
    </div>
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <p class="lead">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</p>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
  <div class="article clearfix">
    <div class="information">
      <h3 class="title">Lorem Ipsum es simplemente el texto de relleno de las imprentas y archivos</h3>
      <a href="#" title="" class="link-more"><i class="ico ico-plus"></i></a>
    </div>
  </div>
</div>';

  return $output;
}

function theme_home_most_views_block($variables) {
  $output = '';

  return $output;
}
