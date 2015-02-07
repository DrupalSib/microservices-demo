(function ($) {
  Drupal.behaviors.showHideColumns = {
    attach: function (context, settings) {
      $('#ms-table.divTable').once(function() {
        $.each(Drupal.settings.microservices.default_excluded_options, function( index, value ) {
          $('#' + value).attr('checked', 'checked');
        });
        // Hide elements if checkboxes is checked.
        $('input[type=checkbox]').each(function (item) {
          if ($(this).attr('checked')) {
            $(' .' + $(this).data('type')).hide();
          }
        });
      });
      // Add click event for each checkbox.
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
  };
}(jQuery));
