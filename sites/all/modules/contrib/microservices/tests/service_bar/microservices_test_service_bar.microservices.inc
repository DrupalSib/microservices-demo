<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_info().
 */
function microservices_test_service_bar_microservices_info() {
  return array(
    'bar' => array(
      'title' => 'Bar',
      'actions' => array(
        'create',
      ),
      'bind events' => array(
        'wake up',
      ),
    ),
  );
}

/*
 * Implements hook_microservices_action().
 */
function microservices_test_service_bar_microservices_action($message) {
  $a = 1;
  $a = 2;
  microservices_send_result($message, 100500);
}

/*
 * Implements hook_microservices_event().
 */
function microservices_test_service_bar_microservices_event($message) {
  $a = 1;
  $a = 2;
}
