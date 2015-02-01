<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_info().
 */
function microservices_test_service_foo_microservices_info() {
  return array(
    'foo' => array(
      'events' => array(
        'wake up',
      ),
    ),
  );
}

/*
 * Implements hook_microservices_result().
 */
function microservices_test_service_foo_microservices_result($message) {
  $a = 1;
  $b = 2;
}
