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
#include "ofxUnibaLogoColor.h"
#include "ofxUnibaLogoTypoDepthRectFaceElement.h"

class ofxUnibaLogoTypoDepthRect : public virtual ofxUnibaLogoTypo {

private:
    ofxUnibaLogoGeom logoGeom;
    vector<ofxUnibaLogoTypoDepthRectFaceElement> logoBillbordNode;

public:
    float typeFacelLength;
    int currentColorIndex;
    void setup( int currentColorIndex ){
        typeFacelLength = 0;
        //--------- object vertex setting ------------
        for ( int j = 0; j < logoGeom.length; j++ ){
            ofVec3f startVec;
            ofVec3f endVec;
            if( 1 <= j ){
                ofxUnibaLogoTypoDepthRectFaceElement nodeObject;
                nodeObject.mID = j - 1;
                nodeObject.colorPatternIndex = currentColorIndex;
                endVec.x = logoGeom.logoVertexArray[ j ][ 0 ] / 100;
                endVec.y = logoGeom.logoVertexArray[ j ][ 1 ] / 100;
                endVec.z = logoGeom.logoVertexArray[ j ][ 2 ] / 100;
                startVec.x = logoGeom.logoVertexArray[ j - 1 ][ 0 ] / 100;
                startVec.y = logoGeom.logoVertexArray[ j - 1 ][ 1 ] / 100;
                startVec.z = logoGeom.logoVertexArray[ j - 1 ][ 2 ] / 100;
                nodeObject.startPoint = startVec;
                nodeObject.endPoint = endVec;
                logoBillbordNode.push_back( nodeObject );
                logoBillbordNode[j-1].setup();
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
        if( typeFacelLength > 20){
            typeFacelLength = 20;
        }
    }
    
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
    }
    
    void setHue( float hue ){
        for( int i = 0; i < logoGeom.length; i++ ){
            logoBillbordNode[i].hue = hue;
            logoBillbordNode[i].isChangeHue = true;
        }
    }
    
    void changeColorVariation( int currentColorIndex ){
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
