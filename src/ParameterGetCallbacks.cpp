#include "ParameterGetCallbacks.h"

#include <cstdio>

#include "ParameterIndex.h"
#include "TapeStopInternalData.h"

/**
 * @brief DSPプラグインのパラメータ取得時のコールバック関数
 * @param dsp_state DSPの内部データ
 * @param index パラメータのインデックス
 * @param value 取得する値を格納するポインタ
 * @param valuestr 取得する値を文字列で格納するバッファ（32バイト以上必要）
 * @return 処理が成功した場合: FMOD_OK, それ以外の場合: FMOD_ERR_INVALID_PARAM
 */
FMOD_RESULT F_CALL TapeStop_GetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr) {
    if (!dsp_state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<TapeStopState*>(dsp_state->plugindata);
    if (!state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    switch (index) {
        case TAPESTOP_PARAM_VOLUME:
            if (value) *value = state->volume;
            if (valuestr) snprintf(valuestr, 32, "%.2f x", state->volume);
            break;

        default:
            return FMOD_ERR_INVALID_PARAM;
    }

    return FMOD_OK;
}