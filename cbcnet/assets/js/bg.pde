// Window Size
int ww;
int wh;

// Color
color[] divideRectColors = new color[4];
// Default Value
divideRectColors[0] = color(217, 217, 217);
divideRectColors[1] = color(199,  95,  91);
divideRectColors[2] = color(242, 156, 159);
divideRectColors[3] = color(255, 246,  26);

// Inner Circle
float divideAngleInner = TWO_PI * random();
float radiusInnerCircle = 100;
// Outer Circle
float divideAngleOuterA = TWO_PI * random();
float divideAngleOuterB = TWO_PI * random();
float radiusOuterCircle = 200;
float outerCircleCenterX;
float outerCircleCenterY;

void setup() {
  processingInitComplete();
  frameRate(30);
  noStroke();
}

void setStageSize(int windowWidth, int windowHeight, float windowScaleS) {
  size(windowWidth, windowHeight);
  windowScale = windowScaleS;
}

void setBgColor(int r, int g, int b, int s) {
  divideRectColors[s] = color(r, g, b);
}

void setSize(int w, int h) {
  ww = w;
  wh = h;
  size(ww, wh);
  radiusInnerCircle = wh / 2.5;
}

void updateBgAngle(float x, float y, float z) {
  divideAngleInner = abs(z);
  divideAngleOuterA = abs(x);
  divideAngleOuterB = abs(y);
}

void captureScreen() {
  save("background.png");
}

void draw() {
  background(divideRectColors[0]);
  
  divideAngleOuterB = divideAngleOuterB % PI;
  outerCircleCenterX = cos(divideAngleInner) * radiusInnerCircle + ww / 2;
  outerCircleCenterY = sin(divideAngleInner) * radiusInnerCircle + wh / 2;
  radiusOuterCircle = ww * 2;

  translate(outerCircleCenterX, outerCircleCenterY);
  rotate(divideAngleOuterA);

  fill(divideRectColors[0]);
  arc(0, 0, radiusOuterCircle, radiusOuterCircle, 0, divideAngleOuterB);
  
  fill(divideRectColors[1]);
  arc(0, 0, radiusOuterCircle, radiusOuterCircle, divideAngleOuterB, PI);
  
  fill(divideRectColors[2]);
  arc(0, 0, radiusOuterCircle, radiusOuterCircle, PI, divideAngleOuterB + PI);
    
  fill(divideRectColors[3]);  
  arc(0, 0, radiusOuterCircle, radiusOuterCircle, divideAngleOuterB + PI, TWO_PI);
}