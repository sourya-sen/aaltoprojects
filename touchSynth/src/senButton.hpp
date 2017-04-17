#pragma once
#include "ofMain.h"

class senButton{
public:
    void setup(bool toggle, ofPoint pos);
    void setup(bool toggle, float posx, float posy);
    void draw();
    bool getState();
    void setState(bool toggle);
    void switchState();
    void setSize(int _size);
    void setMode(string _mode);
    void touchDown(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    
    ofPoint position;
    int size;
    string mode;
    
private:
    bool state;
};
