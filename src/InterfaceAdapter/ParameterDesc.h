#ifndef FMODTAPESTOPPLUGIN_PARAMETERDESC_H
#define FMODTAPESTOPPLUGIN_PARAMETERDESC_H

#include "fmod_dsp.h"
#include "ParameterIndex.h"

namespace tapestop::interface_adapter {

extern FMOD_DSP_PARAMETER_DESC s_Trigger;
extern FMOD_DSP_PARAMETER_DESC s_UseSync;
extern FMOD_DSP_PARAMETER_DESC s_StopTime;
extern FMOD_DSP_PARAMETER_DESC s_SyncBeat;
extern FMOD_DSP_PARAMETER_DESC s_StartTime;
extern FMOD_DSP_PARAMETER_DESC s_Curve;
extern FMOD_DSP_PARAMETER_DESC s_EnableFilter;

extern FMOD_DSP_PARAMETER_DESC* s_Params[NUM_PARAMETERS];

void InitParameterDescs();

} // namespace tapestop::interface_adapter

#endif //FMODTAPESTOPPLUGIN_PARAMETERDESC_H
