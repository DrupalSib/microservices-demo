<?php

/**
 * Implements template_preprocess_microservices_logs.
 * @param $variables
 */
function microservices_ui_preprocess_microservices_logs(&$variables) {
  if (!empty($variables['info'])) {
    $header = array();
    $rows = array();

    if (!empty($variables['info']['services'])) {
      foreach ($variables['info']['services'] as $service ) {
        $header[] = $service['title'];
        $rows['data'][] = '';
      }
    }

    $variables['table_dashboard'] = theme(
      'table',
      array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array(
          'sticky' => TRUE,
          'id' => 'micro-db'
        ),
      )
    );
  }
}
