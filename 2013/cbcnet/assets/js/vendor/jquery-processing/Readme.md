# jquery-processing

  A tiny Processing.js utility built on jQuery.

## Installation

```html
<script src="jquery-1.8.0.js"></script>
<script src="processing-1.4.1.js"></script>
<script src="jquery-processing.js"></script>
```

Notes: Put jquery-processing after Processing.js.

## Usage

Put canvas tag and set pde file path to data attribute.

```html
<canvas data-processing-sources="/path/to/sketch.pde"></canvas>
```

Initialize canvas with jQuery synopsis.

```javascript
jQuery(function($) {
  $('canvas').processing({
      onSetup: function() {
        // callback after setup()
        
        // Get Processing instances
        var p5 = $(this).data('p5-instance')
          , sketch = $(this).data('p5-sketch');
      }
    , onFrameStart: function() {
        // callback before draw()
      }
    , onFrameEnd: function() {
        // callback after draw()
      }
    , onPause: function() {
        // callback on loop is paused
      }
    , onLoop: function() {
        // callback on loop is resumed or started
      }
  });
});
```

## Authors

  - Seiya Konno &lt;seiya@uniba.jp&gt; ([nulltask](https://github.com/nulltask))

## License

(The MIT License)

Copyright (c) 2012 Uniba Inc. &lt;info@uniba.jp&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
