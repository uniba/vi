import processing.core.*; 
import processing.xml.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class scketch extends PApplet {

/*
1\u3001\u30c0\u30a4\u30ca\u30df\u30c3\u30af\uff08\u8272\u76f8\u5909\u5316\uff09
77/77/77
204/204/204
0/104/183
245/151/0

\uff12\u3001\u30ab\u30e9\u30d5\u30eb\uff08\u8272\u76f8\u5909\u5316\uff1f\uff09
217/217/217
199/95/91
242/156/159
255/246/26

\uff13\u3001\u6de1\u3044\uff08\u660e\u5ea6\u5909\u5316\uff1f\uff09
R: 255 G: 234 B: 240
R: 0 G: 187 B: 236
R: 44 G: 110 B: 213
R: 255 G: 252 B: 190

\uff14\u3001\u6e0b\u3044\uff08\u5f69\u5ea6\u5909\u5316\uff1f\uff09
R: 137 G: 201 B: 151
R: 253 G: 251 B: 222
R: 131 G: 106 B: 74
R: 209 G: 163 B: 87
*/

int counter;
int widthCount;
int widthCount2;

PVector[] letterPoints_0 = new PVector[4];
PVector[] letterPoints_1 = new PVector[4];
PVector[] letterPoints_2 = new PVector[4];

public void setup() {
    widthCount2 = 50;
    widthCount3 = 100;
    counter = 0;
    size(512, 512, P2D);
    background(77,77,77);
    
    
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

public void draw() {
    noStroke();

    rectMode(CORNER);
    fill(204);
    rect(0, 0, width, height);

    pushMatrix();
        translate( 210, 50 );
        scale(1.6f);
        fill(0,104,183);
        pushMatrix();
            beginShape(QUADS);
            for(int i = 0; i<4; i++){
                vertex( letterPoints_0[i].x, letterPoints_0[i].y );
            }
            endShape();
        popMatrix();
        
        fill(77);
        beginShape(QUADS);
        for(int i = 0; i<4; i++){
            vertex( letterPoints_2[i].x, letterPoints_2[i].y );
        }
        endShape();
        
        fill(245,151,9);
        beginShape(QUADS);
        for(int i = 0; i<4; i++){
            vertex( letterPoints_1[i].x, letterPoints_1[i].y );
        }
        endShape();
        

    popMatrix();
    
    for(int i=0; i <  2; i ++ ){
        letterPoints_0[2].y = 250 - widthCount;
        letterPoints_0[3].y = 50 - widthCount;
        letterPoints_0[2].x = -50 + widthCount;
        letterPoints_0[3].x = -50 + widthCount;
        
        letterPoints_2[i].x =  150 - widthCount - 50;
        letterPoints_2[0].y =   0 + widthCount;
        letterPoints_2[1].y =   200 + widthCount;
        
        letterPoints_1[2].x = -150 + widthCount2*2;
        letterPoints_1[3].x = -100 + widthCount2*2;

    }
        

    
    counter += 4;
    println(letterPoints_0[i].x);
    if(counter >  50){
        widthCount = 50;
        if(widthCount2 >= 100){
            widthCount2 = 100;
        }else {
            widthCount2 += 4;
        }
    }else{
        widthCount = counter ;
    };
    
    if(400 >= counter){
        counter = 0;
        widthCount = 0;
        widthCount2 = 0;
    }
}
int delnum = 100;
int[] cell = new int[delnum];
int rsize = 5;
int right=0;
int left=0;
int size = 0;
 
public void setup() {
  size(500, 1000);
  background(255);
  for (int i=0; i<delnum; i++) {
    cell[i] = PApplet.parseInt(random(0, 2));
  }
}
 
public void draw() {
  drawCells(cell, size);
  for (int i=0; i<delnum; i++) {
    if (i == 0) {
      left = delnum - 1;
      right = i + 1;
    } else if (i == 99) {
      left = i - 1;
      right = 0;
    } else {
      left = i - 1;
      right = i + 1;
    }
    if (cell[i] == 0) {
      deadecell(i);
    }
    if (cell[i] == 1) {
      alivecell(i);
    }
  }
  size = size + 5;
}
 
public void drawCells(int[] cells, int size) {
  for (int i=0; i<delnum; i++) {
    fill(0);
    if (cells[i] == 0) {
      fill(255);
    }
    rect(i*5, size, rsize, rsize);
  }
}
 
public void deadecell(int i) {
  if (cell[left] == 1 && cell[right] == 1) {
    cell[i] = 0;
  } else if (cell[left] == 1 && cell[right] == 0 || cell[left] == 0 && cell[right] == 1){
    cell[i] = 1;
  } else if (cell[left] == 0 && cell[right] == 0) {
    cell[i] = 0;
  }
}
 
public void alivecell(int i){
  if (cell[left] == 1 && cell[right] == 1) {
    cell[i] = 0;
  } else if (cell[left] == 1 && cell[right] == 0 ) {
    cell[i] = 0;
  } else if (cell[right] == 1 && cell[left] == 0) {
    cell[i] = 1;
  } else if (cell[left] == 0 && cell[right] == 0) {
    cell[i] = 1;
  }
}
  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#c0c0c0", "scketch" });
  }
}
