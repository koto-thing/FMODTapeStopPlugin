#ifndef FMOD_DSP_H
#define FMOD_DSP_H

#include "fmod_common.h"

typedef struct FMOD_DSP_STATE {
    void* plugindata;
    struct FMOD_DSP_STATE_FUNCTIONS* functions;
} FMOD_DSP_STATE;

typedef enum FMOD_MEMORY_TYPE {
    FMOD_MEMORY_NORMAL = 0
} FMOD_MEMORY_TYPE;

typedef void* (*FMOD_MEMORY_ALLOC_CALLBACK)(unsigned int, FMOD_MEMORY_TYPE, const char*);
typedef void (*FMOD_MEMORY_FREE_CALLBACK)(void*, FMOD_MEMORY_TYPE, const char*);

typedef struct FMOD_DSP_STATE_FUNCTIONS {
    FMOD_MEMORY_ALLOC_CALLBACK alloc;
    FMOD_MEMORY_FREE_CALLBACK free;
} FMOD_DSP_STATE_FUNCTIONS;

typedef struct FMOD_DSP_PARAMETER_DESC {
    char name[16];
} FMOD_DSP_PARAMETER_DESC;

#endif
