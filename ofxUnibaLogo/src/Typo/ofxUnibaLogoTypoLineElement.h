//
//  ofxUnibaLogoTypoLineElement.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef UnibaMotionLogo_ofxUnibaLogoTypoLineElement_h
#define UnibaMotionLogo_ofxUnibaLogoTypoLineElement_h
#include "ofMain.h"

class ofxUnibaLogoTypoLineElement : public virtual ofNode  {
public:
    int id;
    float typeFacelLength;
    bool bang;
    bool isFinishMoving;
    void draw() {
        if( bang ){
            typeFacelLength++;
        }
        if( 10 < typeFacelLength ){
            typeFacelLength = 10;
            isFinishMoving = true;
        }
    };
    
    ofxUnibaLogoTypoLineElement() {
        bang = false;
        isFinishMoving = false;
        typeFacelLength = 0;
    };
    
    void resetCounter() {
        typeFacelLength = 0;
        isFinishMoving = false;
        bang = false;
    };
    
};
#endif
