//
//  ofxUnibaLogoBackgroundDivision.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoBackgroundDivision_h
#define UnibaMotionLogo_ofxUnibaLogoBackgroundDivision_h

#include "ofMain.h"
#include "ofxUnibaLogoColor.h"
#include "ofxUnibaLogoGeom.h"

class ofxUnibaLogoBackgroundDivision {

private:
    ofVec2f dividePoint[4];  //background divide vertexes
    ofVec2f divideCrossPoint;
    ofColor divideRectColors[4];
    float divideRectColorHues[4];
    ofxUnibaLogoColor logoColor;

public:
    void setup( int currentColorIndex ) {
        //caliculate background divider
        for ( int i = 0; i < 4; i++ ){
            float angle = ofRandom( 90 ) + ( 90 * i );
            float radius = ofGetWidth() / sqrt( 2.0 );
            ofVec2f calVect = ofVec2f( radius / sqrt( 2.0 ), radius / sqrt( 2.0 ) );
            calVect.rotate( angle );
            calVect += ofVec2f ( ofGetWidth() / 2, ofGetHeight() / 2 );
            dividePoint[i] = calVect;
            int colorMatter = ofRandom( 4 );
            divideRectColors[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatter ];
            divideRectColorHues[i] = logoColor.colorPristArray[ currentColorIndex ][ colorMatter ].getHue();
        }
        ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[ 0 ], dividePoint[ 2 ], dividePoint[ 1 ], dividePoint[ 3 ], divideCrossPoint );
    };
    
    void update( ofVec3f speed ) {
        for( int i = 0; i< 4; i++ ){
            dividePoint[i].x += speed.x * 30;
            dividePoint[i].y += speed.y * 30;
        }
        ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );  
    };
    
    void draw() {
        //-------- draw divided background ---------
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
    };
    
    void setHue( float hue ){
        for( int i = 0; i < 4; i++ ){
            float currentHue = divideRectColorHues[i];
            currentHue = currentHue + hue;
            if( 255 < currentHue )currentHue = currentHue - 256;
            if( 60 < divideRectColors[i].getBrightness() ){
                divideRectColors[i].setHue( currentHue );
            }
        }
    };
    
    void changeColorVariation ( int colorIndex ){
        int width = ofGetWidth();
        int height = ofGetHeight();
        
        for ( int i = 0; i < 4; i++ ){
            
            float angle = ofRandom( 90 ) + ( 90 * i );
            float radius = ofGetWidth() / sqrt(2.0) * 3;
            ofVec2f calVect = ofVec2f( radius / sqrt(2.0), radius / sqrt(2.0) );
            calVect.rotate( angle );
            calVect += ofVec2f ( width / 2, height / 2 );
            dividePoint[i] = calVect;
            int colorMatterFordivider = ofRandom( 4 ) ;
            divideRectColors[i] = logoColor.colorPristArray[ colorIndex ][ colorMatterFordivider ];
            divideRectColorHues[i] = logoColor.colorPristArray[ colorIndex ][ colorMatterFordivider ].getHue();
            
        }
        ofxUnibaLogoGeom::calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );
    };
};


#endif
