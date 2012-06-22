//
//  ofxUnibaLogo.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//


#ifndef UnibaMotionLogo_UnibaLogo_h
#define UnibaMotionLogo_UnibaLogo_h

#define MAX_WORLD_CLIP 7
//use this define, window size will 1280x800 commentout size will 900x900　square.
#define LOGO_MODE_PROJECTION 

//use this define, background color separation will be ON.
#define LOGO_MODE_DIVIDED_BACKGROUND

#include "ofMain.h"
#include "ofxUnibaLogoAnimation.h"
#include "ofxUnibaLogoColor.h"
#include "ofxUnibaLogoGeom.h"
#include "ofxUnibaLogoTypoLine.h"
#include "ofxUnibaLogoTypoDepthRect.h"
#include "ofxUnibaLogoBackgroundDivision.h"
#include "ofxUnibaLogoCamera.h"

class ofxUnibaLogo {
    
private:
    ofxUnibaLogoCamera camera;
    ofxUnibaLogoColor logoColor;
    ofxUnibaLogoGeom logoGeom;
    ofxUnibaLogoBackgroundDivision lagoBackgrounddDvision;
    ofxUnibaLogoTypoLine logoTypeLine;
    ofxUnibaLogoTypoDepthRect logoTypoDepthRecct;
    
public:
    int currentColorIndex;
    float hue;

    bool isAnimationAuto;

    float typeFacelLength;
    int globalCounter;

    void setup(){
        globalCounter = 0;
        typeFacelLength = 0;
        isAnimationAuto = true;
        
        camera.setup();
        
        //--------- set color array ------------------
        currentColorIndex = floor( ofRandom(logoColor.length) - 1 );
        
        //---------set background division -----------
        lagoBackgrounddDvision.setup( currentColorIndex );
        
        int colorPatternIndexNum = floor( ofRandom( 7 ) - 1 );
        
        //---------setup logo depth rect --------------
        logoTypoDepthRecct.setup( currentColorIndex );
        
        //--------- object vertex setting ------------
        for ( int j = 0; j < logoGeom.length; j++ ){
            ofNode aNode;
            ofVec3f vec;
            vec.x = logoGeom.logoVertexArray[ j ][ 0 ] / 100;
            vec.y = logoGeom.logoVertexArray[ j ][ 1 ] / 100;
            vec.z = logoGeom.logoVertexArray[ j ][ 2 ] / 100;
            aNode.setPosition( vec );
            logoTypeLine.addNode( aNode );
        }
            
    };
    
    void update(){
        logoTypoDepthRecct.update( globalCounter );
        
        //---------update background division------------
        lagoBackgrounddDvision.update( camera.speed );
        
        camera.update( globalCounter );
        
        typeFacelLength += 0.15;
        if( typeFacelLength > 20){
            typeFacelLength = 20;
        }
        
        if ( isAnimationAuto ){
            globalCounter++;
        }
        
        if( globalCounter > 1000 ){
            globalCounter = 0;
        }
    };
    
    void draw(){
        //--------draw background division-----------
        lagoBackgrounddDvision.draw();
        
        //------- begin camera & draw 3D space -------
        ofSetColor( 255, 255, 255, 255 );
        camera.begin();
            camera.lookAt( ofVec3f( 0, 0, 0 ) );
            if ( isAnimationAuto ){
                ofRotate(ofGetElapsedTimef() * 20, 0, 1, 0 );
            }
            ofPushMatrix();
                ofTranslate( -4.0f, 2.0f, 0.0f ); // translate objects to center
                ofSetColor( 0, 0, 0,255 );
                ofSetLineWidth( 1.25f );
                
                //------------ draw logo type lines ----------
                logoTypeLine.draw( typeFacelLength );
                logoTypoDepthRecct.draw();
            
            ofPopMatrix();
        camera.end();
    };
    
    void setHue( float hue ){
        //-----set hue of background division---------
        lagoBackgrounddDvision.setHue( hue );
        logoTypoDepthRecct.setHue( hue );
    };
    
    void changeColorVariation(){
        int width = ofGetWidth();
        int height = ofGetHeight();
        currentColorIndex = floor(ofRandom( 6 )) ;
        
        //-----change colorvariation of background division----
        lagoBackgrounddDvision.changeColorVariation( currentColorIndex );
        logoTypoDepthRecct.changeColorVariation( currentColorIndex );
        
        typeFacelLength = 0;
    };
};

#endif
