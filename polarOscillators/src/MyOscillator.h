#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "nlMap.h"

#define FREQ_MIN 45
#define FREQ_MAX 7500
#define LFO_MIN 0.1
#define LFO_MAX 20

#define NLMAP_FREQ 4
#define NLMAP_LFO 4

#define RADIUS 8

class MyOscillator{
public:
    
    //...Methods
    
    void setup(int _bufferSize);
    void update();
    void draw();
    void moveAlive();
    
    //...Variables
    
    ofPoint position;
    ofPoint targetPosition;
    float radius;
    float spacing;
    
    vector<double> drawBuffer;
    
    double wave;
    
    maxiOsc oscillator;
    maxiOsc lfo;
    
    float frequency;
    float lfoFrequency;
    int bufferSize;
    
    float posx, posy;
    
    bool isSelected;
    
    float theta_rad, theta_deg;
    float dist;
    
    bool isAlive;
    int refreshRate;
};

//--------------------------------EOF
