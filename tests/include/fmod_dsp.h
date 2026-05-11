#ifndef FMOD_DSP_H
#define FMOD_DSP_H

#include "fmod_common.h"

#define FMOD_MEMORY_NORMAL 0x00000000

typedef struct FMOD_DSP_STATE_FUNCTIONS {
    void* (*alloc)(unsigned int size, unsigned int type, const char* sourcestr);
    void (*free)(void* ptr, unsigned int type, const char* sourcestr);
    void (*getsamplerate)(struct FMOD_DSP_STATE *dsp_state, int *rate);
} FMOD_DSP_STATE_FUNCTIONS;

typedef struct FMOD_DSP_STATE {
    void* plugindata;
    FMOD_DSP_STATE_FUNCTIONS* functions;
} FMOD_DSP_STATE;

typedef struct FMOD_DSP_PARAMETER_DESC {
    char name[16];
} FMOD_DSP_PARAMETER_DESC;

typedef struct FMOD_DSP_BUFFER_ARRAY {
    int numbuffers;
    int* buffernumchannels;
    float** buffers;
} FMOD_DSP_BUFFER_ARRAY;

typedef enum {
    FMOD_DSP_PROCESS_PERFORM,
    FMOD_DSP_PROCESS_QUERY
} FMOD_DSP_PROCESS_OPERATION;

#define FMOD_DSP_INIT_PARAMDESC_BOOL(desc, name, label, description, defaultval, mapping) \
    /* Mock implementation */
#define FMOD_DSP_INIT_PARAMDESC_FLOAT(desc, name, label, description, minval, maxval, defaultval) \
    /* Mock implementation */
#define FMOD_DSP_INIT_PARAMDESC_INT(desc, name, label, description, minval, maxval, defaultval, goestoinf, mapping) \
    /* Mock implementation */

typedef void* (*FMOD_MEMORY_ALLOC_CALLBACK)(unsigned int size, unsigned int type, const char* sourcestr);
typedef void (*FMOD_MEMORY_FREE_CALLBACK)(void* ptr, unsigned int type, const char* sourcestr);

#endif
