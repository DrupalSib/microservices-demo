<?php
/**
 * @file
 */

/**
 * @param array $config
 */
function endpoint_route($config) {
  endpoint_debug_time();
  endpoint_debug_memory();
  $result = NULL;
  $route = NULL;
  try {
    // Find a route.
    if (!isset($config['routes'])) {
      throw new Exception('Routes should be defined');
    }
    if (!$route = endpoint_match_route($config['routes'])) {
      throw new Exception('Route not found');
    }
    // Before execute.
    if (isset($config['before_execute_callback'])) {
      $config['before_execute_callback']($route);
    }
    // Execute.
    if (isset($config['execute_callback'])) {
      $result = $config['execute_callback']($route);
    }
    else {
      $result = endpoint_callback_execute($route);
    }
    // After execute.
    if (isset($config['after_execute_callback'])) {
      $config['after_execute_callback']($route, $result);
    }
  }
  catch (Exception $e) {
    if (isset($config['error_callback'])) {
      $result = $config['error_callback']($e, $route);
    }
    else {
      $result = endpoint_callback_error($e, $route);
    }
  }

  if (isset($config['delivery_callback'])) {
    print $config['delivery_callback']($result, $route, $config);
  }
  else {
    print endpoint_callback_delivery($result, $route, $config);
  }
}

/**
 * @param array $routes
 *
 * @return null
 */
function endpoint_match_route($routes) {
  foreach ($routes as $pattern => $methods) {
    foreach ($methods as $method => $info) {
      if (preg_match_all('#^' . $pattern . '$#', endpoint_request_path(), $matches, PREG_OFFSET_CAPTURE)) {
        $params = array();
        foreach (array_slice($matches, 1) as $match) {
          $params[$match[0][0]] = $match[0][1];
        }
        // Make a route array.
        $info['pattern'] = $pattern;
        $info['method'] = $method;
        $info['params'] = $params;

        return $info;
      }
    }
  }

  return NULL;
}

/**
 * @return mixed|\stdClass
 * @throws \Exception
 */
function endpoint_request_data() {
  static $static;

  if (!isset($static)) {
    if (isset($_SERVER['CONTENT_TYPE']) && (strpos($_SERVER['CONTENT_TYPE'], 'application/json') !== FALSE)) {
      $static = json_decode(file_get_contents('php://input'), FALSE);
      if (json_last_error()) {
        throw new Exception('Invalid data format');
      }
    }
    elseif (!empty($_POST['data'])) {
      $static = json_decode(urldecode($_POST['data']), FALSE);
      if (json_last_error()) {
        throw new Exception('Invalid data format');
      }
    }
    else {
      $static = new stdClass();
    }
  }

  return $static;
}

/**
 * @param array $route
 *
 * @return mixed
 * @throws \Exception
 */
function endpoint_callback_execute($route) {
  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
  require_once DRUPAL_ROOT . '/includes/common.inc';

  drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

  // Prevent Devel from hi-jacking our output in any case.
  $GLOBALS['devel_shutdown'] = FALSE;

  // Deactivate Drupal Error and Exception handling.
  restore_error_handler();
  restore_exception_handler();
  // Activate Endpoint error handler.
  set_error_handler('endpoint_error_handler');

  $bootstrap = isset($route['bootstrap']) ? $route['bootstrap'] : DRUPAL_BOOTSTRAP_DATABASE;
  if ($bootstrap < DRUPAL_BOOTSTRAP_FULL) {
    fix_gpc_magic();
  }

  if ($bootstrap > DRUPAL_BOOTSTRAP_DATABASE) {
    drupal_bootstrap($bootstrap);
  }

  if (!empty($route['authorized'])) {
    if (($bootstrap < DRUPAL_BOOTSTRAP_SESSION)) {
      require_once DRUPAL_ROOT . '/' . variable_get('session_inc', 'includes/session.inc');
      drupal_session_initialize();
    }
    if (!$GLOBALS['user']->uid) {
      throw new Exception('User should be authorized');
    }
  }

  require_once DRUPAL_ROOT . '/includes/unicode.inc';
  unicode_check();

  require_once DRUPAL_ROOT . '/includes/module.inc';
  require_once DRUPAL_ROOT . '/includes/file.inc';
  file_get_stream_wrappers();

  if (isset($route['include'])) {
    require_once $route['include'];
  }

  return call_user_func_array($route['callback'], !empty($route['params']) ? $route['params'] : array());
}

/**
 * @param $result
 * @param $route
 * @param $config
 *
 * @return string
 */
function endpoint_callback_delivery($result, $route, $config) {
  $json = array('result' => $result);
  if (!empty($config['debug'])) {
    $json['timer'] = endpoint_debug_time();
    $json['memory'] = endpoint_debug_memory();
  }
  $data = endpoint_request_data();
  if (isset($data->id) && is_int($data->id)) {
    $json['id'] = $data->id;
  }
  header('Content-Type: application/json');
  return json_encode($json, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
}

/**
 * @param \Exception $e
 * @param            $route
 *
 * @return array
 */
function endpoint_callback_error(Exception $e, $route) {
  return array(
    'error' => array(
      'message' => $e->getMessage(),
      'code' => $e->getCode(),
    ),
  );
}

/**
 * @param $error_level
 * @param $message
 * @param $filename
 * @param $line
 * @param $context
 *
 * @throws \Exception
 */
function endpoint_error_handler($error_level, $message, $filename, $line, $context) {
  if (defined('E_DEPRECATED') && ($error_level == E_DEPRECATED || $error_level == E_USER_DEPRECATED)) {
    return;
  }
  throw new Exception("Error (level $error_level): $message @ $filename:$line");
}

/**
 * @return float|int
 */
function endpoint_debug_time() {
  static $time = NULL;

  if (!$time) {
    $time = microtime(TRUE);
    return 0;
  }
  else {
    // Time diff in seconds.
    return round(microtime(TRUE) - $time, 3);
  }
}

/**
 * @return float|int
 */
function endpoint_debug_memory() {
  static $memory = NULL;

  if (!$memory) {
    $memory = memory_get_usage();
    return 0;
  }
  else {
    // Memory diff in Mb.
    return round((memory_get_usage() - $memory) / 1024 / 1024, 2);
  }
}

/**
 * Fork of request_path().
 */
function endpoint_request_path() {
  static $path;

  if (isset($path)) {
    return $path;
  }

  $path = '';
  if (isset($_GET['q']) && is_string($_GET['q'])) {
    $path = $_GET['q'];
  }
  elseif (isset($_SERVER['REQUEST_URI'])) {
    $request_path = strtok($_SERVER['REQUEST_URI'], '?');
    $base_path_len = strlen(rtrim(dirname($_SERVER['SCRIPT_NAME']), '\/'));
    $path = substr(urldecode($request_path), $base_path_len + 1);
    if ($path == basename($_SERVER['PHP_SELF'])) {
      $path = '';
    }
  }

  $path = trim($path, '/');

  return $path;
}
