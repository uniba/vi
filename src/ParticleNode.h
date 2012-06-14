//
//  Node.h
//  Codern
//
//  Created by mori koichiro on 12/05/09.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"

class ParticleNode : public ofNode {

private:    
    float scale;
    float count;
    ofPolyline tetrahedronShape;
    float forceControle;
    //ofTrueTypeFont typo;

public:
    int mID;
    float powX,powY,powZ;
    float vel;
    float powRotarion;
    float alpha;
    
    ParticleNode(){
        scale = 40.0;
        alpha = 255;
        forceControle = 0.0000000025;
        tetrahedronShape.addVertex(ofPoint(1,sqrt(3),0));
        tetrahedronShape.addVertex(ofPoint(1,0,sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(2,sqrt(3),sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(0,sqrt(3),sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(1,sqrt(3),0));
        tetrahedronShape.addVertex(ofPoint(2,sqrt(3),sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(1,sqrt(3),0));
        tetrahedronShape.addVertex(ofPoint(2,sqrt(3),sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(1,0,sqrt(3)));
        tetrahedronShape.addVertex(ofPoint(0,sqrt(3),sqrt(3)));
        //typo.loadFont("frabk.ttf", 85);
    };
    
    ~ParticleNode(){
        powX = ofRandom( -1, 1 );
        powY = ofRandom( -1, 1 );
        powZ = ofRandom( -1, 1 );
        powRotarion = ofRandom( -1, 1 );
    };
    
    void update(int counter){
        count = float(counter);
        rotate(count* powRotarion, ofVec3f( powX ,powY ,powZ));
        vel = ofVec3f( powX ,powY ,powZ).length();
    }
    
    void addForce( float x, float y, float z ) {
        powX = powX + x * forceControle;
        powY = powY + y * forceControle;
        powZ = powZ + z * forceControle;
    }
        
    void customDraw() {
        move(powX,powY,powZ);
		ofSetColor(0, 0, 0, alpha);
		glPushMatrix();
		glScalef(scale, scale, scale);
        ofFill();
        tetrahedronShape.draw();
        //typo.drawString("SinOsc", 0,0);
		glPopMatrix();
	}
};
