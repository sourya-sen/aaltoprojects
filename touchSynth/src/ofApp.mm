#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetOrientation(OF_ORIENTATION_90_RIGHT);
    ofEnableAntiAliasing();
    ofSetCircleResolution(1000);
    ofEnableSmoothing();
    ofBackground(0);
    ofSetLineWidth(3);
    
    bufferSize = 512;
    
    mtof.resize(128);
    for(int i=0; i<mtof.size(); i++){
        mtof[i] = 440.0/32.0 * (pow (2.0, ((i-9.0)/12.0)));
    }
    
    //.....................UIBoxes_Main
    clockPos.set(20, 20);
    clockWidth = 220;
    clockHeight = 100;
    
    fmPos.set(250, 20);
    fmWidth = 330;
    fmHeight = 200;
    
    enPos.set(250, 230);
    enWidth = 330;
    enHeight = 210;
    
    algoPos.set(20, 130);
    algoWidth = 220;
    algoHeight = 310;
    
    padPos.set(20, 450);
    padWidth = ofGetWidth()*2/3 - 120;
    padHeight = 300;
    
    filterPos.set(ofGetWidth()*2/3 -100 + 30, 20);
    filterWidth = 390;
    filterHeight = 220;
    
    fxPos.set(ofGetWidth()*2/3 -100 + 30, 20+230);
    fxWidth = 390;
    fxHeight = 220;
    
    fwPos.set(ofGetWidth()*2/3 - 100 + 20, ofGetHeight() - 280);
    fwWidth = ofGetWidth()/3 + 70;
    fwHeight = 270;
    //.................................
    
    //.......................Clock_Init
    clockSwitch.setup(false, clockPos.x+10, clockPos.y+10);
    clockSwitch.setSize(30);
    clockTempo.setup(120, 60, 180, clockPos + ofVec2f(50, 20), 160, 20);
    
    clock.setTicksPerBeat(1);
    
    //..........................FM_Init
    fmSwitch.setup(false, fmPos.x+20, fmPos.y+10);
    fmSwitch.setSize(30);
    
    fmTrigger.setup(false, fmPos.x+20, fmPos.y+50);
    fmTrigger.setSize(30);
    fmTrigger.setMode("gate");
    
    fmClockSource.setup(false, fmPos.x+20, fmPos.y+90);
    fmClockSource.setSize(30);
    
    fmFrequency.setup(60, 0, 128, ofPoint(fmPos.x + 70, fmPos.y + 10), 240, 20);
    fmIndex.setup(1, 1, 10000, ofPoint(fmPos.x + 70, fmPos.y + 40), 240, 20);
    fmRatio.setup(1, 1, 100, ofPoint(fmPos.x + 70, fmPos.y + 70), 240, 20);
    
    fmBuffer.resize(bufferSize);
    
    //..........................Envelope_Init
    enAttack.setup(1000, 1, 5000, ofPoint(enPos.x + 20, enPos.y + 35), enWidth-40, 20);
    enDecay.setup(1, 1, 5000, ofPoint(enPos.x + 20, enPos.y + 75), enWidth-40, 20);
    enSustain.setup(1, 1, 5000, ofPoint(enPos.x + 20, enPos.y + 115), enWidth-40, 20);
    enRelease.setup(100, 1, 5000, ofPoint(enPos.x + 20, enPos.y + 155), enWidth-40, 20);
    
    //.........................Pad_Init
    padButtons.resize(12);
    for(int i = 0; i<padButtons.size(); i++){
        if(i<6){
            padButtons[i].setup(false, padPos.x + 10 + 90 * i, padPos.y + 40);
        } else {
            padButtons[i].setup(false, padPos.x + 10 + 90 * (i-6), padPos.y + 40 + 120);
        }
        padButtons[i].setSize(90);
        padButtons[i].setMode("gate");
    }
    
    //............................Filter_Init
    filterFreq.setup(80, 30, 1200, ofPoint(filterPos.x+20, filterPos.y+20), filterWidth-40, 20);
    filterMix.setup(.5, 0, 1, ofPoint(filterPos.x+20, filterPos.y+20 + 40), filterWidth-40, 20);
    
    filWetBuffer.resize(bufferSize);
    filOutBuffer.resize(bufferSize);
    
    //...........................Delay_Init
    dlSize.setup(1, 1, 5000, ofPoint(fxPos.x + 20, fxPos.y+20), fxWidth-40, 20);
    dlFeedback.setup(.5, 0, 1, ofPoint(fxPos.x + 20, fxPos.y+ 20 + 40), fxWidth-40, 20);
    dlMix.setup(.5, 0, 1, ofPoint(fxPos.x + 20, fxPos.y+ 20 + 80), fxWidth-40, 20);
    
    dlLineBuffer.resize(bufferSize);
    dlMixBuffer.resize(bufferSize);
    
    //..........................FinalWave_Init
    amSwitch.setup(false, fwPos.x+20, fwPos.y + 20);
    amSwitch.setSize(40);
    amMag.setup(10, 10, 100, ofPoint(fwPos.x+80, fwPos.y + 20), fwWidth-100, 40);
    
    finalWaveBuffer.resize(bufferSize);
    
    ofxAccelerometer.setup();
    
    //.........................Algo_Init
    //........................................

    //........................................
    
    ofSoundStreamSetup(2,2,this, 44100, bufferSize, 4);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    envelop.setAttack(enAttack.getValue());
    envelop.setDecay(enDecay.getValue());
    envelop.setSustain(enSustain.getValue());
    envelop.setRelease(enRelease.getValue());
    
    clock.setTempo(clockTempo.getValue());
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetLineWidth(1);
    ofNoFill();
    ofSetColor(191, 102, 122);
    ofDrawRectangle(10, 10, ofGetWidth()*2/3 - 100, ofGetHeight()-20); //Main Generator Box
    ofDrawRectangle(ofGetWidth()*2/3 - 100 + 20, 10, ofGetWidth()/3 + 70, ofGetHeight()-300); //Effects
    ofDrawRectangle(fwPos.x, fwPos.y, fwWidth, fwHeight); //Final Wave
    
    ofDrawRectangle(clockPos.x, clockPos.y, clockWidth, clockHeight); //Clock Box
    ofDrawRectangle(fmPos.x, fmPos.y, fmWidth, fmHeight); //FM
    ofDrawRectangle(enPos.x, enPos.y, enWidth, enHeight); //Envelope
    ofDrawRectangle(algoPos.x, algoPos.y, algoWidth, algoHeight); // Algo
    ofDrawRectangle(padPos.x, padPos.y, padWidth, padHeight); //Buttons!
    
    ofDrawRectangle(filterPos.x, filterPos.y, filterWidth, filterHeight); //Filter Box
    ofDrawRectangle(fxPos.x, fxPos.y, fxWidth, fxHeight); //Delay Box
    
    //Clock Drawing
    clockSwitch.draw();
    clockTempo.draw();
    ofPushStyle();
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawCircle(clockPos + ofVec2f(clockWidth-20, clockHeight-20), 5);
    ofPopStyle();
    
    //FM Drawing
    fmSwitch.draw();
    fmTrigger.draw();
    fmClockSource.draw();
    fmFrequency.draw();
    fmIndex.draw();
    fmRatio.draw();
    
    float fmSpacing = 240/float(fmBuffer.size());
    ofSetLineWidth(1);
    
    ofNoFill();
    ofDrawRectangle(fmPos.x + 70, fmPos.y + 100, 240, 80); //audio box
    
    for(int i = 0; i<fmBuffer.size(); i++){
        ofDrawLine(fmPos.x + 70 + i*fmSpacing, fmPos.y + 140, fmPos.x + 70 + i*fmSpacing, fmPos.y + 140 + fmBuffer[i]*10);
    }
    
    //Envelop Drawing
    enAttack.draw();
    enDecay.draw();
    enSustain.draw();
    enRelease.draw();
    
    //Pad Drawing
    for(int i=0; i<padButtons.size(); i++){
        padButtons[i].draw();
    }
    
    //Filter Drawing
    filterFreq.draw();
    filterMix.draw();
    
    float filSpacing = (filterWidth/2)/float(bufferSize);
    
    ofNoFill();
    ofDrawRectangle(filterPos.x, filterPos.y + 100, filterWidth/2, 120);
    ofDrawRectangle(filterPos.x + filterWidth/2, filterPos.y + 100, filterWidth/2, 120);
    
    for(int i = 0; i<filWetBuffer.size(); i++){
        ofDrawLine(filterPos.x + i*filSpacing, filterPos.y + 160, filterPos.x + i*filSpacing, filterPos.y + 160 + filWetBuffer[i]*10);
    }
    
    for(int i = 0; i<filOutBuffer.size(); i++){
        ofDrawLine(filterPos.x + 195 + i*filSpacing, filterPos.y + 160, filterPos.x + i*filSpacing + 195, filterPos.y + 160 + filOutBuffer[i]*10);
    }
    
    //Delay Drawing
    dlSize.draw();
    dlFeedback.draw();
    dlMix.draw();
    
    ofNoFill();
    ofDrawRectangle(fxPos.x, fxPos.y + 140, fxWidth/2, 80);
    ofDrawRectangle(fxPos.x + fxWidth/2, fxPos.y + 140, fxWidth/2, 80);
    
    float dlSpacing = (fxWidth/2)/float(bufferSize);
    
    for(int i = 0; i<dlLineBuffer.size(); i++){
        ofDrawLine(fxPos.x + i*dlSpacing, fxPos.y + 180, fxPos.x + i*dlSpacing, fxPos.y + 180 + dlLineBuffer[i]*10);
    }

    for(int i = 0; i<dlMixBuffer.size(); i++){
        ofDrawLine(fxPos.x + 195 + i*dlSpacing, fxPos.y + 180, fxPos.x + i*dlSpacing + 195, fxPos.y + 180 + dlMixBuffer[i]*10);
    }
    
    //Final Wave Drawing
    amSwitch.draw();
    amMag.draw();
    
    float fwSpacing = (fwWidth)/float(bufferSize);
    
    for(int i = 0; i<finalWaveBuffer.size(); i++){
        ofDrawLine(fwPos.x + i*fwSpacing, fwPos.y + fwHeight/2 + 20, fwPos.x + i*fwSpacing, fwPos.y + fwHeight/2 + 20 + finalWaveBuffer[i]*20);
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
       
        if(clockSwitch.getState()==true){
            clock.ticker();
        }
        
        volume = (envelop.adsr(1, envelop.trigger));
        
        if(clock.tick){
            clockColor.set(0, 255, 0);
        } else {
            clockColor.set(255, 0 , 0);
        }
        
        if((fmClockSource.getState()==true) && (clock.tick)){
            envelop.trigger = 1;
        } else {
            envelop.trigger = fmTrigger.getState();
            
        }
        
        int playFreq;
        
        playFreq = fmFrequency.getValue();
        
        for(int i = 0; i<padButtons.size(); i++){
            if(padButtons[i].getState() == true){
                playFreq = fmFrequency.getValue() + i;
                if(fmClockSource.getState()==false){
                    envelop.trigger = 1;
                }
        }
        }
        
        counter++;
        
        float freq = mtof[playFreq];
        int ind = int(fmIndex.getValue());
        int rat = int(fmRatio.getValue());
        
        float filFreq = filterFreq.getValue();
        float filMix = filterMix.getValue();
        
        float delSize = dlSize.getValue();
        float delFeedback = dlFeedback.getValue();
        float delMix = dlMix.getValue();
        
        float amMagnitude = ofxAccelerometer.getForce().length() * amMag.getValue();
        
        double lfoOut = lfo.sinewave(fabs(amMagnitude));
        
        double osciOut = oscillator.sinewave(freq + (modulator.sinewave(rat * freq) * ind * volume)) * volume * fmSwitch.getState();
        
        double filterWet = filter.lores(osciOut, filFreq, 4);
        double filterOut = filterWet * filMix + osciOut * (1 - filMix);
        
        double delayLine = delay.dl(filterOut, delSize, delFeedback);
        double delayOut = delayLine * delMix + filterOut * (1 - delMix);
        
        double finalWave;
        
        if(amSwitch.getState()==true){
            finalWave = delayOut * lfoOut;
        } else {
            finalWave = delayOut;
        }
        
        // double myOutput = lfoOut*osciOut*button.getState();
        
        output[i * nChannels] = finalWave;
        output[i * nChannels + 1] = finalWave;
        
        fmBuffer[counter%fmBuffer.size()] = osciOut;
        
        filWetBuffer[counter%filWetBuffer.size()] = filterWet;
        filOutBuffer[counter%filOutBuffer.size()] = filterOut;
        
        dlLineBuffer[counter%dlLineBuffer.size()] = delayLine;
        dlMixBuffer[counter%dlMixBuffer.size()] = delayOut;
        
        finalWaveBuffer[counter%finalWaveBuffer.size()] = finalWave;
        
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    
    
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
    
}
