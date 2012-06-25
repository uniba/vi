//
//  UnibaLogoColor.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#ifndef UnibaMotionLogo_OFXUnibaLogoColor_h
#define UnibaMotionLogo_OFXUnibaLogoColor_h

#include "ofMain.h"

class ofxUnibaLogoColor {

public:
    int length;
    ofColor colorPristArray[8][4];

    static bool isBlack( ofColor color ){
        if( color.r == 0 && color.g == 0 && color.g == 0){
            return true;
        }
        return false;
    }

    // constructor
    ofxUnibaLogoColor() {
        static ofColor refColors[8][4] = { //color preset
            {
                ofColor( 217, 217, 217 ),
                ofColor( 199, 95, 91 ),
                ofColor( 242, 156, 159 ),
                ofColor( 255, 246, 26 )
            },
            {
                ofColor( 77, 77, 77 ),
                ofColor( 0, 158, 150 ),
                ofColor( 207, 159, 93 ),
                ofColor( 206, 100, 95 )
            }, 
            {
                ofColor( 247, 247, 0 ),
                ofColor( 179, 179, 179 ),
                ofColor( 255, 0, 0 ),
                ofColor( 218, 100, 95 )
            },
            {
                ofColor( 0, 0, 0 ),
                ofColor( 204, 204, 204 ),
                ofColor( 0, 104, 183 ),
                ofColor( 245, 151, 0 )
            },
            {
                ofColor( 164, 0, 0 ),
                ofColor( 228, 246, 254 ),
                ofColor( 76, 137, 164 ),
                ofColor( 3, 0, 76 )
            },
            {
                ofColor( 137, 201, 151 ),
                ofColor( 253, 251, 222 ),
                ofColor( 131, 106, 74 ),
                ofColor( 209, 163, 87 )
            },
            {
                ofColor( 255, 234, 240 ),
                ofColor( 0, 187, 236 ),
                ofColor( 44, 110, 213 ),
                ofColor( 255, 252, 190 )
            },
            {
                ofColor( 30, 50, 0 ),
                ofColor( 193, 231, 50 ),
                ofColor( 14, 3, 107 ),
                ofColor( 255, 151, 168 )
            }
        };
        memcpy(colorPristArray, refColors, sizeof refColors);
        length = sizeof( refColors ) / sizeof( ofColor[ 4 ] );
    }
    
    ofColor defuseCol( int colorIndex, int colorMatter ){
        ofColor color = colorPristArray[ colorIndex ][ colorMatter ] ;
        if( color.getBrightness() < 127 ){
            color.setBrightness( color.getBrightness() + 25);
        } else {
            color.setBrightness( color.getBrightness() - 25);
        }
        return color;
    };
    
    ofColor getColor( int colorIndex, int colorMatterFordivider ){
        return colorPristArray[ colorIndex ][ colorMatterFordivider ];
    };
    
    float getHueOfColor( int colorIndex, int colorMatterFordivider ){
        return colorPristArray[ colorIndex ][ colorMatterFordivider ].getHue();
    };
};

#endif
