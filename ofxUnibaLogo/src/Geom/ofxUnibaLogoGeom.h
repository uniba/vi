//
//  UnibaLogoGeom.h
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/06/22.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#ifndef UnibaMotionLogo_OFXUnibaLogoGeom_h
#define UnibaMotionLogo_OFXUnibaLogoGeom_h

class ofxUnibaLogoGeom {
    public:
        int lengthOfArray;
    
        float logoVertexArray[32][3];

        static bool calcIntersectionPoint(	const ofVec2f& pointA, const ofVec2f& pointB, const ofVec2f& pointC, const ofVec2f& pointD, ofVec2f& pointIntersection ) {
            double dR, dS;
            double dBunbo	= ( pointB.x - pointA.x ) * ( pointD.y - pointC.y ) - ( pointB.y - pointA.y ) * ( pointD.x - pointC.x );
            if( 0 == dBunbo ) return false;	// 平行
            ofVec2f vectorAC = pointC - pointA;
            dR = ( ( pointD.y - pointC.y ) * vectorAC.x - ( pointD.x - pointC.x ) * vectorAC.y ) / dBunbo;
            dS = ( ( pointB.y - pointA.y ) * vectorAC.x - ( pointB.x - pointA.x ) * vectorAC.y ) / dBunbo;
            pointIntersection = pointA + dR * ( pointB - pointA );
            return true;
        };
        
        // constructor
        ofxUnibaLogoGeom(){
            static float logoVertexRef[][3] =
            {     //2D UNIBA LOGO TYPO
                {  0,  0,  0},{  0,200,  0},
                {  0,200,  0},{100,200,  0},
                {100,200,  0},{100,  0,  0},
                // N
                {200,200,  0},{200,  0,  0},
                {200,  0,  0},{300,  0,  0},
                {300,  0,  0},{300,200,  0},
                // I
                {400,  0,  0},{400,200,  0},
                // B
                {500,  0,  0},{500,300,  0},
                {500,300,  0},{600,200,  0},
                {600,200,  0},{600,100,  0},
                {600,100,  0},{500,100,  0},
                // A
                {700,  0,  0},{800,  0,  0},
                {800,  0,  0},{800,200,  0},
                {800,200,  0},{700,200,  0},
                {700,200,  0},{700,100,  0},
                {700,100,  0},{800,100,  0},
            };
            memcpy(logoVertexArray, logoVertexRef, sizeof logoVertexRef);
            lengthOfArray = sizeof( logoVertexRef ) / sizeof( float[ 3 ] );
        };
};
#endif
