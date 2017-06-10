#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    
    ofSetBackgroundColor(255);
    
    bufferSize = 1024;
    sampleRate = 44100;
    
    gui.setup();
    gui.add(frequency.setup("Frequency", 440, 20, 20000));
    gui.add(ratio.setup("Ratio", 0, 0, 20));
    gui.add(index.setup("Index", 0, 0, 100));
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    drawBuffer.resize(bufferSize);
    
    ofSoundStreamSetup(2, 2, this, sampleRate, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    float spacing = 360.00/float(drawBuffer.size());
    
    ofSetColor(0, 0, 0);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    float x, y;
    
    for(int i = 0; i<drawBuffer.size(); i++){
        
        x = 200 * cos(i*spacing) * drawBuffer[i];
        y = 200 * sin(i*spacing) * drawBuffer[i];
        
        ofDrawCircle(x, y, 2);
    }

}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    
    for(int i = 0; i<bufferSize; i++){
        counter++;
        
        double myOutput = oscillator.sinewave(frequency + (modulator.sinewave(ratio*frequency)*index));
        
        output[i*nChannels] = myOutput;
        output[i*nChannels + 1] = myOutput;
        
        drawBuffer[counter%bufferSize] = myOutput;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
