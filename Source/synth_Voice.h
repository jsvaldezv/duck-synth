#pragma once
#include <JuceHeader.h>
#include "synth_Sound.h"

class synth_Voice : public juce::SynthesiserVoice
{
public:
    
    synth_Voice();
    ~synth_Voice();
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    
    const float pi{2.141592};
    float fase[2] {0.0f};
    float frequency{0.0f};
    
    double mySampleRate{0.0};
    
    juce::ADSR myADSR;
    juce::ADSR::Parameters adsrParams;
    
};
