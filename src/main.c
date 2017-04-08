#include <stdio.h>
#include "portaudio.h"
#define SAMPLE_RATE (96000)
#typedef 

static int callback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
    

int start(int argn, char **args) {
    PaStream *s
    PaError err;
    err = Pa_Initialize();
    if (err != paNoError) goto error;
    err = Pa_OpenDefaultStream(s&, 0, 1, paFloat32, SAMPLE_RATE, 256,
                               callback, )
    if (err != paNoError) goto error;
    
error:
    printf("Error: %s\n", Pa_GetErrorText(err))
    return -1;
}
