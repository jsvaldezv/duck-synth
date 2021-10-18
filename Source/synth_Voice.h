#pragma once
#include <JuceHeader.h>
#include "synth_Sound.h"

#include "synth_OSC.h"
#include "synth_Delay.h"

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
    
    void getParams(float inVolume,
                   float inAttack,
                   float inDecay,
                   float inSustain,
                   float inRelease,
                   float inDelayTime,
                   float inFeedback);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    float getInterpolatedSampleFree(float inSampleActual);
    
    void setADSRParams(float inAttack, float inDecay, float inSustain, float inRelease);
    
private:

    double mySampleRate{0.0};
    int numChannels{0};
    
    // ADSR
    juce::ADSR myADSR;
    juce::ADSR::Parameters adsrParams;
    
    // OSC
    std::unique_ptr<synth_OSC> ptrOSC[2];
    float frequency{0.0f};
    
    // DELAY
    std::unique_ptr<synth_Delay> ptrDelay[2];
    float delayTime{0.0f}, feedback{0.0f};
    
    // SLIDERS VALUES
    float volumen{0.0f};
};
