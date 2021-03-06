//
//  ofxUnibaLogoTypoDepthRectElement.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoTypoDepthRectElement_h
#define UnibaMotionLogo_ofxUnibaLogoTypoDepthRectElement_h
#include "ofMain.h"

class ofxUnibaLogoTypoDepthRectElement : public virtual ofNode  {

protected:    
    float scale;
    ofMesh rectFace;
    ofVec3f endBoldNessPoint;
    float spring;
    float speed;
    float friction;
    vector<ofColor> colors;
    int colierRnadomMatter() {
        return ofRandom( 4 );
    };
    ofxUnibaLogoColor logoColor;
    
public:
    int mID;
    float count;
    bool startSpring;
    bool didChangedColors;
    bool didChangedHue;
    float rectWidth;
    ofVec3f lineStartPos;
    ofVec3f startPoint;
    ofVec3f endPoint;
    float hue;
    int colorPatternIndex;
    
    ofxUnibaLogoTypoDepthRectElement(){
        startSpring = false;
        didChangedColors = false;
        hue = 0;
        spring = 0.85f;
        speed = 0.4f;
        friction = 0.55f;
        scale = 1.0f;
        rectWidth = 0.0f;
    };
    
    ~ofxUnibaLogoTypoDepthRectElement(){
        
    };
    
    void setup() {
        for(int i = 0; i < 4; i++){
            colors.push_back( logoColor.getColor( colorPatternIndex, i ) );
        }
        ofVec3f normalForPoint = ofxUnibaLogoGeom::getNormal( startPoint, endPoint, endBoldNessPoint );
        rectFace.setupIndicesAuto();
        rectFace.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        int colorMatter = colierRnadomMatter();
        ofColor defuseCol = logoColor.defuseCol(colorPatternIndex, colorMatter);
        
        rectFace.addVertex(startPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( colors[ colorMatter ] );
        
        rectFace.addVertex(endPoint);
        rectFace.addNormal(-normalForPoint);
        
        rectFace.addColor( defuseCol );
        
        rectFace.addVertex(startPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( colors[ colorMatter ] );
        
        
        rectFace.addVertex(endBoldNessPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( defuseCol );
    };
    
    void update(){
        if( count > 1 ){
            ofVec3f startBoldNessPoint = ofVec3f( startPoint.x - rectWidth, startPoint.y + rectWidth * 2, startPoint.z + sqrt( 2 ) * rectWidth ); 
            endBoldNessPoint = ofVec3f( endPoint.x - rectWidth, endPoint.y + rectWidth * 2, endPoint.z + sqrt( 2 ) * rectWidth ); 
            rectFace.setVertex(2,startBoldNessPoint);
            rectFace.setVertex(3,endBoldNessPoint);
        }
        
        float ax;
        if( startSpring ){
            ax = (0.8 - rectWidth) * spring;
            speed += ax;
            speed *= friction;
            rectWidth += speed;
        }
        
        if( didChangedColors ){
            resetColors( colorPatternIndex );
            didChangedColors = false;
        }
        
        if( didChangedHue ){
            changeHue( hue );
            didChangedHue = false;
        }
        
        count++;
    };
    
    void customDraw() {
        if( 5 == mID || 11 == mID || 13 == mID || 21 == mID ){
        } else {
#ifdef TARGET_OF_IPHONE
            if( 20 < ofGetFrameNum() ){
#endif
                glScalef(scale, scale, scale);
                rectFace.drawFaces();
#ifdef TARGET_OF_IPHONE
            }
#endif
        }
    };
    
    void resetColors( int colorIndex ) {
        int colorMatter = colierRnadomMatter();
        ofColor newColor;
        for( int i = 0; i < 4; i++ ){
            if( i%2 == 0 ){
                newColor = logoColor.getColor( colorIndex, colorMatter );
            } else {
                newColor = logoColor.defuseCol( colorIndex, colorMatter );
            }
            rectFace.setColor(i, newColor);
            colors[i] = newColor;
        }
    };
    
    void changeHue( float hueVal ) {
        for( int i = 0; i < 4; i++ ){
            ofColor currentColor = colors[i];
#ifdef TARGET_OF_IPHONE
            if( ofxUnibaLogoColor::isBlack(currentColor) && 50 < currentColor.getBrightness() ){
#else
                if( ofxUnibaLogoColor::isBlack(currentColor) ){                
#endif
                currentColor = ofColor( 255, 255, 255 );
            } else {
                float currentHue = currentColor.getHue();
                float newHue =  currentHue + hueVal ;
                if( 255 < newHue )newHue = newHue - 256;
                currentColor.setHue( newHue );
            }
            //if( 60 < currentColor.getBrightness() ){
            rectFace.setColor(i, currentColor);
            //}
        }
    };
    
};


#endif
