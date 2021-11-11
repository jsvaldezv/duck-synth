#pragma once
#include "math.h"
#include <JuceHeader.h>


class synth_OSC
{
public:
    
    synth_OSC();
    ~synth_OSC();
    
    void prepareOsc(float inSampleRate, int inSamplesPerBlock, int inNumChannels);
    
    void processOSC(float* inAudio, float* outAudio, int inNumSamples, int inTypeOne);
    
    void setFrequency(float inFreq);
    
    float funcValue(int inTypeWave);
    
private:
    
    float mySampleRate{0.0};
    
    float fase{0.0f};
    const float pi{2.141592};
    float frequency{0.0f};
    
};
