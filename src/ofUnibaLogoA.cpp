//
//  ofUnibaLogoA.cpp
//  UnibaMotionLogo
//
//  Created by mori koichiro on 12/05/31.
//  Copyright (c) 2012年 __Uniba Inc.__. All rights reserved.
//
#define WINDOW_WIDTH_DISPLAY 1280
#define WINDOW_HEIGHT_DISPLAY 800
#define WINDOW_WIDTH_CARD 910
#define WINDOW_HEIGHT_CARD 550
#define WINDOW_WIDTH_RECTANGLE 900
#define WINDOW_HEIGHT_RECTANGLE 900

#include "ofUnibaLogoA.h"

string gradientBackgoundImage = "bg_mask.png";
string syphoneServerName = "Uniba Motion Logo Screen Output";
string uiSettingFilePath = "GUI/guiSettings.xml";

bool debugMode = false;
bool drawGradation = true;
//--------------------------------------------------------------
void ofUnibaLogoA::setup(){
    
    ofBackground( 255, 255, 255 );
    ofSetVerticalSync( true );
    ofSetFullscreen( false );
    ofSetFrameRate( 60 );
    
//----------ofxUnibaLogo object--------------
    unibaLogo.setup();
    
//------------ backgroundImage --------------
    gradientMask.allocate( ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA );
    gradientMask.loadImage( gradientBackgoundImage );

//------------ Syphone Server ---------------
    mainOutputSyphonServer.setName( syphoneServerName );
    
//------------ UI Settings--- ---------------
    vector<string> screenSizeRadioNames; 
	screenSizeRadioNames.push_back("Display");
	screenSizeRadioNames.push_back("Card");
	screenSizeRadioNames.push_back("Rectangle");	
    
    gui = new ofxUICanvas( 0, 0 , 300, 800 );
    gui->addWidgetDown( new ofxUILabel("UNIBA MOTION LOGO v0.0.1", OFX_UI_FONT_LARGE) ); 
    gui->addWidgetDown( new ofxUIButton( 20, 20, false, "CHANEGE COLOR VARIATION") );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, true, "DRAW LINE") );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, true, "ANIMATION AUTO") );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, true, "DRAW MASK GRADATION") );
    gui->addWidgetDown( new ofxUIRadio( 20, 20, "WINDOW SIZE", screenSizeRadioNames, OFX_UI_ORIENTATION_HORIZONTAL) );
    gui->addWidgetDown( new ofxUIToggle( 20, 20, false, "FULL SCREEN") );
    gui->addWidgetDown( new ofxUIRotarySlider( 100, 0, 255, 0, "HUE" ) ); 
    gui->addWidgetDown( new ofxUILabel( "press \'o\' to hide and show controller menu." ,OFX_UI_FONT_SMALL ) ); 
    gui->addWidgetDown( new ofxUILabel( "press \'c\' to capture screen." ,OFX_UI_FONT_SMALL ) ); 
    ofAddListener( gui -> newGUIEvent, this, &ofUnibaLogoA::guiEvent ); 
    gui->loadSettings( uiSettingFilePath ); 
    
    //conce set color variation.
    changeColorVariation();
    
    grabbedImage.allocate( ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA );
    
}

//--------------------------------------------------------------
void ofUnibaLogoA::update(){
//----------ofxUnibaLogo object--------------
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
    
//----------ofxUnibaLogo object-------------
    
    unibaLogo.draw();

//------------ backgroundImage --------------
    if( drawGradation ){
        gradientMask.draw( 0, 0, ofGetWidth(), ofGetHeight() );
    }
    
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
    if( 'c' == key ){
        grabbedImage.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        
        grabbedImage.saveImage("logo_cap_image_" + ofGetTimestampString("%m_%d_%H_%M_%S") + ".png" );
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

void ofUnibaLogoA::changeColorVariation () {
    unibaLogo.changeColorVariation();
}

//--------------------------------------------------------------
void ofUnibaLogoA::exit() {
//---------- UI events when colled application exit------
    ofxUIRotarySlider *hueSlider =  (ofxUIRotarySlider *)( gui -> getWidget( "HUE" ) );
    hueSlider -> setValue( 0 );
    ofxUIToggle *toggleDrawLine =  (ofxUIToggle *)( gui -> getWidget( "DRAW LINE" ) );
    toggleDrawLine -> setValue( true );
    ofxUIToggle *toggleAnimation =  (ofxUIToggle *)( gui -> getWidget( "ANIMATION AUTO" ) );
    toggleAnimation -> setValue( true );
    ofxUIToggle *toggleFullscreen =  (ofxUIToggle *)( gui -> getWidget( "FULL SCREEN" ) );
    toggleFullscreen -> setValue( false );
    ofxUIToggle *toggleMaskGradation =  (ofxUIToggle *)( gui -> getWidget( "DRAW MASK GRADATION" ) );
    toggleMaskGradation -> setValue( true );
	gui -> saveSettings( uiSettingFilePath );
    delete gui;
}

//--------------------------------------------------------------
void ofUnibaLogoA::guiEvent( ofxUIEventArgs &e ) {
//------------ UI Events-------------------
    string widgetName = e.widget -> getName();
    if( widgetName == "HUE" ) {
        ofxUIRotarySlider *slider = (ofxUIRotarySlider *) e.widget;    
        float hue =  slider -> getScaledValue();
        unibaLogo.setHue( hue );
    } else if ( widgetName == "CHANEGE COLOR VARIATION" ) {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        if( button -> getValue() ){
            changeColorVariation();
        }
    } else if ( widgetName == "DRAW LINE" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        unibaLogo.drawLineType =  toggle -> getValue();
    } else if ( widgetName == "ANIMATION AUTO" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        unibaLogo.isAnimationAuto =  toggle -> getValue();
    } else if ( widgetName == "DRAW MASK GRADATION" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        drawGradation =  toggle -> getValue();
    } else if ( widgetName == "Display" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        if( toggle -> getValue() ){
            ofSetWindowShape( WINDOW_WIDTH_DISPLAY, WINDOW_HEIGHT_DISPLAY );
        }
    } else if( "Card" == widgetName ){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        if( toggle -> getValue() ){
            ofSetWindowShape( WINDOW_WIDTH_CARD, WINDOW_HEIGHT_CARD );
        }
    } else if( "Rectangle" == widgetName ){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        if( toggle -> getValue() ){
            ofSetWindowShape( WINDOW_WIDTH_RECTANGLE, WINDOW_HEIGHT_RECTANGLE );
        }
    } else if ( e.widget -> getName() == "FULL SCREEN" ) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;    
        ofSetFullscreen( toggle -> getValue() );
    }
    
    
}
