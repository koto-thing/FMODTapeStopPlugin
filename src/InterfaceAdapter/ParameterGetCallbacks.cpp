#include "ParameterGetCallbacks.h"
#include "../Framework/TapeStopInternalData.h"
#include "ParameterIndex.h"

namespace tapestop::interface_adapter {

FMOD_RESULT F_CALL TapeStop_GetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_STOP_TIME:
            if (value) *value = state->params.stop_time;
            return FMOD_OK;
        case PARAM_START_TIME:
            if (value) *value = state->params.start_time;
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALL TapeStop_GetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int *value, char *valuestr) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_SYNC_BEAT:
            if (value) *value = static_cast<int>(state->params.sync_beat);
            return FMOD_OK;
        case PARAM_CURVE:
            if (value) *value = static_cast<int>(state->params.curve);
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALL TapeStop_GetParameterBool(FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL *value, char *valuestr) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_TRIGGER:
            if (value) *value = static_cast<FMOD_BOOL>(state->params.trigger);
            return FMOD_OK;
        case PARAM_USE_SYNC:
            if (value) *value = static_cast<FMOD_BOOL>(state->params.use_sync);
            return FMOD_OK;
        case PARAM_ENABLE_FILTER:
            if (value) *value = static_cast<FMOD_BOOL>(state->params.enable_filter);
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

} // namespace tapestop::interface_adapter
