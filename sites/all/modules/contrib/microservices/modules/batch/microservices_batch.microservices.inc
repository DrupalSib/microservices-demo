<?php
/**
 * @file
 */

/*
 * Implements hook_microservices_info().
 */
function microservices_batch_microservices_info() {
  return array(
    MICROSERVICES_BATCH => array(
      'title' => t('Batch'),
      'actions' => array(
        'execute',
      ),
    ),
  );
}

/*
 * Implements hook_microservices_action().
 */
function microservices_batch_microservices_action($message) {
  if ($message->action == 'execute') {
    microservices_batch_create($message);
  }
}

/*
 * Implements hook_microservices_result().
 */
function microservices_batch_microservices_result($message) {
  if (!empty($message->context->batch)) {
    microservices_batch_item_result($message->context->batch->item_id, $message);
    microservices_batch_process_begin($message->context->batch->id);
  }
}
