//
//  ofUnibaLogoA.cpp
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//

#include "UnibaLogoAppDefinition.h"
#include "ofUnibaLogoA.h"
#include "ofxUnibaLogo.h"

string gradientBackgoundImage = "bg_mask.png";
string syphoneServerName = "Uniba Motion Logo Screen Output";
string uiSettingFilePath = "GUI/guiSettings.xml";

bool debugMode = false;
bool isParallel = false;

//--------------------------------------------------------------
void ofUnibaLogoA::setup(){
    
    ofBackground( 255, 255, 255 );
    ofSetVerticalSync( true );
    ofSetFullscreen( false );
    ofSetFrameRate( 60 );
    
//----------ofxUniba logo object-------------
    unibaLogo.setup();
    
//------------ backgroundImage --------------
    gradientMask.allocate( ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA );
    gradientMask.loadImage( gradientBackgoundImage );

//------------ Syphone Server ---------------
    mainOutputSyphonServer.setName( syphoneServerName );
    
//------------ UI Settings--- ---------------
    gui = new ofxUICanvas( 0, 0 , 300, 800 );
    gui->addWidgetDown( new ofxUILabel("UNIBA MOTION LOGO v0.0.1", OFX_UI_FONT_LARGE) ); 
    gui->addWidgetDown( new ofxUIButton( 20, 20, false, "CHANEGE COLOR VARIATION") );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, false, "ANIMATION AUTO") );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, false, "FULL SCREEN") );
    gui->addWidgetDown( new ofxUIRotarySlider( 100, 0, 255, 0, "HUE" ) ); 
    ofAddListener( gui -> newGUIEvent, this, &ofUnibaLogoA::guiEvent ); 
    gui->loadSettings( uiSettingFilePath ); 

    //conce set color variation.
    changeColorVariation();
}

//--------------------------------------------------------------
void ofUnibaLogoA::update(){    
    unibaLogo.update();
}

//--------------------------------------------------------------
void ofUnibaLogoA::draw(){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

    ofEnableSmoothing();
    if( true == debugMode ){
        ofSetColor( 255, 255, 255 ,255 );
        string fpsStr = "frame rate: " + ofToString( ofGetFrameRate() );
        string counterStr = "Global Counter: " + ofToString( unibaLogo.globalCounter );
        ofDrawBitmapString( fpsStr, 10, 20 );
        ofDrawBitmapString( counterStr, 10, 40 );
        ofDrawBitmapString( "Press \'x\' to change colors", 10, 60 );
        ofDrawBitmapString( "Press \'f\' to fullscreen mode", 10, 80 );
    }
    
    unibaLogo.draw();
    
    gradientMask.draw( 0, 0, ofGetWidth(), ofGetHeight() );

//-------- distribute to Syphone server ------
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofUnibaLogoA::keyPressed  (int key){

    if( 'o' == key ){
        gui -> toggleVisible();
    }
    if( 'd' == key ){
        if( false == debugMode ){
            debugMode = true;
        } else {
            debugMode = false;
        }
    }
//    if(key == 'g'){
//        unibaLogo.nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
//        unibaLogo.nextCamPos.y = ( ofRandom( 1 ) ) * MAX_WORLD_CLIP;
//        unibaLogo.nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
//        unibaLogo.friction = ofRandom( 0.3 ) + 0.4;
//        unibaLogo.spring = 0.85 + ofRandom( 0.24 );
//    }
//    if(key == 't'){
//        unibaLogo.nextCamPos.x = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
//        unibaLogo.nextCamPos.y = ( ofRandom( 1 ) ) * MAX_WORLD_CLIP;
//        unibaLogo.nextCamPos.z = ( ofRandom( 2 ) - 1 ) * MAX_WORLD_CLIP;
//        unibaLogo.friction = ofRandom( 0.0125 );
//        unibaLogo.spring = 0.75+ ofRandom( 0.0125 );
//    }

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

void ofUnibaLogoA::changeColorVariation () {
    unibaLogo.changeColorVariation();
}

//--------------------------------------------------------------
void ofUnibaLogoA::exit() {
    ofxUIRotarySlider *hueSlider =  (ofxUIRotarySlider *)( gui -> getWidget( "HUE" ) );
    hueSlider -> setValue( 0 );
    ofxUIToggle *toggleAnimation =  (ofxUIToggle *)( gui -> getWidget( "ANIMATION AUTO" ) );
    toggleAnimation -> setValue( true );
    ofxUIToggle *toggleFullscreen =  (ofxUIToggle *)( gui -> getWidget( "FULL SCREEN" ) );
    toggleFullscreen -> setValue( false );
	gui -> saveSettings( uiSettingFilePath );
    delete gui;
}

//--------------------------------------------------------------
void ofUnibaLogoA::guiEvent( ofxUIEventArgs &e ) {
    if( e.widget -> getName() == "HUE" ) {
        ofxUIRotarySlider *slider = (ofxUIRotarySlider *) e.widget;    
        unibaLogo.hue =  slider -> getScaledValue();
//        for( int i = 0; i < unibaLogo.lengthOfArray; i++ ){
//            unibaLogo.logoBillbordNode[i].hue = unibaLogo.hue;
//            unibaLogo.logoBillbordNode[i].isChangeHue = true;
//        }
//        for( int i = 0; i < 4; i++ ){
//            float currentHue = unibaLogo.divideRectColorHues[i];
//            currentHue = currentHue + unibaLogo.hue;
//            if( 255 < currentHue )currentHue = currentHue - 256;
//            if( 60 < unibaLogo.divideRectColors[i].getBrightness() ){
//                unibaLogo.divideRectColors[i].setHue( currentHue );
//            }
//        }
        
    } else if ( e.widget -> getName() == "CHANEGE COLOR VARIATION" ) {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        if( button -> getValue() ){
            changeColorVariation();
        }
    } else if ( e.widget -> getName() == "ANIMATION AUTO" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        unibaLogo.isAnimationAuto =  toggle -> getValue();
    } else if ( e.widget -> getName() == "FULL SCREEN" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        ofSetFullscreen( toggle -> getValue() );
    }
}
