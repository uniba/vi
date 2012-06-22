//
//  ofUnibaLogoA.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxUI.h"
#include "ofxUnibaLogo.h"

class ofUnibaLogoA : public ofSimpleApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased (int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void changeColorVariation();
    void exit(); 
    void guiEvent(ofxUIEventArgs &e);
    
private:
    ofxUnibaLogo unibaLogo; //ofxUnibaLogo object
    ofImage gradientMask; //backgroundImage
    ofxUICanvas *gui; //UI object
    ofxSyphonServer mainOutputSyphonServer; //Syphone Server
};