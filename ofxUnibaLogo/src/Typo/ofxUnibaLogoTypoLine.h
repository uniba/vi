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
    void draw( float typeFacelLength ) {
        ofPushMatrix();
        ofRotateX( 180 );
        ofSetColor( 0, 0, 0 );
        for ( int i = 1; i < logoGeom.length; i++ ){
            ofPushMatrix();
            float nextPosX =  logoLineNode[ i - 1 ].getPosition().x - (logoLineNode[ i - 1 ].getPosition().x- logoLineNode[i].getPosition().x) * (typeFacelLength * 0.05);
            float nextPosY =  logoLineNode[ i - 1 ].getPosition().y - (logoLineNode[ i - 1 ].getPosition().y- logoLineNode[i].getPosition().y) * (typeFacelLength * 0.05);
            ofLine( logoLineNode[ i - 1 ].getPosition().x, logoLineNode[ i - 1 ].getPosition().y, logoLineNode[ i - 1 ].getPosition().z,
                   nextPosX, nextPosY , logoLineNode[i].getPosition().z );
            ofPopMatrix();
        }
        ofPopMatrix();
    };
    
    void addNode( ofNode aNode ){
        logoLineNode.push_back( aNode );
    }

};

#endif
