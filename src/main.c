#include <stdio.h>
#include "portaudio.h"
#define SAMPLE_RATE (96000)

#define MAX_REPEATS (16)
#define MAX_

#define OUTPUT_TYPE paFloat32

#typedef struct {
    unsigned int size;
    unsigned OUTPUT_TYPE *lookup;
} SinLookupTable

#typedef struct {
    SinLookupTable *lookup;
    unsigned double maxSamples;
    unsigned int sample;
    unsigned int freq;
    bool freeLookupTable;
} SinGenData;

PaStream *stream = NULL;
bool isPortAudioInitialized = false;

static SinGenData getSinGenData(const unsigned double freq,
                                const SinLookupTable *lookup) {
    SinGenData data; /* Shouldn't need to zero out, we set all properties */
    data->maxSamples = SAMPLE_RATE / freq;
    data->sample = 0;
    data->freq = freq;
    if (lookup == NULL) {
        data->lookup = genLookupTable(freq);
        data->freeLookupTable = true;
    } else {
        data->lookup = lookup;
        data->freeLookupTable = false;
    }
    return data;
}

static int sinCallback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
    SinGenData *data = (SinGenData *) userData;
    
}

int initialize() { /* HAS to check for PortAudio initialization first */
    if (!isPortAudioInitialized) {
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            fprintf(stderr, "Could not initialize PortAudio: %s\n", Pa_GetErrorText(err));
            return -1;
        }
        return 0;
    }
    return -2;
}

char 
