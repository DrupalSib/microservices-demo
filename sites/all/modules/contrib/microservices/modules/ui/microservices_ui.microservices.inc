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
      'title' => t('User interface'),
      'bind events' => array(
        MICROSERVICES_MANAGER . ' ' . MICROSERVICES_QUEUE_REQUEST,
        MICROSERVICES_MANAGER . ' ' . MICROSERVICES_QUEUE_REPLY,
      ),
    ),
  );
}

/**
 * Implements hook_microservices_event().
 */
function microservices_ui_microservices_event($log) {
  drush_print(drupal_json_encode($log));
  $commands[] = ajax_command_before('#micro-db tr:eq(1)', drupal_json_encode($log));
  $message = (object) array(
    'channel' => MICROSERVICES_LOG,
    'commands' => $commands,
    'callback' => 'microservices_ui_dashboard_js_callback',
  );
  nodejs_send_content_channel_message($message);
}
