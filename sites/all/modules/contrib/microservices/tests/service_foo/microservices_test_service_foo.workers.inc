<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_workers_info().
 */
function microservices_test_service_foo_microservices_workers_info() {
  return array(
    'foo-worker' => array(
      'title' => t('Foo test worker'),
      'services' => array(
        MICROSERVICES_MANAGER,
        MICROSERVICES_CRON,
        MICROSERVICES_BATCH,
        'foo',
        'bar',
      ),
    ),
  );
}
