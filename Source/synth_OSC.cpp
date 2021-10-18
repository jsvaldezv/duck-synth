#include "synth_OSC.h"

synth_OSC::synth_OSC(){}

synth_OSC::~synth_OSC(){}

void synth_OSC::prepareOsc(float inSampleRate)
{
    mySampleRate = inSampleRate;
}

void synth_OSC::setFrequency(float inFreq)
{
    frequency = inFreq;
}

void synth_OSC::processOSC(float* inAudio, float* outAudio, int inNumSamples)
{
    for(int i = 0; i < inNumSamples; i++)
    {
        // OBTENIENDO VALOR DE SAMPLE QUE ENTRA AL PLUGIN
        float sample = inAudio[i];
        
        // CALCULANDO VALOR DE SINUSOIDAL
        float sinValue = sin(2.0f * pi * fase);
        
        // MOVIENDO LA FASE
        fase += frequency * (1.0f / mySampleRate);
        
        // CHECANDO QUE LA FASE NO SEA MAYOR A 1
        if(fase >= 1.0f)
            fase = 0.0f;
        
        // SUMAR VALOR DE SINUSOIDAL A SAMPLE
        sample += sinValue;
        
        outAudio[i] = (0.5f * sample);
    }
}
