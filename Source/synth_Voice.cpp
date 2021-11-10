#include "synth_Voice.h"

synth_Voice::synth_Voice(){}

synth_Voice::~synth_Voice(){}

bool synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    for(int i = 0; i < numChannels; i++)
    {
        ptrOSC[i]->setFrequency(frequency);
    }
    
    myADSR.noteOn();
}

void synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    myADSR.noteOff();
}

void synth_Voice::controllerMoved (int controllerNumber, int newControllerValue){}

void synth_Voice::pitchWheelMoved (int newPitchWheelValue){}

void synth_Voice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    mySampleRate = sampleRate;
    myADSR.setSampleRate(mySampleRate);
    numChannels = outputChannels;
    
    for(int i = 0; i < outputChannels; i++)
    {
        ptrOSC[i] = std::make_unique<synth_OSC>();
    }
    
    for(int i = 0; i < outputChannels; i++)
    {
        ptrOSC[i]->prepareOsc(sampleRate);
    }
}

void synth_Voice::getParams(float inVolume,
                            float inAttack,
                            float inDecay,
                            float inSustain,
                            float inRelease,
                            float inDelayTime,
                            float inFeedback,
                            int inTypeOne)
{
    volumen = inVolume;
    typeOne = inTypeOne;
    setADSRParams(inAttack, inDecay, inSustain, inRelease);
}

void synth_Voice::setADSRParams(float inAttack, float inDecay, float inSustain, float inRelease)
{
    adsrParams.attack = inAttack;
    adsrParams.decay = inDecay;
    adsrParams.sustain = inSustain;
    adsrParams.release = inRelease;
    
    myADSR.setParameters(adsrParams);
}

void synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        auto* channelData = outputBuffer.getWritePointer(channel);
        
        ptrOSC[channel]->processOSC(channelData,
                                    channelData,
                                    numSamples,
                                    typeOne);
    }
    
    myADSR.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
