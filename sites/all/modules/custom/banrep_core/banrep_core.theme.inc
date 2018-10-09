<?php

function theme_banrep_user_top_zone($variables) {
  global $user, $language;
  $output = '';
  $item_redemption = "";
  if($user->uid > 0) {
    $user_info = user_load($user->uid);
    $route = isset($user_info->field_ruta['und'][0]['target_id']) ? $user_info->field_ruta['und'][0]['target_id'] : 0;
    if ($route == 15321) {
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
          $aditional_options .= '<li><a href="/' . $language->language . '/profile/group/'.$user_info->field_research_group['und'][0]['tid'].'/edit"><i class="fa fa-cog" aria-hidden="true"></i> '. t('Manage Group') .' </a></li>';
      }
    }

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
                    </li>
                    '. $item_redemption .'
                    ' . $aditional_options . '
                    <li>
                       <a href="/' . $language->language . '/user/logout">
                       <i class="fa fa-sign-out" aria-hidden="true"></i> '. t('Log out') .' </a>
                    </li>
                 </ul>
              </li>';
  }
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
