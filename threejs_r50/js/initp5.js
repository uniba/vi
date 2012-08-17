/**
 * init p5
 * 
 * @dependency jQuery 1.6.2+
 * @dependency Processing.js 1.3.0+
 */

!function(window, document, $, undefined) {

  var p5
    , isiPad = navigator.userAgent.match(/iPad/i) != null
    , isiPhone = navigator.userAgent.indexOf('iPhone') != -1;
    
  /**
   * Expose callback function for Processing.js
   */
  
  window.processingInitComplete = function() {
    window.p5 = Processing.getInstanceById('p5container');
    $(window).resize();
  };
  
  $(function() {
  	$(window).bind("resize orientationchange", function(event) {
  		if (isiPad) {
  			//iPad用の処理
  			var windowWidth = $(window).width()/2;
  			if (Math.abs(window.orientation) === 90) {
  				//横向き
  				var windowWidth = $(window).width()/2;
  				var windowHeight = 374; //$(window).height();
  				var windowScale = 0.3;
  			} else {
  				//縦向き
  				var windowWidth = $(window).width()/2;
  				var windowHeight = 374; //$(window).height();
  				var windowScale = 0.3;
  			}
  		} else if (isiPhone) {
  			//iPhone用の処理
  			if (Math.abs(window.orientation) === 90) {
  				//横向き
  				var windowWidth = $(window).width()/4;
  				var windowHeight = 187; //$(window).height();
  				var windowScale = 0.25;
  			} else {
  				//縦向き
  				var windowWidth = $(window).width()/4;
  				var windowHeight = 187; //$(window).height();
  				var windowScale = 0.2;
  			}
  		} else {
  			//iPad, iPhone以外の処理
  			var windowWidth = $(window).width();
  			var windowHeight = $(window).height();
  			var windowScale = 1;
  		}	
  		
  		if (p5 && p5.setStageSize) {
  			p5.setStageSize(windowWidth, windowHeight, windowScale);
  		}
  	}).trigger("resize");
  });
  
}(window, document, jQuery);
