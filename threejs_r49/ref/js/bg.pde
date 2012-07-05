PVector[] dividePoint = new PVector[4];
PVector divideCrossPoint = new PVector;
color[] divideRectColors = new color[4];

divideRectColors[0] = color(217, 217, 217);
divideRectColors[1] = color(199,  95,  91);
divideRectColors[2] = color(242, 156, 159);
divideRectColors[3] = color(255, 246,  26);

void setup() {
  processingInitComplete();
  frameRate(30);
  for (int i = 0; i < 4; i++) {
    //float angle = HALF_PI * i;
    //float radius = ww / sqrt(2.0);
    //PVector calVect = PVector(radius / sqrt(2.0), radius / sqrt(2.0));
    //calVect = rotate(calVect, 0, 0, angle);
    //calVect += PVector(ww / 2, wh / 2);
    PVector v = new PVector;
    v.x = round(random(ww));
    v.y = round(random(wh));
    dividePoint[i] = v;
  }
  divideCrossPoint.x = round(random(ww));
  divideCrossPoint.y = round(random(wh));
}

void setStageSize(int windowWidth, int windowHeight, float windowScaleS) {
  size(windowWidth, windowHeight);
  windowScale = windowScaleS;
}

void setBgColor(int r, int g, int b, int s) {
  divideRectColors[s] = color(r, g, b);
}

void setSize(int ww, int wh) {
  size(ww, wh);
}

void draw() {
  background(divideRectColors[0]);
  
  for (int i = 0; i < 4; i++){
    noStroke();
    colorMode(RGB);
    stroke(divideRectColors[i]);
    fill(divideRectColors[i]);
    beginShape();
    if (i == 3) {
      vertex(dividePoint[i].x, dividePoint[i].y);
      vertex(divideCrossPoint.x, divideCrossPoint.y);
      vertex(dividePoint[0].x, dividePoint[0].y);
    } else {
      vertex(dividePoint[i].x, dividePoint[i].y);
      vertex(divideCrossPoint.x, divideCrossPoint.y);
      vertex(dividePoint[i + 1].x, dividePoint[i + 1].y);
    }
    switch (i) {
      case 0:
        vertex(0, wh);
        break;
      case 1:
        vertex(0, 0);
        break;
      case 2:
        vertex(ww, 0);
        break;
      case 3:
        vertex(ww, wh);
        break;
    }
    endShape(CLOSE);
  }
}