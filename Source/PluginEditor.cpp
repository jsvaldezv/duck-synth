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
    
    paintADSR();
    paintReverb();
    
    // OSCILADORES
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
    
    // VOLUMEN
    sliderVolumen.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderVolumen.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderVolumen);
    volumenAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "VOLUME_ID",
                                                                                               sliderVolumen);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&sliderVolumen, true);
    volLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    volLabel.setCentrePosition(sliderVolumen.getX() + 38, sliderVolumen.getY() - 5);
    addAndMakeVisible(volLabel);
    
    // LOOK AND FEEL
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
    oscOne.setBounds(90, 20, 100, 30);
    oscTwo.setBounds(210, 20, 100, 30);
    
    sliderAttack.setBounds(50, 100, 80, 80);
    sliderDecay.setBounds(125, 100, 80, 80);
    sliderSustain.setBounds(205, 100, 80, 80);
    sliderRelease.setBounds(280, 100, 80, 80);
    
    sliderRoom.setBounds(80, 200, 80, 80);
    sliderWet.setBounds(160, 200, 80, 80);
    sliderVolumen.setBounds(240, 200, 80, 80);
    
    background.setBounds(0, 0, getWidth(), getHeight());
}

void SynthAudioProcessorEditor::paintADSR()
{
    // ATTACK
    sliderAttack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderAttack.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderAttack);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "ATTACK_ID",
                                                                                               sliderAttack);
    
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.attachToComponent(&sliderAttack, true);
    attackLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    attackLabel.setCentrePosition(sliderAttack.getX() + 38, sliderAttack.getY() - 5);
    addAndMakeVisible(attackLabel);
    
    // SUSTAIN
    sliderSustain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderSustain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderSustain);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "SUSTAIN_ID",
                                                                                              sliderSustain);
    
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sliderSustain, true);
    sustainLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    sustainLabel.setCentrePosition(sliderSustain.getX() + 38, sliderSustain.getY() - 5);
    addAndMakeVisible(sustainLabel);
    
    // DECAY
    sliderDecay.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderDecay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderDecay);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                              "DECAY_ID",
                                                                                              sliderDecay);
    
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.attachToComponent(&sliderDecay, true);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    decayLabel.setCentrePosition(sliderDecay.getX() + 38, sliderDecay.getY() - 5);
    addAndMakeVisible(decayLabel);
    
    // RELEASE
    sliderRelease.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderRelease.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderRelease);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "RELEASE_ID",
                                                                                              sliderRelease);
    
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.attachToComponent(&sliderRelease, true);
    releaseLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    releaseLabel.setCentrePosition(sliderRelease.getX() + 38, sliderRelease.getY() - 5);
    addAndMakeVisible(releaseLabel);
}

void SynthAudioProcessorEditor::paintReverb()
{
    // WET
    sliderWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderWet.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderWet);
    wetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "WET_REVERB_ID",
                                                                                               sliderWet);
    
    wetLabel.setText("Amount", juce::dontSendNotification);
    wetLabel.attachToComponent(&sliderWet, true);
    wetLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    wetLabel.setCentrePosition(sliderWet.getX() + 38, sliderWet.getY() - 5);
    addAndMakeVisible(wetLabel);
    
    // ROOM
    sliderRoom.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderRoom.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderRoom);
    roomAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters,
                                                                                               "ROOM_ID",
                                                                                               sliderRoom);
    
    roomLabel.setText("Room", juce::dontSendNotification);
    roomLabel.attachToComponent(&sliderRoom, true);
    roomLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    roomLabel.setCentrePosition(sliderRoom.getX() + 38, sliderRoom.getY() - 5);
    addAndMakeVisible(roomLabel);
}
