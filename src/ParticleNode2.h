//
//  ParticleNode2.h
//  Codern
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "ofMain.h"

class ParticleNode2 : public ofNode {
    
private:    
    float scale;
    float count;
    float forceControl;
    ofMesh rectFace;
    float rectWidth;
    ofVec3f endBoldNessPoint;
    
public:
    int mID;
    ofVec3f startPoint;
    ofVec3f endPoint;
    float powX,powY,powZ;
    float vel;
    float alpha;
    
    ofVec3f getNormal(ofVec3f vec0, ofVec3f vec1, ofVec3f vec2){
        ofVec3f firstVec = vec1 - vec0;
        ofVec3f secondVec = vec2 - vec0;
        ofVec3f crossedVec = firstVec.getCrossed(secondVec).getNormalized();
        return crossedVec;
    };
    
    ParticleNode2(){
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
        ofVec3f normalForPoint = getNormal(startPoint,endPoint,endBoldNessPoint);
        rectFace.setupIndicesAuto();
        rectFace.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        rectFace.addVertex(startPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( ofColor( 8 * (mID+1) , 0, 256 - 8 * mID ) );
        
        rectFace.addVertex(endPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( ofColor(  8 * (mID+1) , 0, 256 - 8 * mID ) );
        
        rectFace.addVertex(startPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( ofColor(  8 * (mID+1) , 0, 256 - 8 * mID ) );
        
        rectFace.addVertex(endBoldNessPoint);
        rectFace.addNormal(-normalForPoint);
        rectFace.addColor( ofColor(  8 * (mID+1) , 0, 256 - 8 * mID ) );
    }
    
    void update(){
        vel = ofVec3f( powX ,powY ,powZ).length();
        if( count > 1 ){
            ofVec3f startBoldNessPoint = ofVec3f( startPoint.x - rectWidth, startPoint.y + rectWidth*2, startPoint.z + sqrt(2)*rectWidth ); 
            endBoldNessPoint = ofVec3f( endPoint.x - rectWidth, endPoint.y + rectWidth*2, endPoint.z + sqrt(2)*rectWidth); 
            rectFace.setVertex(2,startBoldNessPoint);
            rectFace.setVertex(3,endBoldNessPoint);
        }
        
        count++;
        rectWidth = count/100;
        if( rectWidth > 0.8){
            rectWidth = 0.8;
        }
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
};
