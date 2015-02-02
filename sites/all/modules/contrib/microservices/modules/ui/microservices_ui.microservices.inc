<?php
/**
 * @file
 */

/*
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

/*
 * Implements hook_microservices_event().
 */
function microservices_ui_microservices_event($message) {
  $a = 4;
  $a = 4;
}
