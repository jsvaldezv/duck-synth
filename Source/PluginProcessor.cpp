#include "PluginProcessor.h"
#include "PluginEditor.h"

DuckSynthAudioProcessor::DuckSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    initSynth();
}

void DuckSynthAudioProcessor::initSynth()
{
    for (int i = 0; i < NUM_VOICES; i++)
    {
        synth.addSound (new SynthSound());
        synth.addVoice (new SynthVoice());
    }
}

DuckSynthAudioProcessor::~DuckSynthAudioProcessor(){}

const juce::String DuckSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DuckSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DuckSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DuckSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DuckSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DuckSynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int DuckSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DuckSynthAudioProcessor::setCurrentProgram (int index){}

const juce::String DuckSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void DuckSynthAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

void DuckSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i)))
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    }
}

void DuckSynthAudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DuckSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DuckSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i)))
        {
            voice->getParams (apvts.getRawParameterValue (VOLUME)->load(),
                              apvts.getRawParameterValue (ATTACK)->load(),
                              apvts.getRawParameterValue (DECAY)->load(),
                              apvts.getRawParameterValue (SUSTAIN)->load(),
                              apvts.getRawParameterValue (RELEASE)->load(),
                              apvts.getRawParameterValue (TYPE_ONE)->load(),
                              apvts.getRawParameterValue (TYPE_TWO)->load(),
                              apvts.getRawParameterValue (REVERB_WET)->load(),
                              apvts.getRawParameterValue (ROOM)->load());
        }
    }
    
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

bool DuckSynthAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DuckSynthAudioProcessor::createEditor()
{
    return new DuckSynthAudioProcessorEditor (*this);
}

void DuckSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}

void DuckSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DuckSynthAudioProcessor();
}
