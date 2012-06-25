//
//  ofxUnibaLogoTypo.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#ifndef UnibaMotionLogo_OFXUnibaLogoTypo_h
#define UnibaMotionLogo_OFXUnibaLogoTypo_h
#include "ofMain.h"
#include "ofxUnibaLogoColor.h"
#include "ofxUnibaLogoGeom.h"
class ofxUnibaLogoTypo : public ofNode {

public:
<<<<<<< HEAD
    
    int currentColorIndex;
    float typeFacelLength;
    vector<ofVec3f> endPoints;
    ofxUnibaLogoGeom logoGeom;
    
    void setup(){
        typeFacelLength = 0;
        for ( int i = 0; i < logoGeom.length; i++ ){
            endPoints.push_back( logoGeom.getEndPoint( i ) );
        }
    }
    
    
=======
    int currentColorIndex;
    float typeFacelLength;
>>>>>>> colorなどのリファクタリング
};

#endif