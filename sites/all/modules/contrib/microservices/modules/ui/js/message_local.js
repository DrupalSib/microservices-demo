(function($){
  Drupal.behaviors.message_local = {
    attach: function (context, settings) {

      console.log('Trying to connect: ' + Drupal.settings.server + ':8080');
      var socket = io.connect(Drupal.settings.server + ':8080');

      socket.on('connect', function () {
        console.log('connected');
      });

      socket.on('reconnect', function () {
        console.log('reconnect');
      });

      socket.on('reconnecting', function () {
        console.log('reconnecting');
      });

      socket.on('microservices_ui_dashboard_info', function (message) {
        console.log(message);
      });

      socket.on('error', function (e) {
        console.log('System', e ? e : 'A unknown error occurred');
      });

      $(document).ready(function() {

        /*
        socket.emit('nickname', '<?php print $username ?>', function (nick) {
          if (nick != 'me') {
            myNick = nick;
            return $('#chat').addClass('nickname-set');
          }
        });
        */

      });
    }
  }
})(jQuery);