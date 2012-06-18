//
//  ofUnibaLogoA.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//
#pragma once

#include "ofMain.h"
#include "ParticleNode2.h"
#include "ofxSyphon.h"

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
    bool ofUnibaLogoA::CalcIntersectionPoint( const ofVec2f& pointA, const ofVec2f& pointB, const ofVec2f& pointC, const ofVec2f& pointD, ofVec2f& pointIntersection );
    
private:
    int globalCounter;
    ofCamera camera;
    vector<ofNode> logoNode;
    vector<ParticleNode2> logoBillbordNode;
    ofPolyline logoPolyArray;
    ofLight light;
    int currentColorIndex;
    
#ifndef LOGO_MODE_PROJECTION
    //background divide vertexes
    ofVec2f dividePoint[4];
    ofVec2f divideCrossPoint;
    ofColor divideRectColors[4];
#endif
    
    //camera transtion
    float friction;
    float spring;
    ofVec3f speed;
    ofVec3f curCamPos;
    ofVec3f nextCamPos;
    
    //backgroundImage
    ofImage mask;
    //Syphone Server
    ofxSyphonServer mainOutputSyphonServer;
};