#ifndef FMODTAPESTOPPLUGIN_PARAMETERSETCALLBACKS_H
#define FMODTAPESTOPPLUGIN_PARAMETERSETCALLBACKS_H

#include "fmod_dsp.h"

namespace tapestop::interface_adapter {

FMOD_RESULT F_CALL TapeStop_SetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float value);
FMOD_RESULT F_CALL TapeStop_SetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int value);
FMOD_RESULT F_CALL TapeStop_SetParameterBool(FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL value);

} // namespace tapestop::interface_adapter

#endif //FMODTAPESTOPPLUGIN_PARAMETERSETCALLBACKS_H
