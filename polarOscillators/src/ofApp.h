#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "MyOscillator.h"
#include "nlMap.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    // Audio output and input methods
    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    //Audio Stuff
    
    int		bufferSize;
    int		sampleRate;
    
    double finalWave;
    
    //Utils
    
    int counter;
    bool hud;
    
    //Individual Oscillators
    
    vector<MyOscillator> oscillator;
    
    //Visualization Stuff
    vector<float> masterDrawBuffer;
    float spacing;
    
    float theta_rad, theta_deg;
    float dist;
    
    float nearestDistance;
};
