//Teensy Algorythmic Attention Seeking Sequencer
//Sourya Sen, 2016
//Project for Physical Interaction Design, Aalto Media Lab, December 2016.

#include <ResponsiveAnalogRead.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=97.88888888888889,233.55555555555554
AudioSynthWaveform       waveform1;      //xy=116.6666259765625,108.33333396911621
AudioSynthWaveformSineModulated sine_fm3;       //xy=311.2222137451172,242.44441413879395
AudioSynthWaveformSineModulated sine_fm4;       //xy=311.2222213745117,286.88890647888184
AudioSynthWaveformSineModulated sine_fm2;       //xy=332.5555191040039,198.3333282470703
AudioSynthWaveformSineModulated sine_fm1;       //xy=333.6666259765625,156.3333339691162
AudioEffectEnvelope      envelope4;      //xy=462.44441986083984,286.77778911590576
AudioEffectEnvelope      envelope3;      //xy=463.4444580078125,242.00000762939453
AudioEffectEnvelope      envelope1;      //xy=482.6666259765625,156.3333339691162
AudioEffectEnvelope      envelope2;      //xy=484.8888282775879,198.33331489562988
AudioMixer4              mixer1;         //xy=661.6666259765625,195.3333339691162
AudioEffectDelay         delay1;         //xy=795.6666374206543,198.66666412353516
AudioSynthNoisePink      noise1;         //xy=799.4444427490234,303.7777738571167
AudioMixer4              mixer2;         //xy=1000.2222213745117,236.8888874053955
AudioOutputI2S           i2s1;           //xy=1093.333293914795,376.5555696487427
AudioConnection          patchCord1(waveform2, sine_fm3);
AudioConnection          patchCord2(waveform2, sine_fm4);
AudioConnection          patchCord3(waveform1, sine_fm1);
AudioConnection          patchCord4(waveform1, sine_fm2);
AudioConnection          patchCord5(sine_fm3, envelope3);
AudioConnection          patchCord6(sine_fm4, envelope4);
AudioConnection          patchCord7(sine_fm2, envelope2);
AudioConnection          patchCord8(sine_fm1, envelope1);
AudioConnection          patchCord9(envelope4, 0, mixer1, 3);
AudioConnection          patchCord10(envelope3, 0, mixer1, 2);
AudioConnection          patchCord11(envelope1, 0, mixer1, 0);
AudioConnection          patchCord12(envelope2, 0, mixer1, 1);
AudioConnection          patchCord13(mixer1, delay1);
AudioConnection          patchCord14(delay1, 0, mixer2, 0);
AudioConnection          patchCord15(delay1, 1, mixer2, 1);
AudioConnection          patchCord16(delay1, 2, mixer2, 2);
AudioConnection          patchCord17(noise1, 0, mixer2, 3);
AudioConnection          patchCord18(mixer2, 0, i2s1, 0);
AudioConnection          patchCord19(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=434.99996185302734,37.77777576446533
// GUItool: end automatically generated code


//OTHER STUFF------------------------------------------------------------
const int ANALOG_PIN01 = A3;
const int ANALOG_PIN02 = A2;

ResponsiveAnalogRead analog1(ANALOG_PIN01, true);
ResponsiveAnalogRead analog2(ANALOG_PIN02, true);

int notevalue;
int note;
float freq;

int basenote = 0;
int prevBase = basenote;

int range = 1;
int prevRange = range;

float midi[128];

unsigned long previousMillis = 0;
unsigned long previousMillisPlay = 0;
unsigned long interval = 1000;
unsigned long playInterval = 500;

int playInt[7] = {1000, 500, 500, 500, 500, 250, 250};

unsigned long idleTime = 0;
unsigned int idleTrigger = 8;

int chance;
int threshold = 8;

int ledPin = 8;


bool attention = true;
bool buttonstate;

//SYNTH STUFF THAT ARE VARS
float lfoFreq1 = 2;
float lfoFreq2 = 2;

float mix1_0 = 0.60;
float mix1_1 = 0.20;
float mix1_2 = 0.10;
float mix1_3 = 0.10;

float mix2_0 = 0.40;
float mix2_1 = 0.20;
float mix2_2 = 0.10;
float mix2_3 = 0.00;


//SETUP FOLLOWS-----------------------------------------------------------
//------------------------------------------------------------------------


void setup() {
  Serial.begin(9600);

//PINS INIT HERE----------------------------------------------------------
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(5, INPUT_PULLUP);

//AUDIO CODE INIT HERE----------------------------------------------------
  AudioMemory(16);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.3);
  waveform1.frequency(lfoFreq1);

  waveform2.begin(WAVEFORM_SQUARE);
  waveform2.amplitude(0.2);
  waveform2.frequency(lfoFreq2);

  sine_fm1.amplitude(.3);
  sine_fm2.amplitude(.4);
  sine_fm3.amplitude(.6);
  sine_fm4.amplitude(.6); 

  envelope1.attack(10);
  envelope1.hold(10);
  envelope1.decay(30);
  envelope1.sustain(.7);
  envelope1.release(100);

  envelope2.attack(10);
  envelope2.hold(5);
  envelope2.decay(10);
  envelope2.sustain(.5);
  envelope2.release(50);

  envelope1.attack(10);
  envelope1.hold(15);
  envelope1.decay(15);
  envelope1.sustain(.4);
  envelope1.release(80);

  envelope2.attack(12);
  envelope2.hold(12);
  envelope2.decay(25);
  envelope2.sustain(.3);
  envelope2.release(75);

  mixer1.gain(0, mix1_0);
  mixer1.gain(1, mix1_1);
  mixer1.gain(2, mix1_2);
  mixer1.gain(3, mix1_3);

  delay1.delay(1, 0);
  delay1.delay(2, 5);
  delay1.delay(3, 15);

  mixer2.gain(0, mix2_0);
  mixer2.gain(1, mix2_1);
  mixer2.gain(2, mix2_2);
  mixer2.gain(3, mix2_3);
  
  noise1.amplitude(.02);

  sgtl5000_1.audioPostProcessorEnable();
  sgtl5000_1.enhanceBassEnable();
  sgtl5000_1.enhanceBass(10, 2, 40, 1); 


//MIDI ARRAY CALCULATION//---------------------------------------------------------  
  for(int i=0; i<128; i++){
    midi[i] = 440.0/32.0 * (pow (2.0, ((i-9.0)/12.0)));
    //delay(100);
    //Serial.println(midi[i]);
    //delay(100);
  }

//RANDOM RANDOM
  randomSeed(analogRead(A9));  
  
}

//LOOP FOLLOWS----------------------------------------------------------------------
//----------------------------------------------------------------------------------

void loop() {
  unsigned long currentMillis = millis();

  analog1.update();
  analog2.update();
  buttonstate = digitalRead(5);

  attention = buttonstate;

  basenote = map(analog1.getValue(), 0, 1024, 24, 89);
  range = map(analog2.getValue(), 0, 1024, 1, 7);

  //CALCULATE IDLE STUFF-------------------------------------------------------------
  
  if (currentMillis - previousMillis >= interval){

    if ((prevBase == basenote) && (prevRange == range) && (attention)){
      idleTime ++;
    } else {
      resetAll();
    }

    if (idleTime>idleTrigger){
      chance++;
    } else {
      chance = 0;
    }

    if(chance>4){
      threshold = chance/4;
    } else {
      threshold = 1;
    }
    
    previousMillis = currentMillis;
  }

  //PLAYSTUFF---------------------------------------------------------------
    
 if (currentMillis - previousMillisPlay >= playInterval){

  notevalue = random(range);

   switch (notevalue) {
    case 0:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote;
    stableFunction();    
    }
    break;
    
    case 1:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote + 2;
    stableFunction();
    }
    break;
  
    case 2:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote + 4;
    stableFunction();
    }
    break;

    case 3:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote + 7;
    stableFunction();
    }
    break;

    case 4:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote + 9;
    stableFunction();
    }
    break;

    case 5:
    if(random(chance)>random(threshold)){
      idleFunction();
    } else {
    note = basenote + 12;
    stableFunction();
    }
    break;
    
  }

  freq = midi[note];
  
  sine_fm1.frequency(freq);
  sine_fm2.frequency(freq*2);
  sine_fm3.frequency(freq);
  sine_fm4.frequency(freq*3);

  envelope1.noteOn();
  envelope2.noteOn();
  envelope3.noteOn();
  envelope4.noteOn();  

  //DEBUG PRINT STUFF
//  Serial.print(mix2_3);
//  Serial.print("switch: ");
//  Serial.print(buttonstate);
//  Serial.print("\t");
//  Serial.print("Attention: ");
//  Serial.print(attention);
//  Serial.print("\t");
  Serial.print("Basenote: ");
  Serial.print(basenote);
  Serial.print("\t");
  Serial.print("Range: ");
  Serial.print(range);
  Serial.print("\t");
  Serial.print("Note: ");
  Serial.print(note);
  Serial.print("\t");
  Serial.print("Frequency: ");
  Serial.print(freq);
  Serial.print("\t");
  Serial.print("Idle: ");
  Serial.print(idleTime);
  Serial.print("\t");
  Serial.print("Chance: ");
  Serial.println(chance);

  playInterval = playInt[random(7)]; //Get new note duration
  previousMillisPlay = currentMillis;  //Reset play timer
 }

  if(currentMillis - previousMillisPlay == playInterval - 100){
    envelope1.noteOff();
    envelope2.noteOff();
    envelope3.noteOff();
    envelope4.noteOff();
 }
 
}

//RESET--------------------------------------------------------------------------------------

void resetAll(){
  idleTime = 0;
  prevBase = basenote;
  prevRange = range;
}

//IDLE-------------------------------------------------------------------------------------

void idleFunction(){
  note = random(24, 100);
  digitalWrite(ledPin, LOW);
  
  if(mix1_0 > 0.2){
    mix1_0 -= 0.025;
  }
  if(mix1_1 > 0.1){
    mix1_1 -= 0.025;
  }
  if(mix1_2 < 0.35){
    mix1_2 += 0.025;
  }
  if(mix1_3 < 0.35){
    mix1_3 += 0.025;
  }

  if(mix2_0 > 0.05){
    mix2_0 -= .025;
  }
  if(mix2_3 < 0.9){
    mix2_3 += .0125;
  }

  if(lfoFreq1<50){
  lfoFreq1+=.1;
  }
  if(lfoFreq2<50){
  lfoFreq2+=.1;
  }

  mixer1.gain(0, mix1_0);
  mixer1.gain(1, mix1_1);
  mixer1.gain(2, mix1_2);
  mixer1.gain(3, mix1_3);

  mixer2.gain(0, mix2_0);
  mixer2.gain(1, mix2_1);
  mixer2.gain(2, mix2_2);
  mixer2.gain(3, mix2_3);

  waveform1.frequency(lfoFreq1);
  waveform2.frequency(lfoFreq2);
}

//STABLE-------------------------------------------------------------------------------

void stableFunction(){
  digitalWrite(ledPin, HIGH);

  if(mix1_0 < 0.6){
    mix1_0 += 0.025;
  }
  if(mix1_1 < 0.2){
    mix1_1 += 0.025;
  }
  if(mix1_2 > 0.1){
    mix1_2 -= 0.025;
  }
  if(mix1_3 > 0.4){
    mix1_3 -= 0.025;
  }

  if(mix2_0 < 0.4){
    mix2_0 += 0.05;
  }
  if(mix2_3 >= 0.04){
    mix2_3 -= 0.05;
  } else if ((mix2_3 < 0.025) && (mix2_3 > 0.001)){
    mix2_3 = 0;
  }

  if(lfoFreq1>2.5){
    lfoFreq1 -= .5;
  } else if ((lfoFreq1>2) && (lfoFreq1<2.5)){
    lfoFreq1 = 2;
  }
  
  if(lfoFreq2>2.5){
    lfoFreq2 -= .5;
  } else if ((lfoFreq2>2) && (lfoFreq2<2.5)){
    lfoFreq2 = 2;
  }

  mixer1.gain(0, mix1_0);
  mixer1.gain(1, mix1_1);
  mixer1.gain(2, mix1_2);
  mixer1.gain(3, mix1_3);

  mixer2.gain(0, mix2_0);
  mixer2.gain(1, mix2_1);
  mixer2.gain(2, mix2_2);
  mixer2.gain(3, mix2_3);

  waveform1.frequency(lfoFreq1);
  waveform2.frequency(lfoFreq2);
}

//EOF-----------------------------------------------------------------------------------------------
 
