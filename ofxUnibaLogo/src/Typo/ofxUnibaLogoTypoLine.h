//
//  ofxUnibaLogoTypoLine.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#define MAX_RANDOM_START_POINT_NUM 5
#ifndef UnibaMotionLogo_ofxUnibaLogoTypoLine_h
#define UnibaMotionLogo_ofxUnibaLogoTypoLine_h
#include "ofxUnibaLogoTypo.h"
#include "ofxUnibaLogoGeom.h"
#include "ofxUnibaLogoTypoLineElement.h"

class ofxUnibaLogoTypoLine : public virtual ofxUnibaLogoTypo {
private:
    ofxUnibaLogoGeom logoGeom;
    vector<ofxUnibaLogoTypoLineElement> logoLineNode;
public:
    int animationStartId[ MAX_RANDOM_START_POINT_NUM ];
    int animationCounter;
    void setup() {
        ofxUnibaLogoTypo::setup();
        //--------- object vertex setting ------------
        for( int i = 0; i < logoGeom.length; i++ ){
            ofxUnibaLogoTypoLineElement aNode;
            aNode.setPosition( endPoints[i] );
            aNode.id = i;
            logoLineNode.push_back( aNode );
        };
        
        animationStartId[0] = 1;
        for(int i = 1; i < MAX_RANDOM_START_POINT_NUM; i++ ){
            animationStartId[ i ] = ofRandom( logoGeom.length );
        }
    };
    
    void draw() {
        for( int i = 0; i < MAX_RANDOM_START_POINT_NUM; i++ ){
            logoLineNode[ animationStartId[i] ].bang = true;
        }
        ofPushMatrix();
        ofRotateX( 180 );
        ofSetColor( 0, 0, 0 );
        for( int i = 1; i < logoGeom.length; i++ ){
            ofPushMatrix();
                logoLineNode[i].draw();
                ofVec3f currentPos = logoLineNode[i].getPosition();
                ofVec3f nextPos = logoLineNode[ i - 1 ].getPosition();
                float currentPosX =  nextPos.x - ( nextPos.x - currentPos.x ) * ( logoLineNode[i].typeFacelLength * 0.1 );
                float currentPosY =  nextPos.y - ( nextPos.y - currentPos.y ) * ( logoLineNode[i].typeFacelLength * 0.1 );                
                ofLine( nextPos.x, nextPos.y, nextPos.z, currentPosX, currentPosY , currentPos.z );
            if( logoLineNode[i - 1].isFinishMoving ){
                logoLineNode[i].bang = true;
            }
            
            ofPopMatrix();
        }
        ofPopMatrix();
    };
    
    void resetAnimation() {
        animationCounter = 0;
        for( int i = 1; i < logoGeom.length; i++ ){
            logoLineNode[i].resetCounter();
        }
        for(int i = 1; i < MAX_RANDOM_START_POINT_NUM; i++ ){
            animationStartId[ i ] = ofRandom( logoGeom.length );
        }
    }
        

};

#endif
