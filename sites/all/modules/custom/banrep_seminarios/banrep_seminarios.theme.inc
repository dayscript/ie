<?php

function theme_sem_hm_list($variables){
  $events = $variables['events'];
  $output = '<h2 class="block__title">'.t('Events').'</h2>';
  $output .= '<div class="hm-events">';
  foreach ($events as $key => $event) {
    $date = strtotime($event['date']);
    $day = format_date($date, 'custom', 'd');
    $month = format_date($date, 'custom', 'M');
    $fecha = format_date($date, 'custom', 'd/m/Y');
    $date_range = ($event['date_end']) ?  ' - De '.$event['date_ini'] . ' hasta '. $event['date_end'] : ' - ' . $event['date_ini'];
    $output .= '<div class="node-event view-mode-resumen_seminario">';
    $output .= '<div class="item-info clearfix">';
    $output .= '<div class="info-left"><span class="mes">'.$month.'</span><span class="dia">'.$day.'</span></div>';
    $output .= '<div class="info-right"><span class="date">' . $fecha . $date_range .'</span>';
    $output .= '<h1>' . l($event['title'], drupal_get_path_alias('node/' . $event['nid'])) . '</h1>';
    $output .= '<span class="city">' . $event['city'] . '</span>';
    $output .= '</div></div></div>';
  }
  $output .= '</div>';

  return $output;
}
