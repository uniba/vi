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
    ofxUnibaLogoBackgroundDivision lagoBackgroundDvision;
<<<<<<< HEAD
    ofxUnibaLogoTypoLine logoTypoLine;
=======
    ofxUnibaLogoTypoLine logoTypeLine;
>>>>>>> colorなどのリファクタリング
    ofxUnibaLogoTypoDepthRect logoTypoDepthRecct;
    
public:
    int currentColorIndex;
    float hue;

    bool isAnimationAuto;
    bool drawLineType;
    
    float typeFacelLength;
    int globalCounter;

    void setup(){
        drawLineType = true;
        globalCounter = 0;
        typeFacelLength = 0;
        isAnimationAuto = true;
        
        camera.setup();
        //--------- set color array ------------------
        currentColorIndex = floor( ofRandom(logoColor.length) );
        
        //---------set background division -----------
        lagoBackgroundDvision.currentColorIndex = currentColorIndex;
        lagoBackgroundDvision.setup();
        
        int colorPatternIndexNum = floor( ofRandom(logoColor.length) );
        
        //---------setup logo depth rect --------------
        logoTypoDepthRecct.currentColorIndex = currentColorIndex;
        logoTypoDepthRecct.setup();
        
        //---------setup logo TYPO--------------------
        logoTypoLine.setup();
    };
    
    void update(){
<<<<<<< HEAD
        logoTypoLine.animationCounter = globalCounter;
=======
        
<<<<<<< HEAD
        logoTypoLine.typeFacelLength = typeFacelLength;
=======
        logoTypeLine.typeFacelLength = typeFacelLength;
        
>>>>>>> colorなどのリファクタリング
>>>>>>> colorなどのリファクタリング
        logoTypoDepthRecct.update( globalCounter );

        //---------update background division------------
        lagoBackgroundDvision.update( camera.speed );
        
        //----------------update camera------------------
        camera.update( globalCounter );
        
        if( typeFacelLength < 20 ){
            camera.mode = CametraPanningModeFast;
        } else {
            camera.mode = CametraPanningModeSlow;
        }
        
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
        lagoBackgroundDvision.draw();
        
        //------- begin camera & draw 3D space -------
        ofSetColor( 255, 255, 255, 255 );
        camera.begin();
            camera.lookAt( ofVec3f( 0, 0, 0 ) );
            if ( isAnimationAuto ){
#ifdef TARGET_OF_IPHONE
                ofRotate( -ofGetElapsedTimef() * 20, 1, 0, 0 );
#else
                ofRotate( ofGetElapsedTimef() * 20, 0, 1, 0 );
#endif
            }
#ifdef TARGET_OF_IPHONE
        ofRotateZ( 90 );
#endif
            ofPushMatrix();
                ofTranslate( -4.0f, 2.0f, 0.0f ); // translate objects to center
                ofSetColor( 0, 0, 0,255 );
                ofSetLineWidth( 1.25f );
                
                //------------ draw logo type lines ----------
<<<<<<< HEAD
                if( drawLineType ){
                    logoTypoLine.draw();
                }
=======
<<<<<<< HEAD
                logoTypoLine.draw();
=======
                logoTypeLine.draw();
>>>>>>> colorなどのリファクタリング
>>>>>>> colorなどのリファクタリング
                logoTypoDepthRecct.draw();
            
            ofPopMatrix();
        camera.end();
    };
    
    void setHue( float hue ){
        //-----set hue of background division---------
        lagoBackgroundDvision.setHue( hue );
        logoTypoDepthRecct.setHue( hue );
    };
    
    void changeColorVariation(){
        currentColorIndex = floor(ofRandom( logoColor.length )) ;
        
        //-----change colorvariation of background division----
        lagoBackgroundDvision.changeColorVariation( currentColorIndex );
        logoTypoDepthRecct.changeColorVariation( currentColorIndex );
        
        typeFacelLength = 0;
        logoTypoLine.resetAnimation();
        logoTypoDepthRecct.typeFacelLength = 0;
    };
};

#endif
