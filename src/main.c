#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#define SAMPLE_RATE (96000)

#define TRANSMIT_BUFFER 256

struct ChannelDescriptor {
    unsigned short base;
    unsigned short binSize;
    unsigned short binCount;
};

struct WireDescriptor {
    struct ChannelDescriptor *channels;
    unsigned char channelCount;
};

struct SoundUserData {
    unsigned short currentFrequency
};

PaStream *stream = NULL;
bool isPortAudioInitialized = false;

static int initialize() { /* HAS to check for PortAudio initialization first */
    if (!isPortAudioInitialized) {
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            fprintf(stderr, "Could not initialize PortAudio: %s\n", Pa_GetErrorText(err));
            return -1;
        }
        isPortAudioInitialized = true;
        return 0;
    }
    return -2;
}

static int transmissionCallback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
}

char *msgs[TRANSMIT_BUFFER];

int transmit(struct ChannelDescriptor channel, char *data, unsigned int length) {
    
}
