#pragma once
#include "ofMain.h"

class nlMap{
public:

    nlMap();
    float nlMapFunction(float in, float inMin, float inMax, float outMin, float outMax, float shaper);


};
