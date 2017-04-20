#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#define SAMPLE_RATE (96000)

#define TRANSMIT_BUFFER 256

#define MAX_SIN_BUFFER_CYCLES (32)
#define MAX_EXPECTED_SIN_OFFSET (0.05)

struct SinBuffer {
    unsigned short freq;
    unsigned short size;
    paFloat32 *data;
};

struct ChannelDescriptor {
    SinBuffer *buffers;
    unsigned short base;
    unsigned short binSize;
    unsigned short binCount;
};

struct WireDescriptor {
    struct ChannelDescriptor *channels;
    unsigned char channelCount;
};

struct SoundUserData {
    unsigned long duration;
    unsigned short point;
    struct SinBuffer *buffer;
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

static struct SinBuffer getSinBuffer(unsigned short freq) {
    struct SinBuffer buffer;
    buffer.freq = freq;
    buffer.size = 0;
    unsigned char cycles = 0;
    double samplesPerFreq = SAMPLE_RATE / ((double) freq);
    unsigned short fillSize = floor(samplesPerFreq + 0.5);
    buffer.data = (paFloat32 *) malloc(sizeof(paFloat32) * fillSize);
    double sample = 0;
    while (cycles < MAX_SIN_BUFFER_CYCLES) {
         if (buffer.size == fillSize) {
             fillSize = fillSize * 2;
             buffer.data = realloc((void *) buffer.data, sizeof(paFloat32) * fillSize);
         }
         buffer.data[buffer.size++] = sin(2 * M_PI * (sample++) / samplesPerFreq);
         if (sample > samplesPerFreq) {
             sample = sample - samplesPerFreq;
             ++cycles;
         } else if (sample == samplesPerFreq) {
             break;
         }
    }
    if (buffer.size ~= fillSize) {
        buffer.data = realloc((void *) buffer.data, sizeof(paFloat32) * buffer.size);
    }
    return buffer;
}

static void addBuffersToChannel(ChannelDescriptor *channel) {
    if (channel->buffers == NULL) {
        channel->buffers = (struct SinBuffer *) malloc(sizeof(struct SinBuffer) * channel->binCount);
        unsigned short freq = channel->base;
        for (unsigned short bin = 0; bin < (channel->binCount); ++bin) {
            channel->buffers[bin] = getSinBuffer(freq);
            freq += channel->binSize;
        }
    }
}

static void removeChannelBuffers(ChannelDescriptor *channel) {
    if (channel->buffers != NULL) {
        for (unsigned short bin = 0; bin < (channel->binCount); ++bin) {
            free(channel->buffers[bin].data);
            channel->buffers[bin].data = NULL;
        }
        free(channel->buffers);
        channel->buffers = NULL;
    }
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
