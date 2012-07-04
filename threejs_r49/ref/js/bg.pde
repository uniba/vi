int bgcolorR = 255;
int bgcolorG = 255;
int bgcolorB = 255;

void setup() {
  processingInitComplete();
    
  frameRate(30);
  colorMode(RGB);
  noSmooth();
  noFill();
}

void setStageSize(int windowWidth, int windowHeight, float windowScaleS) {
  size(windowWidth, windowHeight);
  windowScale = windowScaleS;
}

void setBgColor(int r, int g, int b) {
  bgcolorR = r;
  bgcolorG = g;
  bgcolorB = b;
}

void setSize(int ww, int wh) {
  size(ww, wh);
}

void draw() {
  background(bgcolorR, bgcolorG, bgcolorB);
}