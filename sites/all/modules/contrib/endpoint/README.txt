File: <docroot>/.htaccess
==========================================
# Rewrite API callback URLs of the form api.php?q=x.
RewriteCond %{REQUEST_URI} ^\/?api\/.*
RewriteRule ^(.*)$ api.php?q=$1 [L,QSA]
RewriteCond %{QUERY_STRING} (^|&)q=(\/)?(\/)?api\/.*
RewriteRule .* api.php [L]


File: <docroot>/api.php
==========================================
<?php
/**
 * @file
 */

define('DRUPAL_ROOT', getcwd());
require_once 'sites/all/modules/custom/my_module/includes/endpoint.inc';


File: <docroot>/api.php
==========================================
<?php
/**
 * @file
 */

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/sites/all/modules/contrib/endpoint/includes/router.inc';

$routes = array(
  'api/v1/foos' => array(
    'GET' => array(
      'callback' => 'my_module_foo_list',
    ),
    'POST' => array(
      'callback' => 'my_module_foo_create',
      'authorized'  => TRUE,
    ),
  ),
  'api/v1/foo/(\w+)' => array(
    'GET' => array(
      'callback' => 'my_module_foo_get',
    ),
    'POST' => array(
      'callback' => 'my_module_foo_update',
      'include' => DRUPAL_ROOT . '/sites/all/modules/custom/another_module/includes/some_callback.inc',
      'authorized'  => TRUE,
    ),
  ),
);

endpoint_route(array(
  'debug' => TRUE,
  'routes' => $routes,
));

function my_module_foo_get($foo_name) {
  return "Hello $foo_name";
}
