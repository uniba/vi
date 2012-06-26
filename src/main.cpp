
#include "ofMain.h"
#include "ofUnibaLogoA.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    int width,height;
    width = 1280;
    height = 800;
//    width = 900;
//    height = 900;
    ofSetupOpenGL(&window, width,height, OF_WINDOW);
	ofRunApp( new ofUnibaLogoA());


}
