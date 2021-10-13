#include "synth_Voice.h"

synth_Voice::synth_Voice()
{

}

synth_Voice::~synth_Voice()
{
    
}

bool synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    myADSR.noteOn();
}

void synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    myADSR.noteOff();
}

void synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void synth_Voice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    mySampleRate = sampleRate;
    
    myADSR.setSampleRate(mySampleRate);
}

void synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        for(int i = 0; i < outputBuffer.getNumSamples(); i++)
        {
            // OBTENIENDO VALOR DE SAMPLE QUE ENTRA AL PLUGIN
            float sample = outputBuffer.getReadPointer(channel)[i];
            
            // CALCULANDO VALOR DE SINUSOIDAL
            float sinValue = sin(2.0f * pi * fase[channel]);
            
            // MOVIENDO LA FASE
            fase[channel] += frequency * (1.0f / getSampleRate());
            
            // CHECANDO QUE LA FASE NO SEA MAYOR A 1
            if(fase[channel] >= 1.0f)
                fase[channel] = 0.0f;
            
            // SUMAR VALOR DE SINUSOIDAL A SAMPLE
            sample += sinValue;
            
            // REGRESANDO SAMPLES MODIFICADOS A LA SALIDA DEL PLUGIN
            outputBuffer.getWritePointer(channel)[i] = (0.8f * sample);
        }
    }
    
    myADSR.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
