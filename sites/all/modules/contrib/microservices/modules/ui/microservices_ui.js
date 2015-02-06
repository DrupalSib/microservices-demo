(function ($) {
  Drupal.Nodejs.callbacks.microservices_ui_dashboard_js_callback = {
    callback: function (message) {
      Drupal.nodejs_ajax.runCommands(message);
      $("#micro-db tr:even").removeClass('odd').addClass('even');
      $("#micro-db tr:odd").removeClass('even').addClass('odd');
    }
  };
}(jQuery));
