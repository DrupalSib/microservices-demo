<?php

/**
 * Implements template_preprocess_microservices_logs.
 * @param $variables
 */
function microservices_ui_preprocess_microservices_logs(&$variables) {
  if (!empty($variables['info'])) {
    if (!empty($variables['info']['services'])) {
      $variables['div_header_dashboard'] = '<div class="headRow">';
      foreach ($variables['info']['services'] as $machine_name => $service ) {
        $header_class = str_replace(' ', '-', $machine_name);
        $main_header_dashboard[] = '<input type="checkbox" data-type="' . $header_class . '"> </input>' . $service['title'];

        $variables['div_header_dashboard'] .= '<div class="divCell ' . $header_class . '">'. $service['title'] . '</div>';
      }
      $variables['main_header_dashboard'] = theme(
        'item_list',
        array(
          'items' => $main_header_dashboard,
          'title' => 'Settings'
        )
      );
      $variables['div_header_dashboard'] .= '</div>';
    }
  }
}
