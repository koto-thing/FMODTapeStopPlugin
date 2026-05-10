#ifndef FMODTAPESTOPPLUGIN_PARAMETERGETCALLBACKS_H
#define FMODTAPESTOPPLUGIN_PARAMETERGETCALLBACKS_H

#include "fmod_dsp.h"

namespace tapestop::interface_adapter {

FMOD_RESULT F_CALL TapeStop_GetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr);
FMOD_RESULT F_CALL TapeStop_GetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int *value, char *valuestr);
FMOD_RESULT F_CALL TapeStop_GetParameterBool(FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL *value, char *valuestr);

} // namespace tapestop::interface_adapter

#endif //FMODTAPESTOPPLUGIN_PARAMETERGETCALLBACKS_H
