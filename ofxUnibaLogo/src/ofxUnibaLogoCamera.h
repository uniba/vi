//
//  ofxUnibaLogoCamera.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoCamera_h
#define UnibaMotionLogo_ofxUnibaLogoCamera_h
#include "ofMain.h"
#include "ofxUnibaLogoGeom.h"
#include "ofxUnibaLogoAnimation.h"

class ofxUnibaLogoCamera : public virtual ofCamera {

private:
    float friction; //camera transtion
    float spring;
    ofVec3f curCamPos;
    ofVec3f nextCamPos;

public:
    ofVec3f speed;
    void setup(){
        //--------- camera setting -------------------
        setFov( 45.0 );
        setFarClip( 24.0f );
        setNearClip( 0.1f );
        setPosition( 0, 0, 10.0f );
        
        nextCamPos.x,nextCamPos.y,nextCamPos.z = 0;
        curCamPos.x,curCamPos.y,curCamPos.z = 0;
        friction = 0.03;
        spring = 0.05;
    };
    
    void update( int globalCounter ){
        //cmamera animation
        float ax;
        ax = (nextCamPos.x - curCamPos.x) * spring;
        speed.x += ax;
        speed.x *= friction;
        curCamPos.x += speed.x;
        
        float ay;
        ay = (nextCamPos.y - curCamPos.y) * spring;
        speed.y += ay;
        speed.y *= friction;
        curCamPos.y += speed.y;
        
        float az;
        az = (nextCamPos.z - curCamPos.z) * spring;
        speed.z += az;
        speed.z *= friction;
        curCamPos.z += speed.z;
        
        //cmamera animation
        
        if( 0 == globalCounter % 50 ){
            if( 0 == floor( ofRandom( 4 ) ) ){
                if( 0 == floor( ofRandom( 3 ) ) ){
                    nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    friction = ofRandom( 0.3 ) + 0.14;
                    spring = 0.85 + ofRandom( 0.24 );
                }
            } else {
                nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                friction = ofRandom( 0.125 );
                spring = 0.75 + ofRandom( 0.0125 );
                
            }
        }
        
        setGlobalPosition(curCamPos.x,curCamPos.y,curCamPos.z);
        lookAt( ofVec3f( 0, 0, 0 ) );
    };
    
};


#endif
