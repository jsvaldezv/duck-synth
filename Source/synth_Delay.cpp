#include "synth_Delay.h"

synth_Delay::synth_Delay(){}

synth_Delay::~synth_Delay(){}

void synth_Delay::prepareDelay(double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    juce::dsp::ProcessSpec spec;
    
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;
    
    myDelay.reset();
    myDelay.prepare(spec);
    myDelay.setDelay(24000);
    
    mySampleRate = inSampleRate;
}

void synth_Delay::processDelay(float* inAudio,
                               float* outAudio,
                               int inNumSamples,
                               int inChannel,
                               float inDelayTime,
                               float inFeedback)
{
    int delayTimeInSamples = inDelayTime * mySampleRate;
    myDelay.setDelay(delayTimeInSamples);
    
    for(int i = 0; i < inNumSamples; i++)
    {
        float delayedSample = myDelay.popSample(inChannel);
        float inDelay = inAudio[i] + (delayedSample * inFeedback);
        myDelay.pushSample(inChannel, inDelay);
        outAudio[i] = (inAudio[i] + delayedSample);
    }
}
