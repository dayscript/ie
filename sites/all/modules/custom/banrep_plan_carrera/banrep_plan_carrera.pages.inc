<?php

module_load_include('inc', 'banrep_plan_carrera', 'banrep_plan_carrera.functions');

function banrep_plan_carrera_page ($uid){


   $usuario = user_load($uid);
   if(!isset($usuario->uid) || $usuario->uid <= 0 ){
      return 'No existe plan de carrera';
   }

   $route        = $usuario->field_ruta['und'][0]['target_id'];
   $scale        = $usuario->field_usr_escalafon['und'][0]['tid'];
   $requirements = get_requirements($scale,$route);
   $form         = drupal_get_form('banrep_plan_carrera_form',$requirements,$uid);

    $name = 'profile_info_order_'.$uid;
    $profile_info_order = variable_get($name, FALSE);
    if($uid == $user->uid){
        $show_edit = TRUE;
    }     $user_data = get_current_user_data($uid);
    $field_full_name = isset($user_data['field_full_name']) ? $user_data['field_full_name'] : '';
   $user_data['only_personal_information'] = TRUE;
    drupal_add_library('system', 'ui.sortable');
    drupal_add_library('system', 'ui.tabs');
    drupal_add_library('system', 'ui.accordion');
    drupal_add_js(drupal_get_path('module', 'banrep_core') . '/js/profile.js');
    $content = theme('banrep_core_profile', array('user_data' => $user_data, 'profile_info_order' => $profile_info_order));

   $html = $content;
   $html         .= drupal_render($form);


   return $html;



}


function banrep_plan_carrera_form($form, &$form_state, $requirements=array(),$uid){
      $form = array();

      $form['rq_tiempo'] = array(
           '#type'=>'fieldset',
           '#title' => t('Requisitos de tiempo'),
           '#tree' => true
      );

      $tipo_tiempo = list_allowed_values(field_info_field('field_pcr_tipo_tiempo'));

      foreach ($requirements['time'] as $key => $value) {
         $form['rq_tiempo'][$key] = array(
            '#type' => 'container',
            '#attributes' => array('class'=>array('row'))
          );
          $info_user = _get_time_user($uid,$key);
          $form['rq_tiempo'][$key]['rule'] = array(
              '#markup'=>'<span class="col-md-6">'.$tipo_tiempo[$key].' '.$value. ' ('.$info_user.')</span>',
            );

          $checked = 0;

          if ($info_user >= $value ){
              $checked = 1;
          }
          $form['rq_tiempo'][$key]['aprobado'] = array(
              '#type'  => 'checkbox',
              '#title' => 'Aprobado',
              '#default_value' => $checked,
              '#prefix' => '<div class="col-md-6 col-xs-12"><div class="col-xs-12">',
              '#suffix' => '</div>',
            );
          $form['rq_tiempo'][$key]['comment'] = array(
              '#type'  => 'textarea',
              '#title' => 'Comentario',
              '#prefix' => '<div class="col-xs-12 hidden">',
              '#suffix' => '</div></div>',
            );

      }

      $form['rq_publiacion'] = array(
           '#type'=>'fieldset',
           '#title' => t('Requisitos de publiación'),
           '#tree'=> true
      );

      foreach ($requirements['publications'] as $keyg => $group) {
              $prefix = '';
              if(isset($group['operator']) && !empty($group['operator'])){
                 $prefix ='<div class="operator-groups-conditions"><span>'.$group['operator'].'</span></div>';
              }
              $form['rq_publiacion'][$keyg] = array(
                '#type' => 'container',
                '#attributes' => array('class'=>array('group-requirements-publications')),
                '#prefix' => $prefix,
              );

            foreach ($group['conditions'] as $keyc => $condition) {
              $form['rq_publiacion'][$keyg][$keyc] = array(
                '#type' => 'container',
                '#attributes' => array('class'=>array('row'))
              );

              $operator = '';
              if(isset($condition['operator']) && !empty($condition['operator'])){
                  $operator = $condition['operator'].' ';
              }

              switch ($condition['type']) {
                case 'PUNTAJE':
                      $description = 'Puntaje en publicaciones:'.$condition['value'].' (1)';
                  break;
                case 'CANTIDAD':
                      if (isset($condition['serie'])){
                         $name = node_load($condition['serie']);
                         $name = $name->title;
                      }
                      else {
                         if (isset($condition['concept'])){
                            $name = _get_concept_publications($condition['concept']);
                         }
                      }
                      $description = $operator.$condition['value'].' '.$name.' (1)';
                  break;
              }

              $form['rq_publiacion'][$keyg][$keyc]['rule'] = array(
                  '#markup'=>'<span class="col-md-6">'.$description.' <b> no cumple</b></span>',
                );
              $form['rq_publiacion'][$keyg][$keyc]['aprobado'] = array(
                  '#type'  => 'checkbox',
                  '#title' => 'Aprobado',
                  '#default_value' => 1,
                  '#prefix' => '<div class="col-md-6 col-xs-12"><div class="col-xs-12">',
                  '#suffix' => '</div>',
              );
          $form['rq_publiacion'][$keyg][$keyc]['comment'] = array(
              '#type'  => 'textarea',
              '#title' => 'Comentario',
              '#prefix' => '<div class="col-xs-12 hidden">',
              '#suffix' => '</div></div>',


            );



            }
      }

      $form['rq_formacion'] = array(
           '#type'=>'fieldset',
           '#title' => t('Requisitos formación desarrollo y desempeño'),
           '#tree'=>true,
      );

      foreach ($requirements['training'] as $keyg => $group) {
              $prefix = '';
              if(isset($group['operator']) && !empty($group['operator']) && !is_null($group['operator'])){
                 $prefix ='<div class="operator-groups-conditions"><span>'.$group['operator'].'</span></div>';
              }
              $form['rq_formacion'][$keyg] = array(
                '#type' => 'container',
                '#attributes' => array('class'=>array('group-requirements-publications')),
                '#prefix' => $prefix,
              );
            $flag_first_condition = TRUE;
            foreach ($group as $keyc => $condition) {
              if ($keyc == 'operator'){
                 continue;
              }
              $form['rq_formacion'][$keyg][$keyc] = array(
                '#type' => 'container',
                '#attributes' => array('class'=>array('row'))
              );

              if ($flag_first_condition){
                  $operator = '';
                  $flag_first_condition = FALSE;
              }
              else {
                 $operator = 'Y ';
              }
              $name = _get_concept_publications($condition);

              $form['rq_formacion'][$keyg][$keyc]['rule'] = array(
                  '#markup'=>'<span class="col-md-6">'.$operator.$name.' <b> no cumple</b></span>',
                );
              $form['rq_formacion'][$keyg][$keyc]['aprobado'] = array(
                  '#type'  => 'checkbox',
                  '#title' => 'Aprobado',
                  '#default_value' => 1,
                  '#prefix' => '<div class="col-md-6 col-xs-12"><div class="col-xs-12">',
                  '#suffix' => '</div>',
              );

          $form['rq_formacion'][$keyg][$keyc]['comment'] = array(
              '#type'  => 'textarea',
              '#title' => 'Comentario',
              '#prefix' => '<div class="col-xs-12 hidden">',
              '#suffix' => '</div></div>',
            );


            }
      }

      return $form;
}


