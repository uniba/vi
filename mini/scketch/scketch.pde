/*
1、ダイナミック（色相変化）
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

int stageWidth = 64;
int stageHeight = 64;

int counter;

float springWidthCount;
float springWidthCount2;
float springWidthCount3;

float speed,speed2,speed3 = 0.45;
float spring = 0.74;
float friction = 0.6;

float nextPos;
float nextPos2;
float nextPos3;

float currentPos;
float currentPos2;
float currentPos3;

color[] colors = new color[4];

PVector[] letterPoints_0 = new PVector[4];
PVector[] letterPoints_1 = new PVector[4];
PVector[] letterPoints_2 = new PVector[4];

void setup() {
    colors[0] = color(204);
    colors[1] = color(77);
    colors[2] = color(245,151,9);
    colors[3] = color(0,104,183);
    counter = 0;
    nextPos = 0;
    nextPos2 = 50;
    nextPos3 = 100;
    counter = 0;
    size(stageWidth, stageHeight, P2D);
    background(77,77,77);

    springWidthCount = 0;
    springWidthCount2 = 50;    
    springWidthCount3 = 100;
    
    letterPoints_0[0] = new PVector( -50,  50 );
    letterPoints_0[1] = new PVector( -50,  250 );
    letterPoints_0[2] = new PVector( 0, 200 );
    letterPoints_0[3] = new PVector( 0,  0 );

    letterPoints_1[0] = new PVector( 0, 200 );
    letterPoints_1[1] = new PVector( -50, 250 );
    letterPoints_1[2] = new PVector( 50, 250 );
    letterPoints_1[3] = new PVector( 100, 200 );
   
    letterPoints_2[0] = new PVector( 50, 50 );
    letterPoints_2[1] = new PVector( 50, 200 );
    letterPoints_2[2] = new PVector( 100, 200 );
    letterPoints_2[3] = new PVector( 100, 0 );
}

void draw() {
    noStroke();

    rectMode(CORNER);
    fill( colors[0], 120 );
    rect(0, 0, width, height);
    scale( width * 0.00195 );
    pushMatrix();
        translate( 210, 20 );
        scale(1.8);
        fill(colors[1]);
        pushMatrix();
            beginShape(QUADS);
            for(int i = 0; i<4; i++){
                vertex( letterPoints_0[i].x, letterPoints_0[i].y );
            }
            endShape();
        popMatrix();
        

        fill( colors[2] );
        beginShape(QUADS);
        for(int i = 0; i<4; i++){
            vertex( letterPoints_2[i].x, letterPoints_2[i].y );
        }
        endShape();
        
        fill( colors[3] );        
        beginShape(QUADS);
        for(int i = 0; i<4; i++){
            vertex( letterPoints_1[i].x, letterPoints_1[i].y );
        }
        endShape();
    popMatrix();
    
    for(int i=0; i < 2; i ++ ){
        letterPoints_0[2].y = 350 - springWidthCount3;
        letterPoints_0[3].y = 150 - springWidthCount3;
        letterPoints_0[2].x = -150 + springWidthCount3;
        letterPoints_0[3].x = -150 + springWidthCount3;
        
        letterPoints_2[i].x =  150 - springWidthCount - 50;
        letterPoints_2[0].y =   0 + springWidthCount;
        
        letterPoints_1[2].x = -150 + springWidthCount2*2;
        letterPoints_1[3].x = -100 + springWidthCount2*2;
    }
        
    counter += 1;
    if( 50 == counter ){ changeColor(); };
    if( 400 > counter && counter >= 100 ){
        if(counter >= 120){
            nextPos = 50;
            if(counter >= 130){
                nextPos2 = 100;
                if(counter >= 140){
                    nextPos3 = 150;
                }
            }
        }
        
    } else if( 400 <= counter &&  counter >= 100 ){
        nextPos3 = 100;
        if(counter >= 410){
            nextPos2 = 50;
            if(counter >= 420){
                nextPos = 0;
                counter = 0;
            }
        }
    }
    
    float ax;
    ax = (nextPos - currentPos) * spring;
    speed += ax;
    speed *= friction;
    currentPos += speed;
    
    float ax2;
    ax2 = (nextPos2 - currentPos2) * spring;
    speed2 += ax2;
    speed2 *= friction;
    currentPos2 += speed2;
    
    float ax3;
    ax3 = (nextPos3 - currentPos3) * spring;
    speed3 += ax3;
    speed3 *= friction;
    currentPos3 += speed3;
    
    springWidthCount = currentPos;
    springWidthCount2 = currentPos2;
    springWidthCount3 = currentPos3;
    
    if(keyPressed) {
        if (key == 's') {
            save("vimini.tif");
        }
    }
}

void changeColor(){
    color headColor;
    headColor = colors[0];
    for(int i = 0; i < colors.length() - 1; i++){
        colors[i] = colors[i+1];
    }
    colors[colors.length()-1] = headColor;
}