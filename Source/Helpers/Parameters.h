#pragma once
#include <JuceHeader.h>

static const int NUM_VOICES = 5;

static juce::String VOLUME = "Volume";
static juce::String ATTACK = "Attack";
static juce::String DECAY = "Decay";
static juce::String SUSTAIN = "Sustain";
static juce::String RELEASE = "Release";
static juce::String TYPE_ONE = "TypeOne";
static juce::String TYPE_TWO = "TypeTwo";
static juce::StringArray OSC_TYPES = { "Sine", "Triangle", "Square" };
static juce::String REVERB_WET = "ReverbWet";
static juce::String ROOM = "Room";

enum OscType
{
    Sine = 0,
    Triangle = 1,
    Square = 2,
};

inline juce::AudioProcessorValueTreeState::ParameterLayout createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (VOLUME, 1), VOLUME, 0.0f, 1.0f, 0.25f));
    
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (ATTACK, 1), ATTACK, 0.1f, 3.0f, 0.5f));
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (SUSTAIN, 1), SUSTAIN, 0.1f, 3.0f, 0.5f));
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (DECAY, 1), DECAY, 0.1f, 3.0f, 0.5f));
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (RELEASE, 1), RELEASE, 0.1f, 3.0f, 0.5f));
    
    params.add (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID (TYPE_ONE, 1), TYPE_ONE, OSC_TYPES, 0));
    params.add (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID (TYPE_TWO, 1), TYPE_TWO, OSC_TYPES, 0));
    
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (REVERB_WET, 1), REVERB_WET, 0.01f, 1.0f, 0.5f));
    params.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID (ROOM, 1), ROOM, 0.01f, 1.0f, 0.5f));
    
    return params;
}
