#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class DuckSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    
    DuckSynthAudioProcessorEditor (DuckSynthAudioProcessor&);
    ~DuckSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void prepareSlider (juce::Slider&, juce::Label&, juce::String sliderID);

private:

    // Background
    juce::ImageComponent background;
    juce::Image backgroundImage;
    
    // Volume
    juce::Slider sliderVolumen;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttachment;
    juce::Label volLabel;
    
    // ADSR
    juce::Slider sliderAttack, sliderDecay, sliderSustain, sliderRelease;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, releaseAttachment;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    
    // Reverb
    juce::Slider sliderRoom, sliderWet;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> roomAttachment, wetAttachment;
    juce::Label roomLabel, wetLabel;
    
    // Oscillators
    juce::ComboBox oscOne, oscTwo;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscOneAttachment, oscTwoAttachment;
    
    DuckSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuckSynthAudioProcessorEditor)
};
