(function ($) {
  Drupal.Nodejs.callbacks.microservices_ui_dashboard_js_callback = {
    callback: function (message) {
      Drupal.nodejs_ajax.runCommands(message);
      $(".divRow:even").removeClass('odd').addClass('even');
      $(".divRow:odd").removeClass('even').addClass('odd');

      // Hide elements if checkboxes is checked.
      $('input[type=checkbox]').each(function (item) {
        if ($(this).attr('checked')) {
          $(' .' + $(this).data('type')).hide();
        }
      });

      if ($('.divRow').length > Drupal.settings.microservices.table_size) {
        $('.divRow').last().remove();
      }
    }
  };
}(jQuery));
