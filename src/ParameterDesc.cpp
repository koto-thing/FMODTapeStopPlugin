#include "ParameterDesc.h"

#include <cstring>

/**
 * @brief パラメータディスクリプション
 */
FMOD_DSP_PARAMETER_DESC s_Volume;
FMOD_DSP_PARAMETER_DESC* s_Params[NUM_PARAMETERS];

/**
 * @brief パラメータディスクリプションを初期化
 */
void InitParameterDescs() {
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    FMOD_DSP_INIT_PARAMDESC_FLOAT(s_Volume, "Volume", "x", "Linear gain of the TapeStop effect", 0.0f, 2.0f, 1.0f);
    s_Params[TAPESTOP_PARAM_VOLUME] = &s_Volume;
}