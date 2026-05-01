#ifndef FMODTAPESTOPPLUGIN_PARAMETERDESC_H
#define FMODTAPESTOPPLUGIN_PARAMETERDESC_H
#include "fmod_common.h"
#include "fmod_dsp.h"
#include "ParameterIndex.h"

extern FMOD_DSP_PARAMETER_DESC s_Volume;
extern FMOD_DSP_PARAMETER_DESC* s_Params[NUM_PARAMETERS];

void InitParameterDescs();

#endif //FMODTAPESTOPPLUGIN_PARAMETERDESC_H
