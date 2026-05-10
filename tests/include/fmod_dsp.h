#ifndef FMOD_DSP_H
#define FMOD_DSP_H

#include "fmod_common.h"

typedef struct FMOD_DSP_STATE {
    void* plugindata;
} FMOD_DSP_STATE;

typedef struct FMOD_DSP_PARAMETER_DESC {
    char name[16];
} FMOD_DSP_PARAMETER_DESC;

#endif
