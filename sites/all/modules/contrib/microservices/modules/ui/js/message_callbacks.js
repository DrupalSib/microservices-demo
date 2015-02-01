Drupal.Nodejs.callbacks.microservices_ui_dashboard_js_callback = {
  callback: function (message) {
    if (message.callback == 'microservices_ui_dashboard_js_callback') {
      io.sockets.emit('users_count', message.data);
      //for (var i = 0, len = sockets.length; i < len; i++) {
      //  sockets[i].emit('microservices_ui_dashboard_info', message.data);
      //}
    }
  }
};