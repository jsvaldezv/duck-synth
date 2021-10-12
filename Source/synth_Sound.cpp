#include "synth_Sound.h"

synth_Sound::synth_Sound(){}

synth_Sound::~synth_Sound(){}

bool synth_Sound::appliesToNote (int midiNoteNumber)
{
    return true;
}

bool synth_Sound::appliesToChannel (int midiChannel)
{
    return true;
}
