
#include "ofMain.h"
#include "ofUnibaLogoA.h"
#include "ofAppGlutWindow.h"
#include "UnibaLogoAppDefinition.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    int width,height;
#ifdef LOGO_MODE_PROJECTION
    width = 1280;
    height = 800;
#else
    width = 900;
    height = 900;
#endif
    ofSetupOpenGL(&window, width,height, OF_WINDOW);
	ofRunApp( new ofUnibaLogoA());

}
