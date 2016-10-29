//Project for Programming for Artists, Aalto Media Lab
//Sourya Sen 2016

import org.puredata.processing.*;
import cc.arduino.*;
import org.firmata.*;
import processing.serial.*;

Arduino myArduino;
PureData pd;

int pot0, pot1, pot2;

int pin;

int notein;
int velocityin;
int durationin;

int pot0_out;
int pot1_out;
int pot2_out;

int ledPin;

String teststring;
float testfloat;


void setup(){
  size(450, 200);
  
  printArray(Arduino.list());
  myArduino = new Arduino(this, Arduino.list()[1], 57600);
  
  pd = new PureData(this, 44100, 0, 2);
  pd.openPatch("ledSynth.pd");
  pd.subscribe("notein");
  pd.subscribe("velocityin");
  pd.subscribe("durationin");
  pd.start();

}

void draw(){
  //Reset all Leds to OFF
  for(int i = 0; i< 13; i++){
  myArduino.analogWrite(i, 0);
}
  
  //Reading the three potentiometers first
  pot0 = myArduino.analogRead(0);
  pot1 = myArduino.analogRead(2);
  pot2 = myArduino.analogRead(4);
  
  //Mapping the values for Pd
  pot0_out = int(map(pot0, 660, 0, 1, 6));
  pot1_out = int(map(pot1, 660, 0, 1, 6));
  pot2_out = int(map(pot2, 660, 0, 0, 90)); //this needs to be between 0-120
  
  //Sending the actual values which should make sounds
  pd.sendFloat("scaleRange", pot0_out);
  pd.sendFloat("tempoRange", pot1_out);
  pd.sendFloat("velocityRange", random(pot2_out));

  //Setting notes to corresponding pins
  switch (notein){
    case 55:
    pin = 3;
    break;
    
    case 57:
    pin = 5;
    break;
    
    case 59:
    pin = 6;
    break;
    
    case 62:
    pin = 9;
    break;
    
    case 64:
    pin = 10;
    break;
    
    case 67:
    pin = 11;
    break;
    
    default:
    pin = 13;
    break;
  }
  
  //Visualize on the Arduino
  myArduino.analogWrite(pin, int(velocityin*1.3));
  
  println(pot0, pot1, pot2);
  println(pot0_out, pot1_out, pot2_out);
  println(notein, durationin, velocityin);
  println(teststring, testfloat);
 
}


//PD RECEIVING STUFF

void receiveFloat(String source, float x) {
  
  teststring = source;
  testfloat = x;
  
  if (source.equals("notein")){
    notein = int(x);
  }
  else if (source.equals("durationin")){
    durationin = int(x);
  }
  else if (source.equals("velocityin")){
    velocityin = int(x);
  }
}