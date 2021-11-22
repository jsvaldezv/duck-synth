#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::back_jpeg,
                                                      BinaryData::back_jpegSize);
    
    background.setImage(backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(background);
    
    oscOne.addItem("Sine", 1);
    oscOne.addItem("Triangle", 2);
    oscOne.addItem("Square", 3);
    oscOne.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oscOne);
    oscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters,
                                                                                                "TYPE_ONE_ID",
                                                                                                oscOne);
    
    oscTwo.addItem("Sine", 1);
    oscTwo.addItem("Triangle", 2);
    oscTwo.addItem("Square", 3);
    oscTwo.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oscTwo);
    oscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters,
                                                                                                "TYPE_TWO_ID",
                                                                                                oscTwo);
    
    sliderAttack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderAttack.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderAttack);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "ATTACK_ID",
                                                                                               sliderAttack);
    
    sliderSustain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderSustain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderSustain);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "SUSTAIN_ID",
                                                                                              sliderSustain);
    
    sliderDecay.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderDecay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderDecay);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                              "DECAY_ID",
                                                                                              sliderDecay);
    
    sliderRelease.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderRelease.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderRelease);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "RELEASE_ID",
                                                                                              sliderRelease);
    
    sliderWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderWet.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderWet);
    wetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "WET_REVERB_ID",
                                                                                               sliderWet);
    
    sliderRoom.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderRoom.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderRoom);
    roomAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "ROOM_ID",
                                                                                               sliderRoom);
    
    sliderVolumen.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderVolumen.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderVolumen);
    volumenAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "VOLUME_ID",
                                                                                               sliderVolumen);
    
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::yellow);
    getLookAndFeel().setColour (juce::Slider::rotarySliderFillColourId, juce::Colour(226, 223, 0));
    
    getLookAndFeel().setColour (juce::ComboBox::backgroundColourId, juce::Colour(226, 223, 0));
    getLookAndFeel().setColour (juce::ComboBox::textColourId, juce::Colours::black);
    getLookAndFeel().setColour (juce::ComboBox::arrowColourId, juce::Colours::black);
    getLookAndFeel().setColour (juce::ComboBox::buttonColourId, juce::Colours::red);
    
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor(){}

void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Synth", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
    oscOne.setBounds(90, 50, 100, 30);
    oscTwo.setBounds(210, 50, 100, 30);
    
    sliderAttack.setBounds(50, 100, 80, 80);
    sliderDecay.setBounds(125, 100, 80, 80);
    sliderSustain.setBounds(205, 100, 80, 80);
    sliderRelease.setBounds(280, 100, 80, 80);
    
    sliderRoom.setBounds(80, 200, 80, 80);
    sliderWet.setBounds(160, 200, 80, 80);
    sliderVolumen.setBounds(240, 200, 80, 80);
    
    background.setBounds(0, 0, getWidth(), getHeight());
}
