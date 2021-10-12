#pragma once
#include <JuceHeader.h>

class synth_Sound : public juce::SynthesiserSound
{
public:
    
    synth_Sound();
    ~synth_Sound();
    
    bool appliesToNote (int midiNoteNumber) override;
    
    bool appliesToChannel (int midiChannel) override;
    
private:
    
};
