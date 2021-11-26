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
    
    void paintADSR();
    void paintReverb();

private:

    // VOLUME
    juce::Slider sliderVolumen;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttachment;
    juce::Label volLabel;
    
    // ADSR
    juce::Slider sliderAttack, sliderDecay, sliderSustain, sliderRelease;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, releaseAttachment;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    
    // REVERB
    juce::Slider sliderRoom, sliderWet;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> roomAttachment, wetAttachment;
    juce::Label roomLabel, wetLabel;
    
    // OSCILLATORS
    juce::ComboBox oscOne;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscOneAttachment;
    
    juce::ComboBox oscTwo;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscTwoAttachment;
    
    // BACKGROUND
    juce::ImageComponent background;
    juce::Image backgroundImage;
    
    SynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
