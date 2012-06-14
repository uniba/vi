
#include "testApp.h"
#include "ofxMesh2TriMesh.h"
#include "ofxPolyline2Mesh.h"

#define MAX_NODE_NUM 1000
#define MAX_WORLD_CLIP 20000
double workRad;
int countNum = 0;
int lengthOfArray = 0;
bool debugMode = false;

static float logoVertexArray[][3] =
{
    {  0,  0,  0},{  0,200,  0},
    {-80, 80, 80},{-80,280, 80},
    {  0,200,  0},{100,200,  0},
    {-80,280, 80},{ 20,280, 80},
    {100,200,  0},{100,  0,  0},
    { 20,280, 80},{ 20, 80, 80},
    // N
    {200,200,  0},{200,  0,  0},
    {120,280, 80},{120, 80, 80},
    {200,  0,  0},{300,  0,  0},
    {120, 80, 80},{220, 80, 80},
    {300,  0,  0},{300,200,  0},
    {220, 80, 80},{220,280, 80},
    // I
    {400,  0,  0},{400,200,  0},
    {320, 80, 80},{320,280, 80},
    // B
    {500,  0,  0},{500,300,  0},
    {420, 80, 80},{420,380, 80},
    {500,300,  0},{600,200,  0},
    {420,380, 80},{520,280, 80},
    {600,200,  0},{600,100,  0},
    {520,280, 80},{520,180, 80},
    {600,100,  0},{500,100,  0},
    {520,180, 80},{420,180, 80},
    // A
    {700,  0,  0},{800,  0,  0},
    {620, 80, 80},{720, 80, 80},
    {800,  0,  0},{800,200,  0},
    {720, 80, 80},{720,280, 80},
    {800,200,  0},{700,200,  0},
    {720,280, 80},{620,280, 80},
    {700,200,  0},{700,100,  0},
    {620,280, 80},{620,180, 80},
    {700,100,  0},{800,100,  0},
    {620,180, 80},{720,180, 80}
};

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
    ofSetBackgroundAuto(false);
//	testFont.loadFont("cooperBlack.ttf", 24, true, true, true);
    
	ofSetFullscreen(false);
    ofSetFrameRate(60);
    workRad = 3500;
    for(int i=0;i<MAX_NODE_NUM;i++){
        float rad  = ofRandom( PI );
        float prad  = ofRandom( PI*2 );
        
        ParticleNode pnode;
        
        pnode.setPosition( workRad*sin(rad)*cos(prad), workRad*sin(rad)*sin(prad), workRad*cos(rad) );
        pnode.mID = i;
        
        node.push_back(pnode);
    }
    
    lengthOfArray = sizeof( logoVertexArray ) / sizeof( float [3] );
    for (int j=0;j < lengthOfArray; j++ ){
        ofNode aNode;
        ofVec3f vec;
        ofVec3f orientation;
        vec.x = logoVertexArray[j][0] * 10;
        vec.y = logoVertexArray[j][1] * 10;
        vec.z = logoVertexArray[j][2] * 10;
        
        aNode.setPosition( vec );        
        logoNode.push_back(aNode);
    }
        
//    for(int i = 0; i < lengthOfArray; i++) {
//        ofPoint pt;
//        pt.set( logoVertexArray[i][0], logoVertexArray[i][1], logoVertexArray[i][2] );
//        pts.push_back(pt);
//    }
//    mesh.clear();
//	
//	float s = 300;
//	
//	{
//		ofMesh m;
//		m.setMode(OF_PRIMITIVE_LINE_STRIP);
//		
//		for(int i = 0; i < lengthOfArray; i++)
//		{
//			ofVec3f v;
//			v.x = logoVertexArray[i][0];
//			v.y = logoVertexArray[i][1];
//			v.z = logoVertexArray[i][0];
//			
//			m.addColor(ofColor::fromHsb(ofRandom(255), 255, 255));
//			m.addVertex(v);
//		}
//		mesh.add(m);
//	}
//    
//    logoPolyArray = ofPolyline(pts);
    
    camera.setFov(45.0);
	camera.setFarClip(80000.f);
    camera.setNearClip(0.001f);
}

//--------------------------------------------------------------
void testApp::update(){
    
    for( int i=0; i < MAX_NODE_NUM; i++ ){
        float rad  = ofRandom(PI);
        float prad  = ofRandom(PI*2);
        workRad = 5500;
//        for(int j = 0; j < lengthOfArray; j++){
//            if( node[i].getGlobalPosition().distance(logoPolyArray[j] ) < 4000 ){
//                float dirX  = ( logoPolyArray[i][0] - node[i].getPosition().x ) * 0.125;
//                float dirY  = ( logoPolyArray[i][1] - node[i].getPosition().y ) * 0.125;
//                float dirZ  = ( logoPolyArray[i][2] - node[i].getPosition().z ) * 0.125;
//                node[i].powX = dirX;
//                node[i].powY = dirY;
//                node[i].powZ = dirZ;
//                node[i].update( countNum );
//            }
//        }
//        ofVec3f directToCamera =  camera.getLookAtDir();
//        node[i].setOrientation(directToCamera);
        
                
        if( node[i].getX() > MAX_WORLD_CLIP/2 ){
            node[i].setPosition( -MAX_WORLD_CLIP/2, node[i].getY(), node[i].getZ() );
        }
        
        if( node[i].getX() < -MAX_WORLD_CLIP/2 ){
            node[i].setPosition( MAX_WORLD_CLIP/2, node[i].getY(), node[i].getZ() );
        }
        
        if( node[i].getY() > MAX_WORLD_CLIP/2 ){
            node[i].setPosition( node[i].getX(), -MAX_WORLD_CLIP/2, node[i].getZ() );
        }
        
        if( node[i].getY() < -MAX_WORLD_CLIP/2 ){
            node[i].setPosition( node[i].getX(), MAX_WORLD_CLIP/2, node[i].getZ() );
        }
        
        if( node[i].getZ() > MAX_WORLD_CLIP/2 ){
            node[i].setPosition( node[i].getX(), node[i].getY(), -MAX_WORLD_CLIP/2 );
        }
        
        if( node[i].getZ() < -MAX_WORLD_CLIP/2 ){
            node[i].setPosition( node[i].getX(), node[i].getY(), MAX_WORLD_CLIP/2 );
        }
        node[i].update( countNum );
    }

    for( int i = 0; i < MAX_NODE_NUM; i++ ){
    float maximumAlpha = 0;
    float currentAlpha = 0;
        for( int j = 0; j < lengthOfArray; j++ ){
            float grav = node[i].getPosition().distance(logoNode[j].getPosition());
            if( grav < 5000  ){
                ofVec3f logoOrientation = (logoNode[j].getPosition() - node[i].getPosition() );
                node[i].addForce( logoOrientation.x * grav,
                                  logoOrientation.y * grav,
                                  logoOrientation.z * grav );
            }
            currentAlpha = 255 - grav * 0.075;
            if( maximumAlpha <= currentAlpha ) {
                maximumAlpha = currentAlpha;
            } else {
                maximumAlpha = maximumAlpha;
            }
        }
        node[i].alpha = maximumAlpha * 0.5f;
    }
    countNum += 1;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor( 255, 255, 255, (768 - mouseY) );
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    if( true == debugMode ){
        ofSetColor( 0, 0, 0 ,255 );
        string fpsStr = "frame rate: " + ofToString( ofGetFrameRate() );
        ofDrawBitmapString( fpsStr, 10, 10 );
    }

    camera.setGlobalPosition( MAX_WORLD_CLIP/2 ,MAX_WORLD_CLIP/2 , 2500 );
    camera.lookAt( ofVec3f( 0, 0, 0 ) );
    camera.begin();
    //ofRotate(ofGetElapsedTimef() * 20, 0, 1, 0);

    //ofRotate(180, 1, 0, 0);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ///////////////draw particles
    ofFill();
    ofRotate( ofGetElapsedTimef() * 10, 0, 1, 0 );
    ofPushMatrix();
        //ofTranslate( -400, -150, 0 ) ;
        //logoPolyArray.draw();
        for(int i=0;i<MAX_NODE_NUM;i++){
            node[i].draw();
            node[i].lookAt(camera.getPosition());
        }
    cout << node[0].vel << endl;
    ofPopMatrix();
    
    ofSetColor(0, 0, 0,255);
    ofSetLineWidth(0.3);
//    for(int i=0;i<MAX_NODE_NUM;i++){
//        for( int j=0;j<MAX_NODE_NUM;j++ ){
//            if( i%5 == 0 ){
//            if(  node[i].getPosition().distance(node[j].getPosition()) < 400.0f  ){
//                ofLine(node[i].getX(), node[i].getY(), node[i].getZ(),node[j].getX(), node[j].getY(), node[j].getZ());
//            }
//            }
//        }
//    }
    ////////////////draw logoPoints
    ofPushMatrix();
    ofRotateX(180);
    for (int i = 1; i < lengthOfArray; i++ ){
        ofPushMatrix();
            ofLine( logoNode[i-1].getPosition().x, logoNode[i-1].getPosition().y, logoNode[i-1].getPosition().z,
               logoNode[i].getPosition().x, logoNode[i].getPosition().y , logoNode[i].getPosition().z );
        ofPopMatrix();
    }
    ofPopMatrix();
    ///////////////////////////////
    camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
//	testChar = testFont.getCharacterAsPoints(key);
//	letter = key;

    for(int i=0;i<MAX_NODE_NUM;i++){
        float rad  = ofRandom(PI);
        float prad  = ofRandom(PI*2);
        workRad = 1500;
        node[i].setPosition( workRad*sin(rad)*cos(prad), workRad*sin(rad)*sin(prad),workRad*cos(rad) );
    }
    
    if( 'd' == key ){
        if( false == debugMode ){
            debugMode = true;
        } else {
            debugMode = false;
        }
    }

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
