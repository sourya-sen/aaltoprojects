#pragma once

#include "ofxiOS.h"
#include "ofxMaxim.h"

#include "senButton.hpp"
#include "senSlider.hpp"

class ofApp : public ofxiOSApp {
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);

    int bufferSize;
    
    vector<float> mtof;

    int counter;
    
    double test;
    
    //Stuff for Clock.
    senButton clockSwitch;
    senSlider clockTempo;
    ofColor clockColor;
    maxiClock clock;
    
    //Stuff for FM.
    vector<float> fmBuffer;
    senButton fmSwitch;
    senButton fmTrigger;
    senButton fmClockSource;
    senSlider fmFrequency, fmIndex, fmRatio;
    
    maxiOsc oscillator;
    maxiOsc modulator;
    maxiOsc lfo;
    
    //Stuff for Envelop.
    senSlider enAttack, enDecay, enSustain, enRelease;
    maxiEnv envelop;
    double volume;
    
    //Stuff for Pads.
    vector<senButton> padButtons;
    
    //Stuff for filter;
    senSlider filterFreq, filterMix;
    maxiFilter filter;
    vector<float> filWetBuffer;
    vector<float> filOutBuffer;
    
    //Sutff for FX;
    senSlider dlSize, dlFeedback, dlMix;
    maxiDelayline delay;
    vector<float> dlLineBuffer;
    vector<float> dlMixBuffer;
    
    //Stuf for Algo
    //.............
    
    //Stuff for Final Out
    senButton amSwitch;
    senSlider amMag;
    vector<float> finalWaveBuffer;
    
    //Setup Constants here.
    ofVec2f clockPos;
    float clockWidth, clockHeight;
    
    ofVec2f fmPos;
    float fmWidth, fmHeight;
    
    ofVec2f enPos;
    float enWidth, enHeight;
    
    ofVec2f algoPos;
    float algoWidth, algoHeight;
    
    ofVec2f padPos;
    float padWidth, padHeight;
    
    ofVec2f filterPos;
    float filterWidth, filterHeight;
    
    ofVec2f fxPos;
    float fxWidth, fxHeight;
    
    ofVec2f fwPos;
    float fwWidth, fwHeight;
    
};


