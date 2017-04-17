#include "senButton.hpp"

void senButton::setup(bool toggle, ofPoint pos){
    state = toggle;
    position = pos;
    size = 40;
    
    ofAddListener(ofEvents().touchDown, this, &senButton::touchDown);
    ofAddListener(ofEvents().touchUp, this, &senButton::touchUp);
    
}

void senButton::setup(bool toggle, float posx, float posy){
    position.set(posx, posy);
    setup(toggle, position);
}

void senButton::setMode(string _mode){
    mode = _mode;
}

void senButton::draw(){
    ofPushStyle();
    ofSetLineWidth(1);

    ofFill();
    if(state == false){
        ofSetColor(64, 15, 26);
    } else {
        ofSetColor(191, 45, 77);
    }
    ofDrawRectangle(position.x, position.y, size, size);
    
    ofSetColor(191, 102, 122);
    ofNoFill();
    ofDrawRectangle(position.x, position.y, size, size);
    
    ofPopStyle();
}

void senButton::setSize(int _size){
    size = _size;
}

bool senButton::getState(){
    return state;
}

void senButton::setState(bool toggle){
    state = toggle;
}

void senButton::switchState(){
    state = !state;
}

void senButton::touchDown(ofTouchEventArgs & touch){

    if((touch.x>position.x) && (touch.x - position.x < size)){
        if((touch.y>position.y) && (touch.y - position.y < size)){
            switchState();
        }
    }
}

void senButton::touchUp(ofTouchEventArgs & touch){
    if(mode == "gate"){
        if((touch.x>position.x) && (touch.x - position.x < size)){
            if((touch.y>position.y) && (touch.y - position.y < size)){
                switchState();
            }
        }
    }
}

