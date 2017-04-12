#include <stdio.h>
#include "portaudio.h"
#define SAMPLE_RATE (96000)

#typedef struct {
    float *sine;
    unsigned int sineSize;
    char phase;
} SinGenData;

PaStream *stream = NULL;

static int sinCallback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
    SinGenData data = (SinGenData) userData;
    
}

int start() {
    if (stream == NULL) {
        PaError err;
        err = Pa_Initialize();
        if (err != paNoError) goto error;
        SinGenData data;
        data->phase = 0x00;
        data->
        err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, callback, &data);
        if (err != paNoError) goto error;
        return 0;
error:
        printf("Error: %s\n", Pa_GetErrorText(err));
        return -1;
    }
}
