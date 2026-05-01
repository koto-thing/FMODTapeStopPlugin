#include "ParameterSetCallbacks.h"

#include <algorithm>

#include "ParameterDesc.h"
#include "ParameterIndex.h"
#include "TapeStopInternalData.h"

FMOD_RESULT F_CALL TapeStop_SetParameterFloat(FMOD_DSP_STATE* dsp_state, int index, float value) {
    if (!dsp_state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<TapeStopState*>(dsp_state->plugindata);
    if (!state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    switch (index) {
        case TAPESTOP_PARAM_VOLUME:
            value = std::clamp(value, 0.0f, 2.0f);
            state->volume = value;
            break;

        default:
            return FMOD_ERR_INVALID_PARAM;
    }

    return FMOD_OK;
}
