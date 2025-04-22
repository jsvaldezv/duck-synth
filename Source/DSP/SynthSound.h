#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    
    SynthSound() = default;
    
    bool appliesToNote (int midiNoteNumber)
    {
        return true;
    }

    bool appliesToChannel (int midiChannel)
    {
        return true;
    }

};
