<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_cron_info().
 */
function hook_microservices_cron_info() {
  return array(
    'each15m' => '*/15 * * * *', // each 15 minutes
  );
}
