
/*!
 * jQuery Processing - A tiny Processing.js utility build on jQuery.
 *
 * @dependency jQuery v1.7+
 * @dependency Processing.js v1.4+
 * @author Uniba Inc.
 * @license MIT License.
 */

/**
 * Check processing existance.
 */

if (!window.Processing) {
  throw new Error("Processing is not found.");
}

/**
 * Disable processing auto-load mechanism.
 */

Processing.disableInit();

/**
 * Plugin.
 */

(function($, Processing) {

  /**
   * No operation.
   */

  var noop = function() {};

  /**
   * Plugin implementation.
   *
   * @param {Object} options
   * @return {Array}
   */
  
  var plugin = function(options) {

    var options = options || {};

    /**
     * Process each canvas.
     */

    return $(this).each(function() {
      var self = this
        , deferred = $.Deferred()
        , $this = $(this)
        , path = getSketchFilePath(this);

      /**
       * Store deferred object to data attr.
       *
       * $('canvas').data('p5-deferred')
       *   .fail(function(err) { console.log('fail callback'); })
       *   .done(function(sketch, insatnce) { console.log('done callback'); });
       */

      $this.data('p5-deferred', deferred);

      ajax(path, function(err, source) {
        var sketch, instance;

        /**
         * Exit and reject deferred on error.
         */

        if (err) {
          return deferred.reject(err);
        }

        /**
         * Compile and generate Sketch instance.
         */

        sketch = new Processing.compile(source);

        /**
         * Set callbacks.
         */

        sketch.onSetup = $.proxy(options.onSetup || noop, self);
        sketch.onLoop = $.proxy(options.onLoop || noop, self);
        sketch.onExit = $.proxy(options.onExit || noop, self);
        sketch.onLoad = $.proxy(options.onLoad || noop, self);
        sketch.onPause = $.proxy(options.onPause || noop, self);
        sketch.onFrameStart = $.proxy(options.onFrameStart || noop, self);
        sketch.onFrameEnd = $.proxy(options.onFrameEnd || noop, self);

        /**
         * Start rendering.
         */

        instance = new Processing(self, sketch);

        /**
         * Resolve deferred.
         */

        deferred.resolve(sketch, instance);

        /**
         * Store sketch and instance to data attr.
         */

        $this.data('p5-sketch', sketch).data('p5-instance', instance);
      });
    });
  };
  
  /**
   * Set plugin version.
   */

  plugin.version = '0.1.0';

  /**
   * Register as jQuery plugin.
   */

  $.fn.processing = plugin;
  
  /**
   * Detect sketch file path from given canvas element.
   *
   * @param {HTMLCanvas} canvas
   * @param
   */

  function getSketchFilePath(canvas) {
    return canvas.getAttribute('data-processing-sources')
      || canvas.getAttribute('data-src')
      || canvas.getAttribute('datasrc');
  }

  /**
   * Load file using xhr.
   *
   * @param {String} url
   * @param {Function} callback
   */

  function ajax(url, callback) {
    var err
      , xhr = new XMLHttpRequest();

    xhr.onreadystatechange = function() {
      if (4 === xhr.readyState) {
        if (xhr.status !== 200 && xhr.status !== 0) {
          err = new Error('Invalid xhr status: ' + xhr.status);
        }
        callback(err, xhr.responseText);
      }
    };

    xhr.open('GET', url, true);
    xhr.overrideMimeType && xhr.overrideMimeType('text/plain');
    xhr.setRequestHeader('If-Modified-Since', 'Fri, 01 Jan 1960 00:00:00 GMT');
    xhr.send(null);
  }

})(jQuery, Processing);
