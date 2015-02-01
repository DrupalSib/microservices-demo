<?php
/**
 * @file
 */

/**
 * Implements hook_workers_info().
 */
function microservices_cron_workers_info() {
  return array(
    MICROSERVICES_CRON => array(
      'title' => t('Microservices cron worker'),
      'actions' => array(
        'cron tick' => array(
          'callback' => 'microservices_cron_tick',
        ),
      ),
    ),
  );
}

/**
 * @return bool
 */
function microservices_cron_tick() {
  static $time;

  if (!isset($time)) {
    $time = new DateTime('now');
  }
  elseif ((time() - $time->getTimestamp()) < 60) {
    return FALSE;
  }

  $time->setTimestamp(time());
  $expressions = array();
  foreach (microservices_cron_info() as $name => $expression) {
    $cron = Cron\CronExpression::factory($expression);
    if ($cron->isDue($time)) {
      $expressions[$name] = $expression;
    }
  }
  if ($expressions) {
    microservices_send_event(
      'cron',
      array(
        'time' => $time->getTimestamp(),
        'date' => $time->format('Y-m-d H:i:s'),
        'expressions' => $expressions
      )
    );
  }

  return TRUE;
}
