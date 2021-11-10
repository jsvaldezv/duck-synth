#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider sliderVolumen;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttachment;
    
    juce::ImageComponent background;
    juce::Image backgroundImage;
    
    SynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
