(function ($) {
  Drupal.behaviors.showHideColumns = {
    attach: function (context, settings) {
      $('input[type=checkbox]').each(function (item) {
        $(this).click(function() {
          if ($(this).attr('checked')) {
            $(' .' + $(this).data('type')).hide();
          }
          else {
            $(' .' + $(this).data('type')).show();
          }
        });
      });
    }
  }
}(jQuery));
