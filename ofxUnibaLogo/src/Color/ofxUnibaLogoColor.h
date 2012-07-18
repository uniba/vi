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
    ofColor colorPristArray[4][4];

    static bool isBlack( ofColor color ){
        if( color.r == 0 && color.g == 0 && color.g == 0){
            return true;
        }
        return false;
    }
    /*1、ダイナミック（色相変化）
     77/77/77
     204/204/204
     0/104/183
     245/151/0
     
     ２、カラフル（色相変化？）
     217/217/217
     199/95/91
     242/156/159
     255/246/26
     
     ３、淡い（明度変化？）
     R: 255 G: 234 B: 240
     R: 0 G: 187 B: 236
     R: 44 G: 110 B: 213
     R: 255 G: 252 B: 190
     
     ４、渋い（彩度変化？）
     R: 137 G: 201 B: 151
     R: 253 G: 251 B: 222
     R: 131 G: 106 B: 74
     R: 209 G: 163 B: 87
*/
    // constructor
    ofxUnibaLogoColor() {
        static ofColor refColors[4][4] = { //color preset
            {
                ofColor( 77, 77, 77 ),
                ofColor( 204, 204, 204 ),
                ofColor( 0, 104, 183 ),
                ofColor( 245, 151, 0 )
            },
            {
                ofColor( 217, 217, 217 ),
                ofColor( 199, 95, 91 ),
                ofColor( 242, 156, 159 ),
                ofColor( 255, 246, 26 )
            },
            {
                ofColor( 255, 234, 240 ),
                ofColor( 0, 187, 236 ),
                ofColor( 44, 110, 213 ),
                ofColor( 255, 252, 190 )
            },
            {
                ofColor( 137, 201, 151 ),
                ofColor( 253, 251, 222 ),
                ofColor( 131, 106, 74 ),
                ofColor( 209, 163, 87 )
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
