#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    
    oscOne.setFrequency (frequency);
    oscTwo.setFrequency (frequency);
    
    myADSR.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    myADSR.noteOff();
    
    if (!allowTailOff || !myADSR.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    mySampleRate = sampleRate;
    numChannels = outputChannels;
    
    myADSR.setSampleRate(mySampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    oscOne.prepare (spec);
    oscOne.setFrequency (440.0f);
    
    oscTwo.prepare (spec);
    oscTwo.setFrequency (440.0f);
    
    gain.prepare (spec);
    gain.setGainLinear (0.5f);
    
    reverb.prepare (spec);
}

void SynthVoice::getParams (float inVolume, float inAttack, float inDecay, float inSustain, float inRelease, int inTypeOne, int inTypeTwo, float inWetReverb, float inRoom)
{
    volumen = inVolume;
    typeOne = inTypeOne;
    typeTwo = inTypeTwo;
    
    gain.setGainLinear (volumen);
    
    setOscOne (typeOne);
    setOscTwo (typeTwo);
    
    setADSRParams (inAttack, inDecay, inSustain, inRelease);
    
    setReverbParams (inWetReverb, inRoom);
}

void SynthVoice::setADSRParams (float inAttack, float inDecay, float inSustain, float inRelease)
{
    adsrParams.attack = inAttack;
    adsrParams.decay = inDecay;
    adsrParams.sustain = inSustain;
    adsrParams.release = inRelease;
    
    myADSR.setParameters (adsrParams);
}

void SynthVoice::setReverbParams (float inWet, float inRoom)
{
    reverbParams.wetLevel = inWet;
    reverbParams.roomSize = inRoom;
    
    reverb.setParameters (reverbParams);
}

void SynthVoice::setOscOne (int inTypeWave)
{
    switch (inTypeWave)
    {
        case OscType::Sine:
            oscOne.initialise ({ [](float x){return std::sin(x);}});
            break;
            
        case OscType::Triangle:
            oscOne.initialise ({ [](float x){return x/M_PI;}});
            break;
            
        case OscType::Square:
            oscOne.initialise ({ [](float x){return x < 0.0f ? -1.0f : 1.0f;}});
            break;
    }
}

void SynthVoice::setOscTwo (int inTypeWave)
{
    switch(inTypeWave)
    {
        case OscType::Sine:
            oscTwo.initialise ({ [](float x){return std::sin(x);}});
            break;
            
        case OscType::Triangle:
            oscTwo.initialise ({ [](float x){return x/M_PI;}});
            break;
            
        case OscType::Square:
            oscTwo.initialise ({ [](float x){return x < 0.0f ? -1.0f : 1.0f;}});
            break;
    }
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    oscOne.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    oscTwo.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    reverb.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    myADSR.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (!myADSR.isActive())
            clearCurrentNote();
    }
}
