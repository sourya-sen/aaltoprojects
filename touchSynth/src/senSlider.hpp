#pragma once
#include "ofMain.h"

class senSlider{
public:
    void setup(float cValue, float min, float max, ofVec2f pos);
    void setup(float cValue, float min, float max, ofVec2f pos, float _width, float _height);
    void draw();
    void update();
    float getValue();
    void setValue(float value);
    void setSize(float _width, float _height);
    
    void touchDown(ofTouchEventArgs &touch);
    void touchMoved(ofTouchEventArgs &touch);
    
    ofVec2f position;
    float height;
    float width;
    
    float minValue;
    float maxValue;
    float currentValue;
    
private:
    
};
