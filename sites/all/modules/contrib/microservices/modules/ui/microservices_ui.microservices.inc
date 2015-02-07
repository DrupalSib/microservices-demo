<?php
/**
 * @file
 */

/**
 * Implements hook_microservices_info().
 */
function microservices_ui_microservices_info() {
  return array(
    'ui' => array(
      'title' => t('UI'),
      'bind events' => array(
        'manager activity',
      ),
    ),
  );
}

/**
 * Implements hook_microservices_event().
 */
function microservices_ui_microservices_event($message) {
  if ($message->event == 'manager activity') {
    $info = microservices_info();
    if (!empty($info['services'])) {
      $output_div = '<div class="divRow even">';
      foreach ($info['services'] as $machine_name => $service ) {
        $header_class = str_replace(' ', '-', $machine_name);
        $data = ' - ';
        $sender = '';
        if ($message->params->recipient === $machine_name) {
          switch ($message->params->type) {
            case 'action':
              $prefix = 'ACT';
              break;

            case 'event':
              $prefix = 'EVNT';
              break;

            case 'result':
              $prefix = 'RSLT';
              $sender = "{$message->params->sender} /";
              break;
          }
          $data = "$prefix: $sender {$message->params->name}";
        }
        $output_div .= '<div class="divCell ' . $header_class . '">' . $data . '</div>';
      }
      $output_div .= '</div>';
    }

    $commands[] = ajax_command_after('#start-point', $output_div);
    $message = (object) array(
      'channel' => MICROSERVICES_LOG,
      'commands' => $commands,
      'callback' => 'microservices_ui_dashboard_js_callback',
    );
    nodejs_send_content_channel_message($message);
  }
  else {
    throw new Exception('Unexpected event');
  }
}
