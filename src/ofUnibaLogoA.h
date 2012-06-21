//
//  ofUnibaLogoA.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#include "ofMain.h"
#include "ParticleNode2.h"
#include "ofxSyphon.h"
#include "UnibaLogoAppDefinition.h"
#include "ofxUI.h"

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
    bool calcIntersectionPoint( const ofVec2f& pointA, const ofVec2f& pointB, const ofVec2f& pointC, const ofVec2f& pointD, ofVec2f& pointIntersection );
    void changeColorVariation();
    void exit(); 
    void guiEvent(ofxUIEventArgs &e);
    
private:
    int globalCounter;
    ofCamera camera;
    vector<ofNode> logoLineNode;
    vector<ParticleNode2> logoBillbordNode;
    ofPolyline logoPolyArray;
    ofLight light;
    int currentColorIndex;
    float hue;
    
#ifdef LOGO_MODE_DIVIDED_BACKGROUND
    ofVec2f dividePoint[4];  //background divide vertexes
    ofVec2f divideCrossPoint;
    ofColor divideRectColors[4];
    float divideRectColorHues[4];
#endif
    
    float friction; //camera transtion
    float spring;
    ofVec3f speed;
    ofVec3f curCamPos;
    ofVec3f nextCamPos;
    
    ofImage gradientMask; //backgroundImage

    ofxUICanvas *gui; //UI object
    
    ofxSyphonServer mainOutputSyphonServer; //Syphone Server
};