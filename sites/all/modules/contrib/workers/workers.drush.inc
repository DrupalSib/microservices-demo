<?php
/**
 * @file
 */

/**
 * Implements hook_drush_command().
 */
function workers_drush_command() {
  return array(
    'workers' => array(
      'arguments' => array(
        'name' => 'Worker name.',
        'callback' => 'drush_workers',
      ),
    ),
  );
}

/**
 * @param $name
 */
function drush_workers($name) {
  workers_execute($name);
}
