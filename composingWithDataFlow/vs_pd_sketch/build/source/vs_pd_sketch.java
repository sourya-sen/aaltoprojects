import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import oscP5.*; 
import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class vs_pd_sketch extends PApplet {





//Defining global OSC incoming streams here

int counter;
int pdmaster;
int pdfeedback;
int pdkick;
int pdsnare;
int pdhat;
int pdsynth;
int snare;
int chords;
int countercontrol;

float r;
float g;
float b;

float x;
float y;

float rx = 0;
float ry = 0;

float _r = 100;
int hold = 0;

float[] glitchx = new float[100];
float[] glitchy = new float[100];
float[] glitchw = new float[100];
float[] glitchh = new float[100];
float[] glitcha = new float[100];

char keychar = '1';

//Pattern Selector

public void keyReleased(){
  if (key >= '0' && key <= '9') {
    keychar = key;
    background(0);
  }
  if ((key == 'w') || (key == 'W')) {
    background(0);
  }
}


//Defining OSC

OscP5 oscP5;
NetAddress myRemoteLocation;

public void setup(){
  
  frameRate(12);

  oscP5=new OscP5(this, 1390);
  myRemoteLocation = new NetAddress("172.0.0.1", 1390);
}






public void draw(){

  //Pattern Selector
  //
  switch(keychar) {
  case '1':
    pattern01();
    glitch();
    break;

  case '2':
    pattern02();
    rEllipse(255, 255, 0);
    glitch();
    break;

  case '3':
    pattern03();
    rEllipse(0, 255, 0);
    glitch();
    break;

  case '4':
    pattern04();
    rEllipse(255, 0, 0);
    glitch();
    break;

  case '5':
    pattern05();
    rEllipse(0, 255, 255);
    glitch();
    break;

  case '6':
    pattern06();
    rEllipse(255, 255, 0);
    glitch();
    break;

  case '7':
    pattern07();
    rEllipse(0, 255, 255);
    glitch();
    break;

  case '8':
    pattern08();
    rEllipse(255, 0, 0);
    glitch();
    break;

  case '9':
    pattern09();
    rEllipse(255, 0, 255);
    glitch();
    break;

  case '0':
    pattern00();
    rEllipse(255, 255, 0);
    glitch();
    break;
  }


  //FOLLOWING FOR STROBE

  if (keyPressed) {
    if ((key == 'b') || (key=='B')) {
      rectMode(RADIUS);
      fill(0);
      rect(width/2, height/2, width, height);
    }
    if ((key == 'w') || (key == 'W')) {
      rectMode(RADIUS);
      fill(255);
      rect(width/2, height/2, width, height);
    }
  }


}


//OSC INCOMING STREAMS BELOW!

public void oscEvent(OscMessage theOscMessage){

  if(theOscMessage.checkAddrPattern("/counter")==true){
    if(theOscMessage.checkTypetag("i")){
      counter = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdmaster")==true){
    if(theOscMessage.checkTypetag("i")){
      pdmaster = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdfeedback")==true){
    if(theOscMessage.checkTypetag("i")){
      pdfeedback = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdkick")==true){
    if(theOscMessage.checkTypetag("i")){
      pdkick = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdsnare")==true){
    if(theOscMessage.checkTypetag("i")){
      pdsnare = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdhat")==true){
    if(theOscMessage.checkTypetag("i")){
      pdhat = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/pdsynth")==true){
    if(theOscMessage.checkTypetag("i")){
      pdsynth = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/counter")==true){
    if(theOscMessage.checkTypetag("i")){
      counter = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/snaregain")==true){
    if(theOscMessage.checkTypetag("i")){
      snare = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/chordsgain")==true){
    if(theOscMessage.checkTypetag("i")){
      chords = theOscMessage.get(0).intValue();
      return;
    }
  }

  if(theOscMessage.checkAddrPattern("/countercontrol")==true){
    if(theOscMessage.checkTypetag("i")){
      countercontrol = theOscMessage.get(0).intValue();
      return;
    }
  }

}


//ALL PATTERNS GO BELOW

//PATTERN01
public void pattern01() {
  customBackground(0);
  colour();
  float rAlpha = 200 + srandom(-75, 75);
  if ((counter==1) || (counter==3)){
    ellipseMode(CENTER);
    fill(r, g, b, rAlpha);
    float r = 200;
    float randomr = r + srandom(0, 100);
    ellipse(width/2, height/2, randomr, randomr);
  }
}

//PATTERN02
public void pattern02() {
  customBackground(0);
  colour();
  rectMode(CENTER);
  noStroke();
  float w = 5 + srandom(-2, 2);
  float rAlpha = 180 + srandom(-75, 75);
  fill(r, g, b, rAlpha);
  if (counter==1){
    rect(width/2, height/2 + srandom(-5, 5), w, (height-20));
   }
  else if(counter==2){
    rect((width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
    rect((width/2)+(width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
  }
  else if(counter==3){
    rect(width/2, height/2 + srandom(-5, 5), w, (height-20));
    rect((width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
    rect((width/2)+(width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
  }
  else if(counter==4){
    rect((width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
    rect((width/2)+(width/2)/2, height/2 + srandom(-5, 5), w, (height-20));
    rect(0+10, height/2 + srandom(-5, 5), w, (height-20));
    rect(width-10, height/2 + srandom(-5, 5), w, (height-20));
  }
}

//PATTERN03
public void pattern03() {
  customBackground(0);
  colour();
  rectMode(CENTER);
  noStroke();
  float w = 5 + srandom(-2, 2);
  float rAlpha = 180 + srandom(-75, 75);
  fill(r, g, b, rAlpha);

  if (counter == 1){
    rect(width/2 + srandom(-5, 5), 10 + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), (height/2)/2 + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), (height/2) + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), height/2 + (height/2)/2 + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), height - 10 + srandom(-5, 5), (width - 20), w);
  }

  if (counter == 2){
    rect(width/2 + srandom(-5, 5), (height/2)/2 + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), height/2 + (height/2)/2 + srandom(-5, 5), (width - 20), w);
  }

  if (counter == 3){
    rect(width/2 + srandom(-5, 5), (height/2) + srandom(-5, 5), (width - 20), w);
  }

  if (counter == 4){
    rect(width/2 + srandom(-5, 5), (height/2)/2 + srandom(-5, 5), (width - 20), w);
    rect(width/2 + srandom(-5, 5), height/2 + (height/2)/2 + srandom(-5, 5), (width - 20), w);
  }
}

//PATTERN04
public void pattern04() {
 customBackground(0);
 colour();
 rectMode(CENTER);
 noStroke();
 float w = 5 + srandom(-2, 2);
 float rAlpha = 180 + srandom(-75, 75);
 fill(r, g, b, rAlpha);

 if (counter == 1){
   rect(width/2, height/2 + srandom(-5, 5), w, height - 20);
   rect(width/2 - (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);
   rect(width/2 + (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);

   rect(width/2, height/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 - (height/2)/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 + (height/2)/2 + srandom(-5, 5), width - 20, w);
 }

if (counter == 2){
   rect(width/2, height/2 + srandom(-5, 5), w, height - 20);
   //rect(width/2 - (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);
   //rect(width/2 + (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);

   //rect(width/2, height/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 - (height/2)/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 + (height/2)/2 + srandom(-5, 5), width - 20, w);
 }

 if (counter == 3){
   //rect(width/2, height/2 + srandom(-5, 5), w, height - 20);
   rect(width/2 - (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);
   rect(width/2 + (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);

   rect(width/2, height/2 + srandom(-5, 5), width - 20, w);
   //rect(width/2, height/2 - (height/2)/2 + srandom(-5, 5), width - 20, w);
   //rect(width/2, height/2 + (height/2)/2 + srandom(-5, 5), width - 20, w);
 }

 if (counter == 4){
   rect(width/2, height/2 + srandom(-5, 5), w, height - 20);
   //rect(width/2 - (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);
   //rect(width/2 + (width/2)/2, height/2 + srandom(-5, 5), w, height - 20);

   //rect(width/2, height/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 - (height/2)/2 + srandom(-5, 5), width - 20, w);
   rect(width/2, height/2 + (height/2)/2 + srandom(-5, 5), width - 20, w);
 }
}

//PATTERN05
public void pattern05(){
  //hold=0;
  customBackground(0);
  colour();
  int step = 20;
  strokeWeight(4);
  float rAlpha = 180 + srandom(-75, 75);
  stroke(r, g, b, rAlpha);
  if (counter > 0){
    float lastx = -1;
    float lasty = -1;
      for(int y1=100; y1<=height; y1=y1+100){
      for(float x=0; x<=width; x=x+step){
        float y= height/2 + (srandom(-540, y1)/4);
        //float lasty=random(y1);
        line(x, y, lastx, lasty);
        lastx = x;
        lasty = y;
      }
  }
  }
}

//PATTERN06
public void pattern06(){
  customBackground(0);
  colour();
  int step = 20;
  strokeWeight(4);
  float rAlpha = 180 + srandom(-75, 75);
  stroke(r, g, b, rAlpha);

 if(counter==1){
 for(int y1=100; y1<=height; y1=y1+100){
    for(float x=0; x<=width; x=x+step){
      float y=height/2 + (srandom(-540, y1) * 0.5f);
      float lasty=height/2 + (srandom(-540, y1) * 0.5f);
      line(x, y, x+step, lasty);
      }
 }
 for (int i=0; i<height; i+=30){
 line(0, i, width, i);
 }
 }

 if(counter==2){
 for(int y1=100; y1<=height; y1=y1+100){
    for(float x=0; x<=width; x=x+step){
      float y=height/2 + (srandom(-540, y1) * 0.5f);
      float lasty=height/2 + (srandom(-540, y1) * 0.5f);
      line(x, y, x+step, lasty);
      }
 }
 for (int i=0; i<height; i+=90){
 line(0, i, width, i);
 }
 }

 if(counter==3){
 for(int y1=100; y1<=height; y1=y1+100){
    for(float x=0; x<=width; x=x+step){
      float y=height/2 + (srandom(-540, y1) * 0.5f);
      float lasty=height/2 + (srandom(-540, y1) * 0.5f);
      line(x, y, x+step, lasty);
      }
 }
 for (int i=0; i<height; i+=180){
 line(0, i, width, i);
 }
 }

 if(counter==4){
 for(int y1=100; y1<=height; y1=y1+100){
    for(float x=0; x<=width; x=x+step){
      float y=height/2 + (srandom(-540, y1) * 0.5f);
      float lasty=height/2 + (srandom(-540, y1) * 0.5f);
      line(x, y, x+step, lasty);
      }
 }
 for (int i=0; i<height; i+=90){
 line(0, i, width, i);
 }
 }
}

//PATTERN07
public void pattern07(){
  customBackground(0);
  noStroke();
  colour();
}

//PATTERN08
public void pattern08(){
  customBackground(0);
  noStroke();
  colour();
}

//PATTERN09
public void pattern09(){
  customBackground(0);
  noStroke();
  colour();
}

//PATTERN10
public void pattern00(){
  customBackground(0);
  noFill();
  strokeWeight(1);
  stroke(0xffFFFFFF);
  beginShape();

  for(float i=0; i<=361; i++){
    float angle = i;
    float theta = radians(angle);
    float r = 200 + (10 + srandom(10, _r));
    float x= width/2 + (r*cos(theta));
    float y = height/2 + (r*sin(theta));

    curveVertex(x,y);

    _r+=.1f;

  }
  endShape(CLOSE);
}

//
//ADDITIONAL STUFF!
//

//FG GLITCHER
public void glitch(){
  if(snare+pdfeedback>1){
  for(int i=0; i<((snare/2)+(pdfeedback/2)); i++){
    rectMode(CENTER);
    noStroke();

    fill(92, 25, 35, random(200+snare));
    rect(glitchx[i+1], glitchy[i+1], glitchw[i+1], glitchh[i+1]);
  }
  for(int i=0; i<11; i++){
    fill(92, 25, 35, 180);
    rect((glitchx[i*5]), glitchy[i*5], glitchh[i]*2, glitchh[i]*2);
  }
  }
}


//COLOURIZER WITH CHORDS
public void colour(){

  if (chords>0){
    r = random(chords)+100;
    g = random(chords)+100;
    b = random(chords)+100;
  }

  else {
    r = 255;
    g = 255;
    b = 255;
}
}


//CUSTOM RANDOMZIER CONNECTED TO ARPEGGIATOR
public float srandom(float i, float j){
  float synv = norm (pdsynth, 0, 100);
  float nFeed = norm (pdfeedback, 0 , 100);
  if (nFeed>1){
    float newRandom = (random(i, j) * synv * nFeed);
    return newRandom;}
  else{
    float newRandom = (random(i, j) * synv * 2);
    return newRandom;
}
}

//RANDOM POSITION GENERATOR FOR THE CIRCLES
public void randomx(){
  if ((counter==1)&&(countercontrol>0)){
    rx=random(width);
  }
}

public void randomy(){
  if ((counter==1)&&(countercontrol>0)){
    ry=random(height);
  }
}

//THE ACTUAL CIRCLES
public void rEllipse(float cr, float cg, float cb){
  randomx();
  randomy();
  noStroke();
  fill(cr, cg, cb, 255);
  ellipse(rx, ry, 100, 100);
}

//CUSTOM GLITCHY BACKGROUND THINGY
public void customBackground(float c){
  background(c);
  rectMode(CENTER);
  noStroke();
  fill(115, 26, 43, 255);
  rect(width/2, height/2, width, height);
  bgGlitch();
}

//BG GLITCH ATTRIBUTES GENERATOR
public void glitchGenerate(){
  if((counter==1)&&(countercontrol>0)){
    for(int i=0; i<glitchx.length; i++){
      glitchx[i]=random(width);
      glitchy[i]=random(height);
      glitchw[i]=random(width);
      glitchh[i]=random(20);
      glitcha[i]=random(180);
    }
  }
  else if (snare>0){
    for(int i=0; i<glitchx.length; i++){
      glitchx[i]=random(width);
      glitchy[i]=random(height);
      glitchw[i]=random(width);
      glitchh[i]=random(20);
      glitcha[i]=random(180);
    }
  }
}

//CUSTOM GLITCHES DETAILS
public void bgGlitch(){
  glitchGenerate();
    for(int i = 0; i<50; i++){
    fill(92, 25, 35, glitcha[i]);
    rect(glitchx[i], glitchy[i], glitchw[i], glitchh[i]);
    }
    for(int i = 0; i<20; i++){
    fill(92, 25, 35, glitcha[i]);
    rect(glitchx[i+10], glitchy[i+10], glitchh[i]*3, glitchh[i]*3);
    }
}
  public void settings() {  size(960, 540); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--hide-stop", "vs_pd_sketch" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
