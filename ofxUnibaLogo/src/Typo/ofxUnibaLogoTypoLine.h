//
//  ofxUnibaLogoTypoLine.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoTypoLine_h
#define UnibaMotionLogo_ofxUnibaLogoTypoLine_h
#include "ofxUnibaLogoTypo.h"
#include "ofxUnibaLogoGeom.h"

class ofxUnibaLogoTypoLine : public virtual ofxUnibaLogoTypo {
private:
    ofxUnibaLogoGeom logoGeom;
    vector<ofNode> logoLineNode;
public:
    void setup() {
        ofxUnibaLogoTypo::setup();
        //--------- object vertex setting ------------
        for ( int i = 0; i < logoGeom.length; i++ ){
            ofNode aNode;
            aNode.setPosition( endPoints[i] );
            logoLineNode.push_back( aNode );
        };
    };
    
    void draw() {
        ofPushMatrix();
        ofRotateX( 180 );
        ofSetColor( 0, 0, 0 );
        for ( int i = 1; i < logoGeom.length; i++ ){
            ofPushMatrix();
                ofVec3f currentPos = logoLineNode[i].getPosition();
                ofVec3f nextPos = logoLineNode[ i - 1 ].getPosition();
                float currentPosX =  nextPos.x - ( nextPos.x - currentPos.x ) * ( typeFacelLength * 0.05 );
                float currentPosY =  nextPos.y - ( nextPos.y - currentPos.y ) * ( typeFacelLength * 0.05 );
                ofLine( nextPos.x, nextPos.y, nextPos.z, currentPosX, currentPosY , currentPos.z );
            ofPopMatrix();
        }
        ofPopMatrix();
    };
    

};

#endif
