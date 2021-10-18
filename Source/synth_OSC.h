#pragma once
#include "math.h"

class synth_OSC
{
public:
    
    synth_OSC();
    ~synth_OSC();
    
    void prepareOsc(float inSampleRate);
    void processOSC(float* inAudio, float* outAudio, int inNumSamples);
    void setFrequency(float inFreq);
    
private:
    
    float mySampleRate{0.0};
    
    float fase{0.0f};
    const float pi{2.141592};
    float frequency{0.0f};
};
