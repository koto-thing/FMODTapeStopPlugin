#ifndef FMODTAPESTOPPLUGIN_DSPCALLBACKS_H
#define FMODTAPESTOPPLUGIN_DSPCALLBACKS_H
#include "fmod_common.h"
#include "fmod_dsp.h"

FMOD_RESULT F_CALL TapeStop_Create(FMOD_DSP_STATE* dsp_state);
FMOD_RESULT F_CALL TapeStop_Release(FMOD_DSP_STATE* dsp_state);
FMOD_RESULT F_CALL TapeStop_Process(FMOD_DSP_STATE* dsp_state, unsigned int length, const FMOD_DSP_BUFFER_ARRAY* inBuffers, FMOD_DSP_BUFFER_ARRAY* outBuffers, FMOD_BOOL inputsIdle, FMOD_DSP_PROCESS_OPERATION op);

#endif //FMODTAPESTOPPLUGIN_DSPCALLBACKS_H
