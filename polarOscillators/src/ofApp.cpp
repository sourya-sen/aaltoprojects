#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //---------------- ofApp Setup.
    
    ofSetFrameRate(60);
    ofSetWindowTitle("polarOscillators V0.1");
    ofSetEscapeQuitsApp(false);
    
    sampleRate 	= 44100;
    bufferSize	= 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
    ofBackground(25, 25, 25);
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    //--------------- Class Setup Happens Here.
    
    oscillator.resize(6);
    
    for(int i = 0; i<oscillator.size(); i++){
    oscillator[i].setup(bufferSize);
    }
    

    //--------------- Other Stuff/Utils for ofApp.
    
    counter = 0;
    hud = false;
    ofSeedRandom();
    
    //--------------- Master Visualization Setup.
    
    masterDrawBuffer.resize(bufferSize);
    for(int j = 0; j<masterDrawBuffer.size(); j++){
        masterDrawBuffer[j] = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //--------------- Updating all the oscillators. [and checking if they're too close to each other]
    for(int i = 0; i<oscillator.size(); i++){
        oscillator[i].update();
        
        for(int j=i+1; j<oscillator.size(); j++){
            if((ofDist(oscillator[i].targetPosition.x, oscillator[i].targetPosition.y, oscillator[j].targetPosition.x, oscillator[j].targetPosition.y)<25) && (oscillator[i].isSelected == false)){
                oscillator[i].targetPosition.x = ofRandomWidth();
                oscillator[i].targetPosition.y = ofRandomHeight();
                oscillator[j].targetPosition.x = ofRandomWidth();
                oscillator[j].targetPosition.y = ofRandomHeight();
            }
            if(ofDist(oscillator[i].position.x, oscillator[i].position.y, oscillator[j].position.x, oscillator[j].position.y)<25){
                oscillator[i].targetPosition.x = ofRandomWidth();
                oscillator[i].targetPosition.y = ofRandomHeight();
                oscillator[j].targetPosition.x = ofRandomWidth();
                oscillator[j].targetPosition.y = ofRandomHeight();
            }
        }
    }
    
    
    //--------------- Calculation of mouse coordinates for HUD.
    theta_rad = (atan2(mouseY - ofGetHeight()/2, mouseX - ofGetWidth()/2));
    float theta_temp = (theta_rad/M_PI*180) + (theta_rad > 0 ? 0 : 360);
    theta_deg = ofMap(theta_temp, 0, 360, 360, 0);
    
    dist = ofDist(ofGetWidth()/2, ofGetHeight()/2, mouseX, mouseY);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //---------------- Drawing the master visualization.
    spacing = 360/float(masterDrawBuffer.size());
    ofPushStyle();
    for(int j = 0; j<masterDrawBuffer.size(); j++){
        float xpos = ofGetWidth()/2 + 100*cos(j*spacing);
        float ypos = ofGetHeight()/2 + 100*sin(j*spacing);
        ofSetColor(ofColor::fromHsb(240, 125*masterDrawBuffer[j], 255), 255/10);
        ofFill();
        ofDrawCircle(xpos, ypos, masterDrawBuffer[j]);
        
    }
    ofPopStyle();

    
    //---------------- Drawing each individual oscillator;
    for(int i = 0; i<oscillator.size(); i++){
        oscillator[i].draw();
    }
    
    
    //---------------- Mapping mouse coordinates for HUD.
    nlMap tmpMap;
    float frequency = tmpMap.nlMapFunction(theta_deg, 0, 360, FREQ_MIN, FREQ_MAX, NLMAP_FREQ);
    float lfoFrequency = tmpMap.nlMapFunction(dist, 0, ofGetWidth()/2, LFO_MIN, LFO_MAX, NLMAP_LFO);
    
    
    //---------------- HUD Drawing.
    if(hud){
        ofPushStyle();
        ofSetColor(255, 255, 255, 255/4);
        ofFill();
        ofDrawCircle(mouseX, mouseY, 2);
        ofDrawLine(mouseX-10, mouseY, mouseX+10, mouseY);
        ofDrawLine(mouseX, mouseY-10, mouseX, mouseY+10);
        
        ofNoFill();
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, dist);
        
        ofDrawLine(mouseX, mouseY, ofGetWidth()/2, ofGetHeight()/2);
        
        ofDrawBitmapString("Freq:" + ofToString(frequency), mouseX +25, mouseY -8);
        ofDrawBitmapString("LFO:" + ofToString(lfoFrequency), mouseX +25, mouseY + 4);
        
        for(int i=0; i<oscillator.size(); i++){
            ofDrawBitmapString("Freq:" + ofToString(oscillator[i].frequency), oscillator[i].position.x +22, oscillator[i].position.y);
            ofDrawBitmapString("LFO:" + ofToString(oscillator[i].lfoFrequency), oscillator[i].position.x +22, oscillator[i].position.y + 11);
            ofDrawBitmapString(i + 1, oscillator[i].position.x - 27, oscillator[i].position.y);
            ofDrawCircle(oscillator[i].position.x, oscillator[i].position.y, 2);
            ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, oscillator[i].position.x, oscillator[i].position.y);
        }
        
        ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
        ofDrawLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
        
        ofDrawBitmapString("Frame Rate:" + ofToString(ofGetFrameRate()), 10, ofGetHeight()-10);
        
        ofPopStyle();
        ofHideCursor();
    }
    
    
    //----------------- Drawing this if there's no HUD.
    else{
        ofDrawBitmapStringHighlight("press 'h' to toggle HUD", 20, 20);
        ofSetColor(255, 255, 255, 60);
        ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
        ofHideCursor();
        
        ofDrawLine(mouseX-10, mouseY, mouseX+10, mouseY);
        ofDrawLine(mouseX, mouseY-10, mouseX, mouseY+10);
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++){
        
        
        counter++;
        
        for(int i=0; i<oscillator.size(); i++){
        
        oscillator[i].wave = oscillator[i].oscillator.sinewave(oscillator[i].frequency) * oscillator[i].lfo.sinewave(oscillator[i].lfoFrequency);
        
        finalWave += oscillator[i].wave;
        }
        
        output[i*nChannels    ] = finalWave * 0.01;
        output[i*nChannels + 1] = finalWave * 0.01;
        
        for(int i = 0; i<oscillator.size(); i++){
        oscillator[i].drawBuffer[counter%bufferSize] = oscillator[i].wave;
        }
        
        masterDrawBuffer[counter%bufferSize] = finalWave/oscillator.size();
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == '1'){
        oscillator[0].isSelected = !oscillator[0].isSelected;
    }

    if(key == '2'){
        oscillator[1].isSelected = !oscillator[1].isSelected;
    }
    
    if(key == '3'){
        oscillator[2].isSelected = !oscillator[2].isSelected;
    }
    
    if(key == '4'){
        oscillator[3].isSelected = !oscillator[3].isSelected;
    }
    
    if(key == '5'){
        oscillator[4].isSelected = !oscillator[4].isSelected;
    }
    
    if(key == '6'){
        oscillator[5].isSelected = !oscillator[5].isSelected;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        for(int i=0; i<oscillator.size(); i++){
            if(!oscillator[i].isSelected){
                oscillator[i].targetPosition.x = ofRandomWidth();
                oscillator[i].targetPosition.y = ofRandomHeight();
            }
        }
    }
    
    if(key == 'a'){
        for(int i=0; i<oscillator.size(); i++){
            if(oscillator[i].isSelected){
                oscillator[i].isAlive = !oscillator[i].isAlive;
            }
        }
    }
    
    if(key=='h'){
        hud = !hud;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    for(int i=0; i<oscillator.size(); i++){
        if(oscillator[i].isSelected){
                oscillator[i].targetPosition.x = x;
                oscillator[i].targetPosition.y = y;
        }
    }
    
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
