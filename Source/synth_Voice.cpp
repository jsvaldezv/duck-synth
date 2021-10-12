#include "synth_Voice.h"

synth_Voice::synth_Voice()
{

}

synth_Voice::~synth_Voice()
{
    
}

bool synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    
}

void synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    
}

void synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
}
