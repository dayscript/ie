<?php

/**
 * @file
 * Proporciona plantillas a bloques del CMS.
 */

/**
 * Plantilla bloque top user general.
 */
function theme_banrep_user_top_zone($variables) {
  global $user, $language;
  $output = '';
  if($user->uid > 0) {
    $user_info = user_load($user->uid);
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

/**
 * Plantilla bloque soluciones CAIE.
 */
function theme_caie_solutions($variables) {
  $items = $variables['items'];
  $output = '';
  $output .= '<div class="soluciones-caie"><div class="row"><div class="col-lg-3"><h2>' . t('SOLUTIONS') . '</h2></div> <div class="col-lg-9"><ul class="solution-items">';
  foreach ($items as $key => $item) {
      $c = $key+1;
      $iconclass = isset($item->field_icono_class['und'][0]['value'])?$item->field_icono_class['und'][0]['value']:'';
      $icon = '<span class="' . $iconclass . '"></span>';
      $url = url('taxonomy/term/' . $item->tid);
      $output .= '<li class="item-'.$c.'"> <a href="' . $url . '" title="'. $item->name .'">' . $icon . '<strong class="item-title">'. $item->name .'</strong></a></li>';
  }
  $output .= '</ul></div></div></div>';
  return $output;
}

/**
 * Plantilla bloque recursos CAIE.
 */
function theme_caie_resources($variables) {
    $items = $variables['items'];
    $output = '';
    $output .= '<div class="recursos"><div class="row"><div class="col-lg-12"><ul class="recursos-items">';
    foreach ($items as $key => $item) {
        $c = $key+1;
        $status_resources = FALSE;
        if(isset($item->status) && ($item->status == '1')){
            $status_resources = TRUE;
        }
        if($status_resources){
            $iconclass = isset($item->field_icono_class['und'][0]['value'])?$item->field_icono_class['und'][0]['value']:'';
            $icon = '<span class="' . $iconclass . '"></span>';
            if(isset($item->field_url_recurso['und'][0]['url'])){
                $url = $item->field_url_recurso['und'][0]['url'];
            }else{
                $url = url('taxonomy/term/' . $item->tid);
            }
            $output .= '<li class="item-'.$c.'"> <a href="' . $url . '" title="'. $item->name .'">' . $icon . '<strong class="item-title">'. $item->name .'</strong></a></li>';
        }
    }
    $output .= '</ul></div></div></div>';
    return $output;
}

/**
 * Plantilla bloque colaboradores CAIE.
 */
function theme_caie_collaborators($variables) {
    $items = $variables['items'];
    $output = '<div class="colaboradores"><ul>';
    foreach ($items as $key => $item) {
        $output .= '<li><div class="profile-image">'.theme('image_style', array('style_name' => 'user_picture_60x60', 'path' => $item->field_imagen['und'][0]['uri'])).'</div>';
        $output .= '<div class="user-info"><div class="full-name">'.$item->name.'</div>
        <div class="position">'.$item->description.'</div></div></li>';
    }
    $output .= '</ul><div class="contact-email"><a href="mailto:caie-soluciones@banrep.gov.co"><i class="fa fa-envelope" aria-hidden="true"></i> caie-soluciones@banrep.gov.co</a></div>';
    $output .= '</ul></div>';
    return $output;
}
