<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_info().
 */
function microservices_cron_microservices_info() {
  return array(
    MICROSERVICES_CRON => array(
      'events' => array(
        'cron',
      ),
    ),
  );
}

/*
 * Implements hook_microservices_cron_info().
 */
function microservices_cron_microservices_cron_info() {
  return array(
    'yearly' => '0 0 1 1 *',
    'annually' => '0 0 1 1 *',
    'monthly' => '0 0 1 * *',
    'weekly' => '0 0 * * 0',
    'daily' => '0 0 * * *',
    'hourly' => '0 * * * *',
  );
}
