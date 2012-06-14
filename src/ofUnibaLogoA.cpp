/////////////////To DO
/*
 1.Depth TestとCamereの両立
 2.Lineのアニメーション
 3.クラス無いカウンター
 4.アニメーション
 5.カメラアニメーション
*/

#include "ofUnibaLogoA.h"
#include "ofxMesh2TriMesh.h"
#include "ofxPolyline2Mesh.h"

#define MAX_NODE_NUM 1000
#define MAX_WORLD_CLIP 20000
double workRad;
int countNum = 0;
int lengthOfArray = 0;
bool debugMode = false;
bool isFullscreen = false;

static float logoVertexArray[][3] =
{     //2D LOGO
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

//--------------------------------------------------------------
void ofUnibaLogoA::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    ofSetFullscreen(false);
    ofSetFrameRate(60);
    
    camera.setFov(65.0);
	camera.setFarClip(24.0f);
    camera.setNearClip(0.1f);
    //light setting
    ofEnableLighting();
//    light.setPointLight();
    ///////////////
    
    lengthOfArray = sizeof( logoVertexArray ) / sizeof( float [3] );
    
    for (int j=0;j < lengthOfArray; j++ ){
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
            endVec.x = logoVertexArray[j][0] / 100;
            endVec.y = logoVertexArray[j][1] / 100;
            endVec.z = logoVertexArray[j][2] / 100;
            startVec.x = logoVertexArray[j - 1][0] / 100;
            startVec.y = logoVertexArray[j - 1][1] / 100;
            startVec.z = logoVertexArray[j - 1][2] / 100;
            nodeObject.startPoint = startVec;
            nodeObject.endPoint = endVec;
            logoBillbordNode.push_back(nodeObject);
            logoBillbordNode[j-1].setup();
        }
        
        aNode.setPosition( startVec );     
        logoNode.push_back(aNode);
    }
    
    camera.setPosition( 0 ,0 ,10.0f );
    
    nextCamPos.x,nextCamPos.y,nextCamPos.z = 0;
    curCamPos.x,curCamPos.y,curCamPos.z = 0;
    friction = 0.03;
    spring =0.05;
    
    //Syphone Server
    mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofUnibaLogoA::update(){
    for (int i=0; i < lengthOfArray - 1; i++ ){
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
    camera.lookAt( ofVec3f( 0,0,0 ) );
}

//--------------------------------------------------------------
void ofUnibaLogoA::draw(){
    glEnable(GL_DEPTH_TEST);
    
    ofEnableSmoothing();
    
    if( true == debugMode ){
        ofSetColor( 0, 0, 0 ,255 );
        string fpsStr = "frame rate: " + ofToString( ofGetFrameRate() );
        ofDrawBitmapString( fpsStr, 10, 10 );
    }
    camera.begin();
    camera.lookAt(ofVec3f(0,0,0));
    ofRotate(ofGetElapsedTimef() * 20, 0, 1, 0);
    ofPushMatrix();
        ofTranslate( -4.0f, 2.0f, 0.0f);
        ofPushMatrix();
            light.setPosition(0, MAX_WORLD_CLIP, 0);
            ofRotateX(180);
            light.lookAt(ofVec3f(400,200,0));        
            light.setAmbientColor(ofColor(125, 125, 225));
            light.setSpecularColor(ofColor(255, 255, 255));
            light.enable();
        ofPopMatrix();
        
        ofSetColor(0, 0, 0,255);
        ofSetLineWidth(1.25);
        
        ofPushMatrix();
        ofRotateX(180);
            for (int i = 1; i < lengthOfArray; i++ ){
                ofPushMatrix();
                ofLine( logoNode[i-1].getPosition().x, logoNode[i-1].getPosition().y, logoNode[i-1].getPosition().z,
                       logoNode[i].getPosition().x, logoNode[i].getPosition().y , logoNode[i].getPosition().z );
                ofPopMatrix();
            }
        ofPopMatrix();
      
        
        ofPushMatrix();
            ofRotateX(180);
            for (int i=0; i < lengthOfArray - 1; i++ ){
                ofPushMatrix();
                ofFill();
                logoBillbordNode[i].draw();
                ofPopMatrix();
            }
        ofPopMatrix();
    ofPopMatrix();
    camera.end();
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
    if( 'f' == key ){
        if( !isFullscreen ){
            ofSetFullscreen(true);
            isFullscreen = true;
        } else {
            ofSetFullscreen(false);
            isFullscreen = false;
        }
    }
    
    if(key == 'g'){
        nextCamPos.x = (ofRandom(2)-1)*7;
        nextCamPos.y = (ofRandom(1))*7;
        nextCamPos.z = (ofRandom(2)-1)*7;
        friction = ofRandom(0.3)+0.4;
        spring = 0.85+ ofRandom(0.24);
    }
    if(key == 't'){
        nextCamPos.x = (ofRandom(2)-1)*7;
        nextCamPos.y = (ofRandom(1))*7;
        nextCamPos.z = (ofRandom(2)-1)*7;
        friction = ofRandom(0.0125);
        spring = 0.75+ ofRandom(0.0125);
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
