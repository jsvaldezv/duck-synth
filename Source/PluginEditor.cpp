#include "PluginProcessor.h"
#include "PluginEditor.h"

DuckSynthAudioProcessorEditor::DuckSynthAudioProcessorEditor (DuckSynthAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Background
    backgroundImage = juce::ImageCache::getFromMemory (BinaryData::back_jpeg, BinaryData::back_jpegSize);
    background.setImage (backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible (background);
    
    // Sliders
    prepareSlider (sliderAttack, attackLabel, ATTACK);
    prepareSlider (sliderDecay, decayLabel, DECAY);
    prepareSlider (sliderSustain, sustainLabel, SUSTAIN);
    prepareSlider (sliderRelease, releaseLabel, RELEASE);
    prepareSlider (sliderWet, wetLabel, REVERB_WET);
    prepareSlider (sliderRoom, roomLabel, ROOM);
    prepareSlider (sliderVolumen, volLabel, VOLUME);
    
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), ATTACK, sliderAttack);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), DECAY, sliderDecay);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), SUSTAIN, sliderSustain);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), RELEASE, sliderRelease);
    wetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), REVERB_WET, sliderWet);
    roomAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), ROOM, sliderRoom);
    volumenAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), VOLUME, sliderVolumen);
    
    // Oscillators
    int i = 1;
    for (auto& choice : OSC_TYPES)
    {
        oscOne.addItem (choice, i);
        oscTwo.addItem (choice, i);
        
        i++;
    }
    
    oscOne.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (oscOne);
    
    oscTwo.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (oscTwo);
    
    oscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.getAPVTS(), TYPE_ONE, oscOne);
    oscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.getAPVTS(), TYPE_TWO, oscTwo);
    
    // L&F
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::yellow);
    getLookAndFeel().setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (226, 223, 0));
    getLookAndFeel().setColour (juce::ComboBox::backgroundColourId, juce::Colour (226, 223, 0));
    getLookAndFeel().setColour (juce::ComboBox::textColourId, juce::Colours::black);
    getLookAndFeel().setColour (juce::ComboBox::arrowColourId, juce::Colours::black);
    getLookAndFeel().setColour (juce::ComboBox::buttonColourId, juce::Colours::red);
    
    setSize (400, 300);
}

DuckSynthAudioProcessorEditor::~DuckSynthAudioProcessorEditor() {}

void DuckSynthAudioProcessorEditor::prepareSlider (juce::Slider& slider, juce::Label& label, juce::String sliderID)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible (slider);
    
    label.setText (sliderID, juce::dontSendNotification);
    label.attachToComponent (&slider, false);
    label.setColour (juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void DuckSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Synth", getLocalBounds(), juce::Justification::centred, 1);
}

void DuckSynthAudioProcessorEditor::resized()
{
    background.setBounds (getLocalBounds());
    
    oscOne.setBounds (90, 20, 100, 30);
    oscTwo.setBounds (210, 20, 100, 30);
    
    sliderAttack.setBounds (50, 100, 80, 80);
    sliderDecay.setBounds (125, 100, 80, 80);
    sliderSustain.setBounds (205, 100, 80, 80);
    sliderRelease.setBounds (280, 100, 80, 80);
    
    sliderRoom.setBounds (80, 200, 80, 80);
    sliderWet.setBounds (160, 200, 80, 80);
    sliderVolumen.setBounds (240, 200, 80, 80);
}
