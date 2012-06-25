//
//  ofxUnibaLogoTypoDepthRectFaceElement.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoTypoDepthRectFaceElement_h
#define UnibaMotionLogo_ofxUnibaLogoTypoDepthRectFaceElement_h
#include "ofMain.h"

class ofxUnibaLogoTypoDepthRectFaceElement : public ofNode  {

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
    bool isChangeColors;
    bool isChangeHue;
    float rectWidth;
    ofVec3f lineStartPos;
    ofVec3f startPoint;
    ofVec3f endPoint;
    float hue;
    int colorPatternIndex;
    
    ofxUnibaLogoTypoDepthRectFaceElement(){
        startSpring = false;
        isChangeColors = false;
        hue = 0;
        spring = 0.85f;
        speed = 0.4f;
        friction = 0.55f;
        scale = 1.0f;
        rectWidth = 0.0f;
    };
    
    ~ofxUnibaLogoTypoDepthRectFaceElement(){
        
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
        
        if( isChangeColors ){
            resetColors( colorPatternIndex );
            isChangeColors = false;
        }
        
        if( isChangeHue ){
            changeHue( hue );
            isChangeHue = false;
        }
        
        count++;
    };
    
    void customDraw() {
        if( 5 == mID || 11 == mID || 13 == mID || 21 == mID ){
        } else {
            glScalef(scale, scale, scale);
            rectFace.drawFaces();
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
            if( ofxUnibaLogoColor::isBlack(currentColor) ){
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
