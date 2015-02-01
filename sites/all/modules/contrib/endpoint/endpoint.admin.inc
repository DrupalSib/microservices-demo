<?php
/**
 * @file
 */

/**
 * Form callback for the js configuration form.
 */
function endpoint_configure_form($form, &$form_state) {
  $htaccess = '# Rewrite API callback URLs of the form api.php?q=x.' . PHP_EOL;
  $htaccess .= 'RewriteCond %{REQUEST_URI} ^\/?api\/.*' . PHP_EOL;
  $htaccess .= 'RewriteRule ^(.*)$ api.php?q=$1 [L,QSA]' . PHP_EOL;
  $htaccess .= 'RewriteCond %{QUERY_STRING} (^|&)q=(\/)?(\/)?api\/.*' . PHP_EOL;
  $htaccess .= 'RewriteRule .* api.php [L]';

  $form['htaccess'] = array(
    '#type'        => 'textarea',
    '#title'       => t('Add the following lines in front of the existing RewriteRules in your .htaccess.'),
    '#value'       => $htaccess,
  );

  return system_settings_form($form);
}
