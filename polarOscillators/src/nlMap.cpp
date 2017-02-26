#include "nlMap.h"

//-----------------------------------------------------------

nlMap::nlMap(){
    
}
//-----------------------------------------------------------

float nlMap::nlMapFunction(float in, float inMin, float inMax, float outMin, float outMax, float shaper){
    
    // (1) convert to pct (0-1)
    float pct = ofMap(in, inMin, inMax, 0, 1, true);
    
    // raise this number to a power
    pct = powf(pct, shaper);
    float out = ofMap(pct, 0,1, outMin, outMax, true);
    return out;
}

//------------------------------------------------------------

/*
 
From Zach on oF Forum:

 If shaper is 1, you get linear output like ofMap.
 
 If not, you can shape the output. 
 Shaper > 1 means you'll have non linear steps weighted towards the start.
 If shaper is < 1 and > 0 you can get non linear range weighted towards the end.
 There are plenty of other shaper functions that take a pct (a number between 0 and 1) and output a pct, which might help.

*/
