<?php

function microservices_ui_preprocess(&$variables) {
  $header = array();
  foreach ($variables['info']['services'] as $service ) {
    $header[] = key($service);
  }
  $variables['header'] = $header;
  $a = 4;
}
