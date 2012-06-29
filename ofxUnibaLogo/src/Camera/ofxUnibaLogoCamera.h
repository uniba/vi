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
#include "ofxUnibaLogoAnimation.h"
#include "ofxUnibaLogoGeom.h"

typedef enum{
    CametraPanningModeSlow = 0,
    CametraPanningModeFast = 1
} CametraPanningMode;

class ofxUnibaLogoCamera : public virtual ofCamera {

private:
    float friction; //camera transtion
    float spring;
    ofVec3f curCamPos;
    ofVec3f nextCamPos;
    int panRythm;
    ofxUnibaLogoGeom logoGeom;

public:
    CametraPanningMode mode;
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
        panRythm = 20;
    };
    
    void update( int globalCounter ){
        
        switch ( mode ) {
            case CametraPanningModeSlow:
                panRythm = 50;
                break;
            case CametraPanningModeFast:
                panRythm = 20;
                break;
            default:
                break;
        }
        
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
        
        if( 0 == globalCounter % panRythm ){
            if( 0 == floor( ofRandom( 2 ) ) ){
                if( 0 == floor( ofRandom( 3 ) ) ){
#ifdef TARGET_OF_IPHONE
                    nextCamPos.x = ( ofRandom( 1 ) - 2 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.y = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
#else
                    nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
#endif
                    switch ( mode ) {
                        case CametraPanningModeSlow:
                            friction = ofRandom( 0.3 ) + 0.14;
                            spring = 0.85 + ofRandom( 0.24 );
                            break;
                        case CametraPanningModeFast:
                            friction = ofRandom( 0.3 ) + 0.2;
                            spring = 0.5 + ofRandom( 0.4 );
                            break;
                        default:
                            break;
                    }
                }
            } else {
#ifdef TARGET_OF_IPHONE
                nextCamPos.x = ( ofRandom( 1 ) - 2 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.y = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
#else
                nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
#endif
                
                switch ( mode ) {
                    case CametraPanningModeSlow:
                        friction = ofRandom( 0.125 );
                        spring = 0.75 + ofRandom( 0.0125 );
                        break;
                    case CametraPanningModeFast:
                        friction = ofRandom( 0.25 );
                        spring = 0.75 + ofRandom( 0.05 );
                        break;
                    default:
                        break;
                }
                
                
            }
        }
        
        setGlobalPosition( curCamPos.x,curCamPos.y,curCamPos.z );
        lookAt( ofVec3f( 0, 0, 0 ) );

    };
    
};


#endif
