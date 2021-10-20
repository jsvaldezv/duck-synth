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
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    myADSR.noteOn();
    
    for(int i = 0; i < numChannels; i++)
    {
        ptrOSC[i]->setFrequency(frequency);
    }
}

void synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    myADSR.noteOff();
}

void synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void synth_Voice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    mySampleRate = sampleRate;
    numChannels = outputChannels;
    
    myADSR.setSampleRate(mySampleRate);
    
    for(int i = 0; i < outputChannels; i++)
    {
        ptrOSC[i] = std::make_unique<synth_OSC>();
    }
    
    for(int i = 0; i < numChannels; i++)
    {
        ptrOSC[i]->prepareOSC(mySampleRate);
    }
}

void synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        auto* channelData = outputBuffer.getWritePointer(channel);
        
        ptrOSC[channel]->processOSC(channelData, channelData, numSamples);
    }
    
    myADSR.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
