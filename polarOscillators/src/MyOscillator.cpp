#include "MyOscillator.h"


//------------------------------------------------------

void MyOscillator::setup(int _bufferSize){
    
    bufferSize = _bufferSize;
    
    position.x = ofRandomWidth();
    position.y = ofRandomHeight();
    
    targetPosition = position;
    
    drawBuffer.resize(bufferSize);
    
    for(int i=0; i<drawBuffer.size(); i++){
        drawBuffer[i] = 0;
    }
    
    isAlive = true;
    refreshRate = 180;
}

//------------------------------------------------------

void MyOscillator::update(){
    
    radius = isSelected ?  RADIUS * 2 : RADIUS + 5*ofNoise(ofGetFrameNum());
    
    float speed = 100;
    
    position.x += (targetPosition.x - position.x)/speed;
    position.y += (targetPosition.y - position.y)/speed;
    
    theta_rad = (atan2(position.y - ofGetHeight()/2, position.x - ofGetWidth()/2));
    float theta_temp = (theta_rad/M_PI*180) + (theta_rad > 0 ? 0 : 360);
    theta_deg = ofMap(theta_temp, 0, 360, 360, 0);
    
    float dist = ofDist(ofGetWidth()/2, ofGetHeight()/2, position.x, position.y);
    
    nlMap tmpMap;
    frequency = tmpMap.nlMapFunction(theta_deg, 0, 360, FREQ_MIN, FREQ_MAX, NLMAP_FREQ);
    lfoFrequency = tmpMap.nlMapFunction(dist, 0, ofGetWidth()/2, LFO_MIN, LFO_MAX, NLMAP_LFO);
    
    
    if(isAlive){
        moveAlive();
    }
    
    //.......Particles shouldn't cross between Q1 & Q4
    
    //Are they in Q1?
    if(position.x>ofGetWidth()/2 && position.y<ofGetHeight()/2){
        if(targetPosition.y>ofGetHeight()/2){
            if(position.y>ofGetHeight()/2 - 2*RADIUS){
                targetPosition.x = position.x + ofRandom(-200, 200);
                targetPosition.y = position.y + ofRandom(-200, 0);
            }
        }
    }
    
    //Are they in Q4?
    if(position.x>ofGetWidth()/2 && position.y>ofGetHeight()/2){
        if(targetPosition.y<ofGetHeight()/2){
            if(position.y<ofGetHeight()/2 + 2*RADIUS){
                targetPosition.x = position.x + ofRandom(-200, 200);
                targetPosition.y = position.y + ofRandom(0, 200);
        }
    }
    }
    
    //.......Check for screen boundaries.
    
    if(targetPosition.x>ofGetWidth() - 2*RADIUS || targetPosition.x<0 + 2*RADIUS){
        targetPosition.x = ofRandomWidth();
    }
    
    if(targetPosition.y>ofGetHeight() - 2*RADIUS || targetPosition.y<0 + 2*RADIUS){
        targetPosition.y = ofRandomHeight();
    }

}

//------------------------------------------------------

void MyOscillator::draw(){
    
    ofPushStyle();
    float alpha = isSelected ? 50 : 12.5;
    float hue = isAlive ? 45 : 0;
    
    if(targetPosition.x != position.x || targetPosition.y != position.y){
        ofSetColor(255, 255, 255, 60);
        ofDrawLine(targetPosition.x, targetPosition.y, position.x, position.y);
        ofDrawCircle(targetPosition.x, targetPosition.y, 2);
    }
    
    spacing = 360/float(drawBuffer.size());
    
    
    ofSetColor(255, 255, 255, 60);
    ofDrawCircle(position.x, position.y, 2);
    
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    
    for(int i=0; i<drawBuffer.size(); i++){
        posx = radius*cos(i*spacing);
        posy = radius*sin(i*spacing);
        
        ofSetColor(ofColor::fromHsb(hue, 1000*drawBuffer[i], 255), alpha);
        ofDrawCircle(posx, posy, 3*drawBuffer[i]);
        
    }
    
    ofPopMatrix();
    
    if(isSelected){
        ofSetColor(255, 255, 255, 127);
        ofDrawBitmapString("Freq:" + ofToString(frequency), position.x +22, position.y);
        ofDrawBitmapString("LFO:" + ofToString(lfoFrequency), position.x +22, position.y + 11);
    }
    ofPopStyle();
    
}

//------------------------------------------------------

void MyOscillator::moveAlive(){
    
    if(ofGetFrameNum()%refreshRate == 0){
        if(ofRandom(100)>75){
            targetPosition.x = position.x + ofRandom(-200, 200);
            targetPosition.y = position.y + ofRandom(-200, 200);
        }
    }
}

//------------------------------------------------------
