#include "ParameterDesc.h"
#include <cstring>

namespace tapestop::interface_adapter {

FMOD_DSP_PARAMETER_DESC s_Trigger;
FMOD_DSP_PARAMETER_DESC s_UseSync;
FMOD_DSP_PARAMETER_DESC s_StopTime;
FMOD_DSP_PARAMETER_DESC s_SyncBeat;
FMOD_DSP_PARAMETER_DESC s_StartTime;
FMOD_DSP_PARAMETER_DESC s_Curve;
FMOD_DSP_PARAMETER_DESC s_EnableFilter;

FMOD_DSP_PARAMETER_DESC* s_Params[NUM_PARAMETERS];

static const char* s_SyncBeatNames[] = { "1/8", "1/4", "1/2", "1 Bar", "2 Bars" };
static const char* s_CurveNames[] = { "Linear", "Smooth", "SlowStart", "QuickCut" };

void InitParameterDescs() {
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    FMOD_DSP_INIT_PARAMDESC_BOOL(s_Trigger, "Trigger", "", "Trigger TapeStop effect", false, nullptr);
    s_Params[PARAM_TRIGGER] = &s_Trigger;

    FMOD_DSP_INIT_PARAMDESC_BOOL(s_UseSync, "BPM Sync", "", "Sync stop time to BPM", false, nullptr);
    s_Params[PARAM_USE_SYNC] = &s_UseSync;

    FMOD_DSP_INIT_PARAMDESC_FLOAT(s_StopTime, "Stop Time", "s", "Time to completely stop", 0.1f, 2.0f, 0.5f);
    s_Params[PARAM_STOP_TIME] = &s_StopTime;

    FMOD_DSP_INIT_PARAMDESC_INT(s_SyncBeat, "Stop Beat", "", "Beat length for stop time", 0, 4, 1, false, s_SyncBeatNames);
    s_Params[PARAM_SYNC_BEAT] = &s_SyncBeat;

    FMOD_DSP_INIT_PARAMDESC_FLOAT(s_StartTime, "Start Time", "s", "Time to return to normal speed", 0.1f, 2.0f, 0.5f);
    s_Params[PARAM_START_TIME] = &s_StartTime;

    FMOD_DSP_INIT_PARAMDESC_INT(s_Curve, "Curve", "", "Curve of pitch/speed change", 0, 3, 0, false, s_CurveNames);
    s_Params[PARAM_CURVE] = &s_Curve;

    FMOD_DSP_INIT_PARAMDESC_BOOL(s_EnableFilter, "Low-pass Effect", "", "Apply low-pass filter as speed drops", true, nullptr);
    s_Params[PARAM_ENABLE_FILTER] = &s_EnableFilter;
}

} // namespace tapestop::interface_adapter
