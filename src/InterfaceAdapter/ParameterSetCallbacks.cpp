#include "ParameterSetCallbacks.h"
#include "../Framework/TapeStopInternalData.h"
#include "ParameterIndex.h"

namespace tapestop::interface_adapter {

FMOD_RESULT F_CALL TapeStop_SetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float value) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_STOP_TIME:
            state->params.stop_time = value;
            return FMOD_OK;
        case PARAM_START_TIME:
            state->params.start_time = value;
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALL TapeStop_SetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int value) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_SYNC_BEAT:
            state->params.sync_beat = static_cast<usecase::SyncBeat>(value);
            return FMOD_OK;
        case PARAM_CURVE:
            state->params.curve = static_cast<usecase::TapeCurve>(value);
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

FMOD_RESULT F_CALL TapeStop_SetParameterBool(FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL value) {
    if (!dsp_state || !dsp_state->plugindata) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<framework::TapeStopState*>(dsp_state->plugindata);

    switch (index) {
        case PARAM_TRIGGER:
            state->params.trigger = static_cast<bool>(value);
            return FMOD_OK;
        case PARAM_USE_SYNC:
            state->params.use_sync = static_cast<bool>(value);
            return FMOD_OK;
        case PARAM_ENABLE_FILTER:
            state->params.enable_filter = static_cast<bool>(value);
            return FMOD_OK;
    }

    return FMOD_ERR_INVALID_PARAM;
}

} // namespace tapestop::interface_adapter
