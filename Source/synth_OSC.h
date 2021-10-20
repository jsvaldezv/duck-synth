#pragma once
#include "math.h"

class synth_OSC
{
public:
    
    synth_OSC();
    ~synth_OSC();
    
    void prepareOSC(float inSampleRate);
    
    void setFrequency(float inFrequency);
    
    void processOSC(float* inAudio, float* outAudio, int inNumSamples);
    
private:
    
    float mySampleRate{0.0f};
    float frequency{0.0f};
    
    const float pi{3.141592};
    float fase {0.0f};
    
};
