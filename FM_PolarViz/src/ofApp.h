#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void audioOut(float *output, int bufferSize, int nChannels);
    
    int bufferSize, sampleRate;
    
    vector<float> drawBuffer;
    int counter;
    
    maxiOsc oscillator;
    maxiOsc modulator;
    
    ofxFloatSlider frequency, ratio, index;
    ofxPanel gui;
    
//    float frequency, ratio, index;
		
};
