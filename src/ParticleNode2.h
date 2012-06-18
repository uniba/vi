//
//  ParticleNode2.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#include "ofMain.h"
#include "UnibaLogoAppDefinition.h"

class ParticleNode2 : public ofNode {
    
private:    
    float scale;
    float forceControl;
    ofMesh rectFace;
    
    ofVec3f endBoldNessPoint;
    
    float spring;
    float speed;
    float friction;
    int countNumOfSpring;
    
    vector<ofColor> colors;
    
    int colierRnadomMatter() {
        return floor( ofRandom( 4 ) ) - 1;
    };
    
public:
    int mID;
    float count;
    bool startSpring;
    float rectWidth;
    ofVec3f lineStartPos;
    ofVec3f startPoint;
    ofVec3f endPoint;
    float powX,powY,powZ;
    float vel;
    float alpha;
    int colorPatternIndex;
    
    ofVec3f getNormal(ofVec3f vec0, ofVec3f vec1, ofVec3f vec2){
        ofVec3f firstVec = vec1 - vec0;
        ofVec3f secondVec = vec2 - vec0;
        ofVec3f crossedVec = firstVec.getCrossed(secondVec).getNormalized();
        return crossedVec;
    };
    
    ParticleNode2(){
        startSpring = false;
        countNumOfSpring = floor( ofRandom( 100 ) ) + 300;
        spring = 0.85f;
        speed = 0.4f;
        friction = 0.55f;
        scale = 1.0f;
        alpha = 255;
        rectWidth = 0.0f;
        forceControl = 0.0000000025f;
    };
    
    ~ParticleNode2(){
        powX = ofRandom( -1, 1 );
        powY = ofRandom( -1, 1 );
        powZ = ofRandom( -1, 1 );
        
    };
    
    void setup() {
        for(int i = 0; i < 4; i++){
            colors.push_back( colorPristArray[ colorPatternIndex ][ i ] );
        }
        ofVec3f normalForPoint = getNormal(startPoint,endPoint,endBoldNessPoint);
        rectFace.setupIndicesAuto();
        rectFace.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        int colorMatter = colierRnadomMatter();
        
        ofColor defuseCol = colors[ colorMatter ];
        if( defuseCol.getBrightness() < 127 ){
            defuseCol.setBrightness( defuseCol.getBrightness() + 25);
        } else {
            defuseCol.setBrightness( defuseCol.getBrightness() - 25);
        }
        
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
    }
    
    void update(){
        vel = ofVec3f( powX ,powY ,powZ).length();
        if( count > 1 ){
            ofVec3f startBoldNessPoint = ofVec3f( startPoint.x - rectWidth, startPoint.y + rectWidth*2, startPoint.z + sqrt(2)*rectWidth ); 
            endBoldNessPoint = ofVec3f( endPoint.x - rectWidth, endPoint.y + rectWidth*2, endPoint.z + sqrt(2)*rectWidth); 
            rectFace.setVertex(2,startBoldNessPoint);
            rectFace.setVertex(3,endBoldNessPoint);
        }
        
        //if ( count > countNumOfSpring )startSpring = true;
        float ax;
        if( startSpring ){
            ax = (0.8 - rectWidth) * spring;
            speed += ax;
            speed *= friction;
            rectWidth += speed;
        }
        
        count++;
    }
    
    void addForce( float x, float y, float z ) {
        powX = powX + x * forceControl;
        powY = powY + y * forceControl;
        powZ = powZ + z * forceControl;
    }
    
    void customDraw() {
        if( 5 == mID || 11 == mID || 13 == mID || 21 == mID ){
        } else {
            glScalef(scale, scale, scale);
            rectFace.drawFaces();
        }
	}
    
    void resetColors(int colorIndex) {
        ofDisableBlendMode();
        int colorMatter = colierRnadomMatter();
        //rectFace.clearColors();
        ofColor newColor;
        for( int i = 0; i < 4; i++ ){
            if( i%2 == 0 ){
                newColor = colorPristArray[ colorIndex ][ colorMatter ];
            } else {
                ofColor defuseCol = (colorPristArray[ colorIndex ][ colorMatter ]);
                if( defuseCol.getBrightness() < 127 ){
                    defuseCol.setBrightness( defuseCol.getBrightness() + 25);
                } else {
                    defuseCol.setBrightness( defuseCol.getBrightness() - 25);
                }
                newColor = defuseCol;
                
            }
            rectFace.setColor( i, newColor );
        }
        
    }
};
