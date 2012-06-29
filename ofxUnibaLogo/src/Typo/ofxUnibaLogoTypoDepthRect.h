//
//  ofxUnibaLogoTypoDepthRect.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoTypoDepthRect_h
#define UnibaMotionLogo_ofxUnibaLogoTypoDepthRect_h
#include "ofxUnibaLogoTypo.h"
#include "ofxUnibaLogoGeom.h"
#include "ofxUnibaLogoTypoDepthRectFaceElement.h"

class ofxUnibaLogoTypoDepthRect : public virtual ofxUnibaLogoTypo {

private:
    ofxUnibaLogoGeom logoGeom;
    vector<ofxUnibaLogoTypoDepthRectFaceElement> logoBillbordNode;

public:
    void setup(){
        ofxUnibaLogoTypo::setup();
        //--------- object vertex setting ------------
        for ( int j = 0; j < logoGeom.length; j++ ){
            ofVec3f startVec;
            if( 1 <= j ){
                ofxUnibaLogoTypoDepthRectFaceElement nodeObject;
                nodeObject.mID = j - 1;
                nodeObject.colorPatternIndex = currentColorIndex;
                
                startVec = logoGeom.getStartPoint(j);
                
                nodeObject.startPoint = startVec;
                nodeObject.endPoint = endPoints[j];
                logoBillbordNode.push_back( nodeObject );
                logoBillbordNode[ j - 1 ].setup();
            }
        }
    };
    
    void update( int globalCounter ) {
        for ( int i = 0; i < logoGeom.length - 1; i++ ){
            logoBillbordNode[i].update();
        }
        
        if( 0 == globalCounter % 50 ){
            if( 0 == floor( ofRandom( 4 ) ) ){
                if( 0 == floor( ofRandom( 3 ) ) ){
                    for( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                        int matterREctNum = floor( ofRandom( logoGeom.length ) );
                        if( typeFacelLength >= 20 ) logoBillbordNode[ matterREctNum ].startSpring = true;
                    }
                }
            } else {
                for ( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                    int matterREctNum = floor( ofRandom( logoGeom.length ) );
                    if( typeFacelLength >= 20 ) logoBillbordNode[ matterREctNum ].startSpring = true;
                }
            }
        }
        
        typeFacelLength += 0.15;
        if( typeFacelLength > 20 ){
            typeFacelLength = 20;
        }
    };
    
    void draw() {
        //------ draw logo lines width rectangle -----
        ofPushMatrix();
        ofRotateX( 180 );
        for (int i = 0; i < logoGeom.length - 1; i++ ){
            ofPushMatrix();
            ofFill();
            logoBillbordNode[i].draw();
            ofPopMatrix();
        }
        ofPopMatrix();
    };
    
    void setHue( float hue ){
        for( int i = 0; i < logoGeom.length; i++ ){
            logoBillbordNode[i].hue = hue;
            logoBillbordNode[i].isChangeHue = true;
        }
    };
    
    void changeColorVariation( int currentColorIndex ){
        typeFacelLength = 0;
        for ( int i = 0; i< logoGeom.length; i++ ){
            logoBillbordNode[i].startSpring  = false;
            logoBillbordNode[i].count = 0;
            logoBillbordNode[i].rectWidth = 0;
            logoBillbordNode[i].colorPatternIndex = currentColorIndex;
            logoBillbordNode[i].isChangeColors = true;
        }
    }
};


#endif
