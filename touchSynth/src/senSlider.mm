#include "senSlider.hpp"

void senSlider::setup(float cValue, float min, float max, ofVec2f pos){
    position = pos;
    currentValue = cValue;
    maxValue = max;
    minValue = min;
    
    height = 20;
    width = 300;
    
    ofAddListener(ofEvents().touchDown, this, &senSlider::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &senSlider::touchMoved);
    
}

void senSlider::setup(float cValue, float min, float max, ofVec2f pos, float _width, float _height){
    position = pos;
    currentValue = cValue;
    maxValue = max;
    minValue = min;
    
    height = _height;
    width = _width;
    
    ofAddListener(ofEvents().touchDown, this, &senSlider::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &senSlider::touchMoved);
}

void senSlider::setSize(float _width, float _height){
    width = _width;
    height = _height;
}

void senSlider::draw(){
    ofPushStyle();
    ofSetLineWidth(1);
    
    ofFill();
    ofSetColor(191, 45, 77);
    ofDrawRectangle(position.x, position.y, (currentValue-minValue)/(maxValue-minValue) * width, height);
    
    ofNoFill();
    ofSetColor(191, 102, 122);
    ofDrawRectangle(position.x, position.y, width, height);
    ofPopStyle();
    
}

float senSlider::getValue(){
    return currentValue;
}

void senSlider::update(){
    
}

void senSlider::setValue(float value){
    currentValue = ofMap(value, 0, width, minValue, maxValue);
}

void senSlider::touchDown(ofTouchEventArgs &touch){
    
    if((touch.x>position.x) && (touch.x - position.x < width)){
        if((touch.y>position.y) && (touch.y - position.y < height)){
            setValue(touch.x - position.x);
        }
    }
}

void senSlider::touchMoved(ofTouchEventArgs &touch){
    
    if((touch.x>position.x) && (touch.x - position.x < width)){
        if((touch.y>position.y) && (touch.y - position.y < height)){
            setValue(touch.x - position.x);
            
            
        }
    }
}
