<?php
/**
 * @file
 */

/**
 * Implements hook_workers_info().
 */
function microservices_ui_workers_info() {
  return array(
    'ui-worker' => array(
      'title' => t('ui test worker'),
      'services' => array(
        'ui',
      ),
    ),
  );
}
