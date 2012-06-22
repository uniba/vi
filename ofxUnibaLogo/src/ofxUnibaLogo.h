//
//  ofxh
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
#include "ofxUnibaLogoTypo.h"
#include "ofxUnibaLogoGeom.h"

class ofxUnibaLogo {
    
private:
        ofCamera camera;
        ofxUnibaLogoColor logoColor;
        ofxUnibaLogoGeom logoGeom;
    
        
    
    public:
    #ifdef LOGO_MODE_DIVIDED_BACKGROUND
        ofVec2f dividePoint[4];  //background divide vertexes
        ofVec2f divideCrossPoint;
        ofColor divideRectColors[4];
        float divideRectColorHues[4];
    #endif
    
        vector<ofNode> logoLineNode;
        vector<ofxUnibaLogoTypo> logoBillbordNode;
        int currentColorIndex;
        float hue;
    
        float friction; //camera transtion
        float spring;
        ofVec3f speed;
        ofVec3f curCamPos;
        ofVec3f nextCamPos;
        bool isAnimationAuto;
    
        float typeFacelLength;
        int globalCounter;
    
        void setup(){
            globalCounter = 0;
            typeFacelLength = 0;
            isAnimationAuto = true;
            //--------- camera setting -------------------
            camera.setFov( 45.0 );
            camera.setFarClip( 24.0f );
            camera.setNearClip( 0.1f );
            camera.setPosition( 0, 0, 10.0f );
            
            nextCamPos.x,nextCamPos.y,nextCamPos.z = 0;
            curCamPos.x,curCamPos.y,curCamPos.z = 0;
            friction = 0.03;
            spring = 0.05;
            
            //--------- set color array ------------------
            
            currentColorIndex = floor( ofRandom(logoColor.lengthOfCollorArray) - 1 );
            
    #ifdef LOGO_MODE_DIVIDED_BACKGROUND
            //caliculate background divider
            for ( int i = 0; i < 4; i++ ){
                float angle = ofRandom( 90 ) + ( 90 * i );
                float radius = ofGetWidth() / sqrt( 2.0 );
                ofVec2f calVect = ofVec2f( radius / sqrt( 2.0 ), radius / sqrt( 2.0 ) );
                calVect.rotate(angle);
                calVect += ofVec2f ( ofGetWidth() / 2, ofGetHeight() / 2 );
                dividePoint[i] = calVect;
                int colorMatter = ofRandom( 4 );
                divideRectColors[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatter ];
                divideRectColorHues[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatter ].getHue();
            }
            ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[ 0 ], dividePoint[ 2 ], dividePoint[ 1 ], dividePoint[ 3 ], divideCrossPoint );
    #endif
            
            int colorPatternIndexNum = floor( ofRandom( 7 ) - 1 );
            
            //--------- object vertex setting ------------
            for ( int j = 0; j < logoGeom.lengthOfArray; j++ ){
                ofNode aNode;
                
                ofVec3f vec;
                ofVec3f startVec;
                ofVec3f endVec;
                
                vec.x = logoGeom.logoVertexArray[ j ][ 0 ] / 100;
                vec.y = logoGeom.logoVertexArray[ j ][ 1 ] / 100;
                vec.z = logoGeom.logoVertexArray[ j ][ 2 ] / 100;
                
                ofVec3f orientation;
                
                if( 1 <= j ){
                    ofxUnibaLogoTypo nodeObject;
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
                
                aNode.setPosition( vec );     
                logoLineNode.push_back( aNode );
            }
        };
    
    void update(){
        for ( int i = 0; i < logoGeom.lengthOfArray - 1; i++ ){
            logoBillbordNode[i].update();
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
        
        
        for( int i = 0; i< 4; i++ ){
            dividePoint[i].x += speed.x * 30;
            dividePoint[i].y += speed.y * 30;
        }
        
        
         ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );    //cmamera animation
        
        if( 0 == globalCounter % 50 ){
            if( 0 == floor( ofRandom( 4 ) ) ){
                if( 0 == floor( ofRandom( 3 ) ) ){
                    nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                    friction = ofRandom( 0.3 ) + 0.14;
                    spring = 0.85 + ofRandom( 0.24 );
                    for( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                        int matterREctNum = floor( ofRandom( logoGeom.lengthOfArray ) );
                        if( typeFacelLength >= 20 ) logoBillbordNode[ matterREctNum ].startSpring = true;
                    }
                }
            } else {
                nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                friction = ofRandom( 0.125 );
                spring = 0.75 + ofRandom( 0.0125 );
                for ( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                    int matterREctNum = floor( ofRandom( logoGeom.lengthOfArray ) );
                    if( typeFacelLength >= 20 ) logoBillbordNode[ matterREctNum ].startSpring = true;
                }
            }
        }
        
        camera.setGlobalPosition(curCamPos.x,curCamPos.y,curCamPos.z);
        camera.lookAt( ofVec3f( 0, 0, 0 ) );
        
        if ( isAnimationAuto ){
            globalCounter++;
        }
        typeFacelLength += 0.15;
        if( typeFacelLength > 20){
            typeFacelLength = 20;
        }
        if( globalCounter > 1000 ){
            globalCounter = 0;
        }
    };
    
    void draw(){
        //-------- draw divided background ---------
#ifdef LOGO_MODE_DIVIDED_BACKGROUND
        glDisable(GL_DEPTH_TEST);
        for ( int i = 0; i < 4; i++ ){
            ofColor colCarrent = divideRectColors[i];
            colCarrent = ofColor( colCarrent.r, colCarrent.g, colCarrent.b, 220 );
            ofSetColor( colCarrent );
            ofBeginShape();
            if( 3 == i ){
                ofVertex( dividePoint[i].x, dividePoint[i].y );
                ofVertex( divideCrossPoint.x, divideCrossPoint.y );
                ofVertex( dividePoint[0].x, dividePoint[0].y );
            } else {
                ofVertex( dividePoint[i].x, dividePoint[i].y );
                ofVertex( divideCrossPoint.x, divideCrossPoint.y );
                ofVertex( dividePoint[i + 1].x, dividePoint[i + 1].y );
            }
            switch (i){
                case 0:
                    ofVertex( 0, ofGetHeight() );
                    break;
                case 1:
                    ofVertex( 0, 0 );
                    break;
                case 2:
                    ofVertex( ofGetWidth(), 0);
                    break;
                case 3:
                    ofVertex( ofGetWidth(), ofGetHeight() );
                    break;
            }
            ofEndShape();
        }
        glEnable(GL_DEPTH_TEST);
#endif
        
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
        ofPushMatrix();
        ofRotateX( 180 );
            ofSetColor( 0, 0, 0 );
            for ( int i = 1; i < logoGeom.lengthOfArray; i++ ){
                ofPushMatrix();
                    float nextPosX =  logoLineNode[ i - 1 ].getPosition().x - (logoLineNode[ i - 1 ].getPosition().x- logoLineNode[i].getPosition().x) * (typeFacelLength * 0.05);
                    float nextPosY =  logoLineNode[ i - 1 ].getPosition().y - (logoLineNode[ i - 1 ].getPosition().y- logoLineNode[i].getPosition().y) * (typeFacelLength * 0.05);
                    ofLine( logoLineNode[ i - 1 ].getPosition().x, logoLineNode[ i - 1 ].getPosition().y, logoLineNode[ i - 1 ].getPosition().z,
                           nextPosX, nextPosY , logoLineNode[i].getPosition().z );
                ofPopMatrix();
            }
        ofPopMatrix();
        
        //------ draw logo lines width rectangle -----
        ofPushMatrix();
        ofRotateX( 180 );
        for (int i = 0; i < logoGeom.lengthOfArray - 1; i++ ){
            ofPushMatrix();
            ofFill();
            logoBillbordNode[i].draw();
            ofPopMatrix();
        }
        ofPopMatrix();
        ofPopMatrix();
        camera.end();
    
    };
    
    void setHue( float hue ){
        for( int i = 0; i < logoGeom.lengthOfArray; i++ ){
            logoBillbordNode[i].hue = hue;
            logoBillbordNode[i].isChangeHue = true;
        }
        for( int i = 0; i < 4; i++ ){
            float currentHue = divideRectColorHues[i];
            currentHue = currentHue + hue;
            if( 255 < currentHue )currentHue = currentHue - 256;
            if( 60 < divideRectColors[i].getBrightness() ){
                divideRectColors[i].setHue( currentHue );
            }
        }
    };
    
    void changeColorVariation(){
        int width = ofGetWidth();
        int height = ofGetHeight();
        currentColorIndex = floor(ofRandom( 6 )) ;
        
        for ( int i = 0; i < 4; i++ ){
            float angle = ofRandom( 90 ) + ( 90 * i );
            float radius = ofGetWidth() / sqrt(2.0) * 3;
            ofVec2f calVect = ofVec2f( radius / sqrt(2.0), radius / sqrt(2.0) );
            calVect.rotate( angle );
            calVect += ofVec2f ( width / 2, height / 2 );
            dividePoint[i] = calVect;
            
            int colorMatterFordivider = ofRandom( 4 ) ;
            divideRectColors[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatterFordivider ];
            divideRectColorHues[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatterFordivider ].getHue();
        }
        ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );
        
        for ( int i = 0; i< logoGeom.lengthOfArray; i++ ){
            logoBillbordNode[i].startSpring  = false;
            logoBillbordNode[i].count = 0;
            logoBillbordNode[i].rectWidth = 0;
            logoBillbordNode[i].colorPatternIndex = currentColorIndex;
            logoBillbordNode[i].isChangeColors = true;
        }
        typeFacelLength = 0;
    };
};

#endif
