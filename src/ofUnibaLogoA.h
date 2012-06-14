//
//  ofUnibaLogoA.h
//  Codern
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
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
    
private:
    ofCamera camera;
    vector<ofNode> logoNode;
    vector<ParticleNode2> logoBillbordNode;
    ofPolyline logoPolyArray;
    ofLight light;
    
    //camera transtion
    float friction;
    float spring;
    ofVec3f speed;
    ofVec3f curCamPos;
    ofVec3f nextCamPos;
    
    //Syphone Server
    ofxSyphonServer mainOutputSyphonServer;
};
