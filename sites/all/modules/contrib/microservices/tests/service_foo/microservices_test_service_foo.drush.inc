<?php
/**
 * @file
 */

/**
 * Implements hook_drush_command().
 */
function microservices_test_service_foo_drush_command() {
  return array(
    'foo-create-bar' => array(
      'callback' => 'drush_foo_create_bar',
    ),
    'foo-create-bars' => array(
      'callback' => 'drush_foo_create_bars',
    ),
    'foo-send-wake-up-event' => array(
      'callback' => 'drush_foo_send_wake_up_event',
    ),
  );
}

function drush_foo_create_bar() {
  microservices_send_action('bar', 'create', array('a' => '100500'), 'foo', array('some context' => 18500));
}

function drush_foo_send_wake_up_event() {
  microservices_send_event('wake up', 'Stand up and fight!');
}

function drush_foo_create_bars() {
  $context = array('process' => 'It is all about money');
  $params = array(
    'step 1' => array(
      'type' => MICROSERVICES_MESSAGE_ACTION,
      'service' => 'bar',
      'action' => 'create',
      'params' => array('a' => '100500'),
    ),
    'step 2' => array(
      'type' => MICROSERVICES_MESSAGE_ACTION,
      'service' => 'bar',
      'action' => 'create',
      'params' => array('a' => '100600'),
      'wait' => TRUE,
      'context' => array('nid' => 812),
    ),
    'final' => array(
      'type' => MICROSERVICES_MESSAGE_EVENT,
      'service' => 'bar',
      'event' => 'wake up',
      'params' => 'Stand up and fight!',
    ),
  );

  microservices_send_action(
    MICROSERVICES_BATCH,
    'execute',
    $params,
    'foo',
    $context
  );

//  $message = new stdClass();
//  $message->type = MICROSERVICES_MESSAGE_ACTION;
//  $message->recipient = MICROSERVICES_BATCH_MANAGER;
//  $message->action = 'execute';
//  $message->params = $params;
//  $message->sender = 'foo';
//  $message->context = $context;
//  microservices_batch_create(json_decode(json_encode($message)));
}
