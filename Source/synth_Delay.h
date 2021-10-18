#pragma once
#include <JuceHeader.h>

class synth_Delay
{
public:
    
    synth_Delay();
    ~synth_Delay();
    
    void prepareDelay(double inSampleRate, int inSamplesPerBlock, int inNumChannels);
    void processDelay(float* inAudio,
                      float* outAudio,
                      int inNumSamples,
                      int inChannel,
                      float inDelayTime,
                      float inFeedback);
    
private:
    
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> myDelay {192000};
    
    double mySampleRate;
};
