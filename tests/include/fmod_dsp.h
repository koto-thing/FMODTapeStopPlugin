#ifndef FMOD_DSP_H
#define FMOD_DSP_H

#include "fmod_common.h"
#include <string.h>

typedef struct FMOD_DSP_STATE {
    void* plugindata;
    struct FMOD_DSP_STATE_FUNCTIONS *functions;
} FMOD_DSP_STATE;

typedef struct FMOD_DSP_BUFFER_ARRAY {
    int numbuffers;
    int *buffernumchannels;
    unsigned int *bufferchannelmask;
    float **buffers;
    int speakermode;
} FMOD_DSP_BUFFER_ARRAY;

typedef enum {
    FMOD_DSP_PROCESS_PERFORM,
    FMOD_DSP_PROCESS_QUERY
} FMOD_DSP_PROCESS_OPERATION;

typedef void * (*FMOD_MEMORY_ALLOC_CALLBACK)(unsigned int size, unsigned int type, const char *sourcestr);
typedef void (*FMOD_MEMORY_FREE_CALLBACK)(void *ptr, unsigned int type, const char *sourcestr);

typedef struct FMOD_DSP_STATE_FUNCTIONS {
    FMOD_MEMORY_ALLOC_CALLBACK alloc;
    FMOD_MEMORY_FREE_CALLBACK free;
} FMOD_DSP_STATE_FUNCTIONS;

typedef struct FMOD_DSP_PARAMETER_DESC_FLOAT {
    float min;
    float max;
    float defaultval;
    int mapping;
} FMOD_DSP_PARAMETER_DESC_FLOAT;

typedef struct FMOD_DSP_PARAMETER_DESC {
    char name[16];
    char label[16];
    const char *description;
    int type;
    union {
        FMOD_DSP_PARAMETER_DESC_FLOAT floatdesc;
    };
} FMOD_DSP_PARAMETER_DESC;

#define FMOD_MEMORY_NORMAL 0

#define FMOD_DSP_INIT_PARAMDESC_FLOAT(_p, _name, _label, _desc, _min, _max, _defaultval) \
    memset(&(_p), 0, sizeof(FMOD_DSP_PARAMETER_DESC)); \
    strncpy((_p).name, _name, 15); \
    strncpy((_p).label, _label, 15); \
    (_p).description = _desc; \
    (_p).floatdesc.min = _min; \
    (_p).floatdesc.max = _max; \
    (_p).floatdesc.defaultval = _defaultval;

#endif
