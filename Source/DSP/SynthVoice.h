#pragma once
#include <JuceHeader.h>
#include "../Helpers/Parameters.h"
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    SynthVoice() = default;
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    
    void getParams (float inVolume, float inAttack, float inDecay, float inSustain, float inRelease, int inTypeOne, int inTypeTwo, float inWetReverb, float inRoom);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void setADSRParams (float inAttack, float inDecay, float inSustain, float inRelease);
    
    void setReverbParams (float inWet, float inRoom);
    
    void setOscOne (int inTypeWave);
    
    void setOscTwo (int inTypeWave);
    
private:

    double mySampleRate { 0.0 };
    int numChannels { 0 };
    
    // Oscillator
    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Oscillator<float> oscOne { [](float x){return std::sin(x);} };
    juce::dsp::Oscillator<float> oscTwo { [](float x){return x/M_PI;} };
    float frequency { 0.0f };
    int typeOne { 0 }, typeTwo { 0 };
    
    // ADSR
    juce::ADSR myADSR;
    juce::ADSR::Parameters adsrParams;
    
    // Volume
    juce::dsp::Gain<float> gain;
    float volumen { 0.0f };
    
    // Reverb
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    float reverbValue { 0.0f };
};
