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
    
    oscOne.setFrequency(frequency);
    oscTwo.setFrequency(frequency);
    
    myADSR.noteOn();
}

void synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    myADSR.noteOff();
    
    if(!allowTailOff || !myADSR.isActive())
        clearCurrentNote();
}

void synth_Voice::controllerMoved (int controllerNumber, int newControllerValue){}

void synth_Voice::pitchWheelMoved (int newPitchWheelValue){}

void synth_Voice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    mySampleRate = sampleRate;
    numChannels = outputChannels;
    
    myADSR.setSampleRate(mySampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    oscOne.prepare(spec);
    oscOne.setFrequency(440.0f);
    
    oscTwo.prepare(spec);
    oscTwo.setFrequency(440.0f);
}

void synth_Voice::getParams(float inVolume,
                            float inAttack,
                            float inDecay,
                            float inSustain,
                            float inRelease,
                            float inDelayTime,
                            float inFeedback,
                            int inTypeOne,
                            int inTypeTwo)
{
    volumen = inVolume;
    typeOne = inTypeOne;
    typeTwo = inTypeTwo;
    
    setOscOne(typeOne);
    setOscTwo(typeTwo);
    
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

void synth_Voice::setOscOne(int inTypeWave)
{
    switch(inTypeWave)
    {
        case 0:
            oscOne.initialise({ [](float x){return std::sin(x);}});
            break;
        case 1:
            oscOne.initialise({ [](float x){return x/M_PI;}});
            break;
        case 2:
            oscOne.initialise({ [](float x){return x < 0.0f ? -1.0f : 1.0f;}});
            break;
    }
}

void synth_Voice::setOscTwo(int inTypeWave)
{
    switch(inTypeWave)
    {
        case 0:
            oscTwo.initialise({ [](float x){return std::sin(x);}});
            break;
        case 1:
            oscTwo.initialise({ [](float x){return x/M_PI;}});
            break;
        case 2:
            oscTwo.initialise({ [](float x){return x < 0.0f ? -1.0f : 1.0f;}});
            break;
    }
}

void synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if(!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock {synthBuffer};
    
    oscOne.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    oscTwo.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    myADSR.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if(!myADSR.isActive())
            clearCurrentNote();
    }
}
