import promidi.*;
MidiIO midiIO;

//PrintWriter output;
//BufferedReader reader;
String trace;
PGraphics bg, fillBg;

// MIDI Controll Data
ArrayList<String> xRotateMidi = new ArrayList<String>();
ArrayList<String> yRotateMidi = new ArrayList<String>();
ArrayList<String> zRotateMidi = new ArrayList<String>();
ArrayList<String> strokeHMidi = new ArrayList<String>();
ArrayList<String> strokeSMidi = new ArrayList<String>();
ArrayList<String> strokeBMidi = new ArrayList<String>();
ArrayList<String> bgAlphaMidi = new ArrayList<String>();
ArrayList<String> xDiffMidi = new ArrayList<String>();
ArrayList<String> yDiffMidi = new ArrayList<String>();
ArrayList<String> zDiffMidi = new ArrayList<String>();
ArrayList<String> scZMidi = new ArrayList<String>();
ArrayList<String> weightMidi = new ArrayList<String>();

//initial
int dpi = 72;
float width_mm = 910;
float height_mm = 550;
int  width_px = int(width_mm * 0.03937 * dpi);
int  height_px = int(height_mm * 0.03937 * dpi);

//Uniba logo
float radS = -PI/360*70;
float camZ = -3000 - 0.5 * 3000;
float scZ = -1000;
float xRotate = 0;
float yRotate = 0;
float zRotate = PI/2;
float weight = 0.5;
int strokeH = 0;
int strokeS = 255;
int strokeB = 255;
float bgAlpha = 100;

//Logo
int[][] logo = {
  // U
  {0,  0,  0,  0,200, 80},
  {0,  0,200,100,200, 80},
  {0,100,200,100,  0, 80},
  // N
  {1,200,200,200,  0, 80},
  {1,200,  0,300,  0, 80},
  {1,300,  0,300,200, 80},
  // I
  {2,400,  0,400,200, 80},
  // B
  {3,500,  0,500,300, 80},
  {3,500,300,600,200, 80},
  {3,600,200,600,100, 80},
  {3,600,100,500,100, 80},
  // A
  {4,700,  0,800,  0, 80},
  {4,800,  0,800,200, 80},
  {4,800,200,700,200, 80},
  {4,700,200,700,100, 80},
  {4,700,100,800,100, 80},
  // U-N
  {5,100,  0,200,200,  0},
  // N-I
  {6,300,200,400,  0,  0},
  // I-B
  {7,400,200,500,  0,  0},
  // B-A
  {8,500,100,700,  0,  0}
};
float xDiff = 0;
float yDiff = 0;
float zDiff = 0;

//Z
int zPitch = 20;

float[] randomPos = new float[logo.length*6];
int strokeHval = 10;
int strokeSval = 10;
int strokeBval = 10;

void setup()
{
  frameRate(30);
  colorMode(HSB);
  noFill();
  noSmooth();
  size(910, 550);
  background(255);
  
  midiIO = MidiIO.getInstance(this);
  midiIO.openInput(0, 0);
  
  for(int i=0; i<logo.length; i++){
    logo[i][1] -= 400;
    logo[i][2] -= 125;
    logo[i][3] -= 400;
    logo[i][4] -= 125;
  }
  
  bg = createGraphics(width, height, P2D);
  bg.beginDraw();
  bg.noFill();
  bg.rect(0, 0, width/1.9, height/1.9);
  bg.endDraw();
}

void draw()
{
  noStroke();
  fill(255, bgAlpha);
  rect(0,0,width,height);
  
  // Saving MIDI Control Data
  Float xRotateS = new Float(xRotate);
  xRotateMidi.add(xRotateS.toString());
  Float yRotateS = new Float(yRotate);
  yRotateMidi.add(yRotateS.toString());
  Float zRotateS = new Float(zRotate);
  zRotateMidi.add(zRotateS.toString());
  Float strokeHS = new Float(strokeH);
  strokeHMidi.add(strokeHS.toString());
  Float strokeSS = new Float(strokeS);
  strokeSMidi.add(strokeSS.toString());
  Float strokeBS = new Float(strokeB);
  strokeBMidi.add(strokeBS.toString());
  Float bgAlphaS = new Float(bgAlpha);
  bgAlphaMidi.add(bgAlphaS.toString());
  Float xDiffS = new Float(xDiff);
  xDiffMidi.add(xDiffS.toString());
  Float yDiffS = new Float(yDiff);
  yDiffMidi.add(yDiffS.toString());
  Float zDiffS = new Float(zDiff);
  zDiffMidi.add(zDiffS.toString());
  Float scZS = new Float(scZ);
  scZMidi.add(scZS.toString());
  Float weightS = new Float(weight);
  weightMidi.add(weightS.toString());
  
  for(int i=0; i<logo.length; i=i+1) {
    for(float j=0; j<=logo[i][5]; j=j+zPitch) {
      draw2dLine(logo[i][1]+xDiff,logo[i][2]+yDiff,logo[i][3]+xDiff,logo[i][4]+yDiff, j+zDiff, j+zDiff, xRotate, yRotate, zRotate);
    }
  }
  
  if (keyPressed == true)
  {
    if(key == 's'){
      
      int D = day();
      int M = month();
      int Y = year();
      int h = hour();
      int m = minute();
      int s = second();
      int c = millis();
      
      String stamp = Y + "_" + M  + "_" + D + "_" + h + "_" + m  + "_" + s + "_" + c;
      
      save("p5_" + stamp + ".tif");
      println("tif image saved");
      
    } else if (key == 'c') {
      
      image(bg, width/2-width/4, height/2-height/4);
    
    } else if (key == 'r') {
      
      // Saving MIDI Control Data
      String[] xRotateMidiS = xRotateMidi.toArray(new String[0]);
      String[] yRotateMidiS = yRotateMidi.toArray(new String[0]);
      String[] zRotateMidiS = zRotateMidi.toArray(new String[0]);
      String[] strokeHMidiS = strokeHMidi.toArray(new String[0]);
      String[] strokeSMidiS = strokeSMidi.toArray(new String[0]);
      String[] strokeBMidiS = strokeBMidi.toArray(new String[0]);
      String[] bgAlphaMidiS = bgAlphaMidi.toArray(new String[0]);
      String[] xDiffMidiS = xDiffMidi.toArray(new String[0]);
      String[] yDiffMidiS = yDiffMidi.toArray(new String[0]);
      String[] zDiffMidiS = zDiffMidi.toArray(new String[0]);
      String[] scZMidiS = scZMidi.toArray(new String[0]);
      String[] weightMidiS = weightMidi.toArray(new String[0]);

      saveStrings("xRotate.txt", xRotateMidiS);
      saveStrings("yRotate.txt", yRotateMidiS);
      saveStrings("zRotate.txt", zRotateMidiS);
      saveStrings("strokeH.txt", strokeHMidiS);
      saveStrings("strokeS.txt", strokeSMidiS);
      saveStrings("strokeB.txt", strokeBMidiS);
      saveStrings("bgAlpha.txt", bgAlphaMidiS);
      saveStrings("xDiff.txt", xDiffMidiS);
      saveStrings("yDiff.txt", yDiffMidiS);
      saveStrings("zDiff.txt", zDiffMidiS);
      saveStrings("weight.txt", weightMidiS);
      saveStrings("scZ.txt", scZMidiS);
      
    }
  }
  
}

void controllerIn(Controller nob, int deviceNumber, int midiChannel)
{  
  
    //println(nob.getNumber() +": " + nob.getValue());
    //output.println(nob.getNumber()+","+nob.getValue());
    
    // Stroke Weight
    if(nob.getNumber() == 20){
      weight = nob.getValue();
    }
    
    // Hue
    if(nob.getNumber() == 116){
      strokeH = nob.getValue()*2;
    }
    
    // Saturation
    if(nob.getNumber() == 117){
      strokeS = nob.getValue()*2;
    }
    
    // Brightness
    if(nob.getNumber() == 8){
      strokeB = nob.getValue()*2;
    }
    
    // RotateX
    if(nob.getNumber() == 118){
      xRotate = TWO_PI/127*nob.getValue();
    }
    
    // RotateY
    if(nob.getNumber() == 119){
      yRotate = TWO_PI/127*nob.getValue();
    }
    
    // RotateZ
    if(nob.getNumber() == 15){
      zRotate = TWO_PI/127*nob.getValue();
    }
    
    // Density
    if(nob.getNumber() == 9){
      zPitch = 400/nob.getValue();
    }
    
    // Background Alpha
    if(nob.getNumber() == 10){
      bgAlpha = 0.7874*nob.getValue();
      println("bgAlpha="+bgAlpha);
    }
    
    // X position
    if(nob.getNumber() == 16){
      xDiff = 10*nob.getValue() - 10*64;
    }
    
    // Y position
    if(nob.getNumber() == 17){
      yDiff = 10*nob.getValue() - 10*64;
    }
    
    // Z position
    if(nob.getNumber() == 18){
      zDiff = 10*nob.getValue() - 10*64;
    }
    
    // Smooth
    if(nob.getNumber() == 19){
      if( nob.getValue() < 64){
        smooth();
        println("smooth");
      } else {
        noSmooth();
        println("no smooth");
      }
    }
    
    // 
    if(nob.getNumber() == 13){
      if( nob.getValue() < 42) {
         strokeCap(ROUND);
         println("Round");
      } else if( nob.getValue() > 43 && nob.getValue() < 84 ) {
         strokeCap(SQUARE);
         println("Square");
      } else {
         strokeCap(PROJECT);
         println("Project");
      }
    }
    
    // Zoom
    if(nob.getNumber() == 14){
      scZ = -(5000/128)*(127-nob.getValue());
    }
 
}

void draw2dLine(float x1,float y1,float x2,float y2,float z1, float z2, float rx, float ry, float rz)
{
  //Y
  float z1cash = z1;
  float z2cash = z2;
  z1 = x1 * sin(ry) - z1cash * cos(ry);
  z2 = x2 * sin(ry) - z2cash * cos(ry);
  x1 = x1 * cos(ry) + z1cash * sin(ry);
  x2 = x2 * cos(ry) + z2cash * sin(ry);
  //X
  //float z1cash = z1;
  //float z2cash = z2;
  z1 = y1 * sin(rx) - z1cash * cos(rx);
  z2 = y2 * sin(rx) - z2cash * cos(rx);
  y1 = y1 * cos(rx) + z1cash * sin(rx);
  y2 = y2 * cos(rx) + z2cash * sin(rx);
  //Z
  float x1cash = x1;
  float x2cash = x2;
  float y1cash = y1;
  float y2cash = y2;
  x1 = x1 * sin(rz) + y1cash * cos(rz);
  x2 = x2 * sin(rz) + y2cash * cos(rz);
  y1 = y1 * sin(rz) - x1cash * cos(rz);
  y2 = y2 * sin(rz) - x2cash * cos(rz);
  //
  float x1b = width/2  + x1 * (camZ + z1) * tan(radS/2) / (scZ + z1) * tan(radS/2);
  float y1b = height/2 + y1 * (camZ + z1) * tan(radS/2) / (scZ + z1) * tan(radS/2);
  float x2b = width/2  + x2 * (camZ + z2) * tan(radS/2) / (scZ + z2) * tan(radS/2);
  float y2b = height/2 + y2 * (camZ + z2) * tan(radS/2) / (scZ + z2) * tan(radS/2);
  //
  translate(0,0);
  //
  stroke(strokeH, strokeS, strokeB);
  strokeWeight(weight);
  //
  line(x1b,y1b,x2b,y2b);
}
