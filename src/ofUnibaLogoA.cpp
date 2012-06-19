//
//  ofUnibaLogoA.cpp
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#include "UnibaLogoAppDefinition.h"
#include "ofUnibaLogoA.h"

#define MAX_WORLD_CLIP 7
int lengthOfArray = 0;
bool debugMode = false;
bool isFullscreen = false;
float typeFacelLength;
bool isParallel = false;

static float logoVertexArray[][3] =
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

ofColor colorPristArray[][4] = { //color preset
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

//--------------------------------------------------------------
void ofUnibaLogoA::setup(){
    globalCounter = 0;
    typeFacelLength = 0;
    ofBackground( 255, 255, 255 );
    ofSetVerticalSync( true );
    ofSetFullscreen( false );
    ofSetFrameRate( 60 );
    
//--------- camera setting -------------------
    camera.setFov( 45.0 );
	camera.setFarClip( 24.0f );
    camera.setNearClip( 0.1f );
    
    //light setting
//    ofEnableLighting();
//    light.setPointLight();
    ///////////////

//--------- set color array ------------------
    int lengthOfCollorArray = sizeof( colorPristArray ) / sizeof( ofColor[4] );
    currentColorIndex = floor( ofRandom(lengthOfCollorArray) -1 );
    
#ifdef LOGO_MODE_DIVIDED_BACKGROUND
    //caliculate background divider
    for ( int i = 0; i<4; i++ ){
        float angle = ofRandom( 90 ) + ( 90 * i );
        float radius = ofGetWindowWidth()/sqrt(2.0);
        ofVec2f calVect = ofVec2f( radius / sqrt(2.0), radius / sqrt(2.0) );
        calVect.rotate(angle);
        calVect += ofVec2f ( ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 );
        dividePoint[i] = calVect;
        int colorMatter = ofRandom( 4 );
        divideRectColors[i] = colorPristArray[ currentColorIndex ][ colorMatter ];
    }
    isParallel = calcIntersectionPoint(dividePoint[0],dividePoint[2],dividePoint[1],dividePoint[3],divideCrossPoint);
#endif
    
    lengthOfArray = sizeof( logoVertexArray ) / sizeof( float [3] );
    
    int colorPatternIndexNum = floor(ofRandom(7) - 1);
    
//--------- object vertex setting ------------
    for ( int j=0;j < lengthOfArray; j++ ){
        ofNode aNode;
        
        ofVec3f vec;
        ofVec3f startVec;
        ofVec3f endVec;
        
        vec.x = logoVertexArray[j][0] / 100;
        vec.y = logoVertexArray[j][1] / 100;
        vec.z = logoVertexArray[j][2] / 100;
        
        ofVec3f orientation;
       
        if( 1 <= j ){
            ParticleNode2 nodeObject;
            nodeObject.mID = j - 1;
            nodeObject.colorPatternIndex = currentColorIndex;
            endVec.x = logoVertexArray[j][0] / 100;
            endVec.y = logoVertexArray[j][1] / 100;
            endVec.z = logoVertexArray[j][2] / 100;
            startVec.x = logoVertexArray[j - 1][0] / 100;
            startVec.y = logoVertexArray[j - 1][1] / 100;
            startVec.z = logoVertexArray[j - 1][2] / 100;
            nodeObject.startPoint = startVec;
            nodeObject.endPoint = endVec;
            logoBillbordNode.push_back( nodeObject );
            logoBillbordNode[j-1].setup();
        }
        
        aNode.setPosition( startVec );     
        logoLineNode.push_back( aNode );
    }
//------------ camera setting --------------
    camera.setPosition( 0 ,0 ,10.0f );
    
    nextCamPos.x,nextCamPos.y,nextCamPos.z = 0;
    curCamPos.x,curCamPos.y,curCamPos.z = 0;
    friction = 0.03;
    spring =0.05;
    
//------------ backgroundImage --------------
    gradientMask.allocate(ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_COLOR_ALPHA);
    gradientMask.loadImage("bg_mask.png");

    
    
//------------ Syphone Server ---------------
    mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofUnibaLogoA::update(){
    for ( int i=0; i < lengthOfArray - 1; i++ ){
        logoBillbordNode[i].update();
    }
    
    //cmamera animation
    float ax;
    ax = (nextCamPos.x - curCamPos.x) * spring;
    speed.x += ax;
    speed.x *= friction;
    curCamPos.x += speed.x;
    
    float ay;
    ay = (nextCamPos.y - curCamPos.y) * spring;
    speed.y += ay;
    speed.y *= friction;
    curCamPos.y += speed.y;
    
    float az;
    az = (nextCamPos.z - curCamPos.z) * spring;
    speed.z += az;
    speed.z *= friction;
    curCamPos.z += speed.z;
    
    camera.setGlobalPosition(curCamPos.x,curCamPos.y,curCamPos.z);
    camera.lookAt( ofVec3f( 0, 0, 0 ) );
    
    if( 0 == globalCounter % 50 ){
        if( 0 == floor( ofRandom( 4 ) ) ){
            if( 0 == floor( ofRandom( 3 ) ) ){
                nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
                friction = ofRandom( 0.3 ) + 0.14;
                spring = 0.85 + ofRandom(0.24);
                for( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                    int matterREctNum = floor(ofRandom(lengthOfArray));
                    if( typeFacelLength >=20 ) logoBillbordNode[matterREctNum].startSpring = true;
                }
            }
        } else {
            nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
            nextCamPos.y = ( ofRandom( 1 ) - 0.5 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
            nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP/2 + MAX_WORLD_CLIP/2;
            friction = ofRandom( 0.125 );
            spring = 0.75 + ofRandom( 0.0125 );
            for ( int i = 0; i < floor( ofRandom( 40 ) ); i++ ){
                int matterREctNum = floor( ofRandom( lengthOfArray ) );
                if( typeFacelLength >= 20 ) logoBillbordNode[matterREctNum].startSpring = true;
            }
        }
    }
    
    isParallel = calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );

    globalCounter++;
    typeFacelLength += 0.15;
    if( typeFacelLength > 20){
        typeFacelLength = 20;
    }
    if( globalCounter > 1000 ){
        globalCounter = 0;
    }

}

//--------------------------------------------------------------
void ofUnibaLogoA::draw(){

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

    ofEnableSmoothing();
    if( true == debugMode ){
        ofSetColor( 0, 0, 0 ,255 );
        string fpsStr = "frame rate: " + ofToString( ofGetFrameRate() );
        string counterStr = "Global Counter: " + ofToString( globalCounter );
        ofDrawBitmapString( fpsStr, 10, 10 );
        ofDrawBitmapString( counterStr, 10, 30 );
    }

//-------- draw divided background ---------
#ifdef LOGO_MODE_DIVIDED_BACKGROUND
    glDisable(GL_DEPTH_TEST);
    for ( int i = 0; i < 4; i++ ){
        ofColor colCarrent = divideRectColors[i];
        colCarrent = ofColor( colCarrent.r, colCarrent.g, colCarrent.b, 220 );
        ofSetColor( colCarrent );
        ofBeginShape();
        if( 3 == i ){
            ofVertex( dividePoint[i].x, dividePoint[i].y );
            ofVertex( divideCrossPoint.x, divideCrossPoint.y );
            ofVertex( dividePoint[0].x, dividePoint[0].y );
        } else {
            ofVertex( dividePoint[i].x, dividePoint[i].y );
            ofVertex( divideCrossPoint.x, divideCrossPoint.y );
            ofVertex( dividePoint[i + 1].x, dividePoint[i + 1].y );
        }
        switch (i){
            case 0:
                ofVertex( 0, ofGetHeight() );
                break;
            case 1:
                ofVertex( 0, 0 );
                break;
            case 2:
                ofVertex( ofGetWindowWidth(), 0);
                break;
            case 3:
                ofVertex( ofGetWindowWidth(), ofGetWindowHeight() );
                break;
        }
        ofEndShape();
    }
    glEnable(GL_DEPTH_TEST);
#endif

//------- begin camera & draw 3D space -------
    ofSetColor( 255, 255, 255, 255 );
    camera.begin();
        camera.lookAt( ofVec3f( 0, 0, 0 ) );
        ofRotate(ofGetElapsedTimef() * 20, 0, 1, 0 );
        ofPushMatrix();
            ofTranslate( -4.0f, 2.0f, 0.0f ); // translate objects to center
    //        ofPushMatrix();
    //            light.setPosition(0, MAX_WORLD_CLIP, 0);
    //            ofRotateX( 180 );
    //            light.lookAt( ofVec3f( 400, 200, 0 ) );        
    //            light.setAmbientColor( ofColor( 225, 225, 255 ) );
    //            light.setSpecularColor( ofColor( 255, 255, 255 ) );
    //            light.enable();
    //        ofPopMatrix();
            
            ofSetColor( 0, 0, 0,255 );
            ofSetLineWidth( 1.25f );

//------------ draw logo type lines ----------
            ofPushMatrix();
                ofRotateX( 180 );
                ofSetColor( 0, 0, 0 );
                for ( int i = 1; i < lengthOfArray; i++ ){
                    ofPushMatrix();
                        float nextPosX =  logoLineNode[i - 1].getPosition().x - (logoLineNode[i - 1].getPosition().x- logoLineNode[i].getPosition().x) * (typeFacelLength * 0.05);
                        float nextPosY =  logoLineNode[i - 1].getPosition().y - (logoLineNode[i - 1].getPosition().y- logoLineNode[i].getPosition().y) * (typeFacelLength * 0.05);
                        ofLine( logoLineNode[i-1].getPosition().x, logoLineNode[i-1].getPosition().y, logoLineNode[i-1].getPosition().z,
                               nextPosX, nextPosY , logoLineNode[i].getPosition().z );
                    ofPopMatrix();
                }
            ofPopMatrix();
        
//------ draw logo lines width rectangle -----
            ofPushMatrix();
                ofRotateX( 180 );
                for (int i = 0; i < lengthOfArray - 1; i++ ){
                    ofPushMatrix();
                    ofFill();
                    logoBillbordNode[i].draw();
                    ofPopMatrix();
                }
            ofPopMatrix();
        ofPopMatrix();
    camera.end();
    
    gradientMask.draw( 0, 0, ofGetWindowWidth(), ofGetWindowHeight() );

//-------- distribute to Syphone server ------
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofUnibaLogoA::keyPressed  (int key){

    if( 'd' == key ){
        if( false == debugMode ){
            debugMode = true;
        } else {
            debugMode = false;
        }
    }
    if( 'f' == key ){ //full screen
        if( !isFullscreen ){
            ofSetFullscreen(true);
            isFullscreen = true;
        } else {
            ofSetFullscreen(false);
            isFullscreen = false;
        }
    }
    
    if(key == 'g'){
        nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
        nextCamPos.y = ( ofRandom( 1 ) ) * MAX_WORLD_CLIP;
        nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
        friction = ofRandom( 0.3 ) + 0.4;
        spring = 0.85 + ofRandom( 0.24 );
    }
    if(key == 't'){
        nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
        nextCamPos.y = ( ofRandom( 1 ) ) * MAX_WORLD_CLIP;
        nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
        friction = ofRandom( 0.0125 );
        spring = 0.75+ ofRandom( 0.0125 );
    }
    
    if(key == 'x'){
        int width = ofGetWindowWidth();
        int height = ofGetWindowHeight();
        currentColorIndex = floor(ofRandom( 6 )) ;

        for ( int i = 0; i < 4; i++ ){
            float angle = ofRandom( 90 ) + ( 90 * i );
            float radius = ofGetWindowWidth() / sqrt(2.0);
            ofVec2f calVect = ofVec2f( radius / sqrt(2.0), radius / sqrt(2.0) );
            calVect.rotate(angle);
            calVect += ofVec2f ( width / 2, height / 2 );
            dividePoint[i] = calVect;
        }
        isParallel = calcIntersectionPoint( dividePoint[0], dividePoint[2], dividePoint[1], dividePoint[3], divideCrossPoint );
        
        for ( int i = 0; i< lengthOfArray; i++ ){
            logoBillbordNode[i].startSpring  = false;
            logoBillbordNode[i].count = 0;
            logoBillbordNode[i].rectWidth = 0;
            typeFacelLength = 0;
            logoBillbordNode[i].resetColors(currentColorIndex);
            int colorMatter = ofRandom( 4 ) ;
            divideRectColors[i] = colorPristArray[ currentColorIndex ][ colorMatter ];
        }
    }

}

//--------------------------------------------------------------
void ofUnibaLogoA::keyReleased  (int key){
}

//--------------------------------------------------------------
void ofUnibaLogoA::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofUnibaLogoA::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofUnibaLogoA::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofUnibaLogoA::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofUnibaLogoA::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofUnibaLogoA::dragEvent(ofDragInfo dragInfo){
    
}

bool ofUnibaLogoA::calcIntersectionPoint(	const ofVec2f& pointA, const ofVec2f& pointB, const ofVec2f& pointC, const ofVec2f& pointD, ofVec2f& pointIntersection ) {
    double dR, dS;
	double dBunbo	= ( pointB.x - pointA.x ) * ( pointD.y - pointC.y ) - ( pointB.y - pointA.y ) * ( pointD.x - pointC.x );
	if( 0 == dBunbo ) return false;	// 平行
	ofVec2f vectorAC = pointC - pointA;
	dR = ( ( pointD.y - pointC.y ) * vectorAC.x - ( pointD.x - pointC.x ) * vectorAC.y ) / dBunbo;
	dS = ( ( pointB.y - pointA.y ) * vectorAC.x - ( pointB.x - pointA.x ) * vectorAC.y ) / dBunbo;
	pointIntersection = pointA + dR * ( pointB - pointA );
	return true;
}
