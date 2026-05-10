#include "DSPCallbacks.h"

#include <algorithm>
#include <cstring>

#include "ParameterDesc.h"
#include "TapeStopInternalData.h"

/**
 * DSPプラグインのインスタンス生成時のコールバック関数
 * @param dsp_state
 * @return
 */
FMOD_RESULT F_CALL TapeStop_Create(FMOD_DSP_STATE *dsp_state) {
    if (!dsp_state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    InitParameterDescs();

    // dsp_stateのfunctionsが有効かどうかを確認
    if (!dsp_state->functions) {
        return FMOD_ERR_INTERNAL;
    }

    // TapeStopのインスタンスを作成し、初期化する
    FMOD_MEMORY_ALLOC_CALLBACK alloc_callback = dsp_state->functions->alloc;
    if (!alloc_callback) {
        return FMOD_ERR_INTERNAL;
    }

    // メモリを確保
    auto *state = (TapeStopState*)alloc_callback(sizeof(TapeStopState), FMOD_MEMORY_NORMAL, "DSPCallbacks.cpp");
    if (state == nullptr) {
        return FMOD_ERR_MEMORY;
    }

    // dsp_stateにポインタを返す
    dsp_state->plugindata = state;

    // デフォルトのビット深度を設定
    state->volume = s_Volume.floatdesc.defaultval;

    // 正常終了を返す
    return FMOD_OK;
}

FMOD_RESULT F_CALL TapeStop_Release(FMOD_DSP_STATE *dsp_state) {
    if (!dsp_state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    if (!dsp_state->functions) {
        return FMOD_ERR_INTERNAL;
    }

    // TapeStopのインスタンスを取得
    FMOD_MEMORY_FREE_CALLBACK free_callback = dsp_state->functions->free;
    if (!free_callback) {
        return FMOD_ERR_INTERNAL;
    }

    // TapeStopのインスタンスを取得
    auto *state = static_cast<TapeStopState*>(dsp_state->plugindata);
    if (state) {
        free_callback(state, FMOD_MEMORY_NORMAL, "DSPCallbacks.cpp");
    }

    // 内部データもクリアする
    dsp_state->plugindata = nullptr;

    return FMOD_OK;
}

/* ---DSPプラグインのプロセス関数--- */
FMOD_RESULT F_CALL TapeStop_Process(FMOD_DSP_STATE* dsp_state, unsigned int length,
    const FMOD_DSP_BUFFER_ARRAY *inBuffers, FMOD_DSP_BUFFER_ARRAY *outBuffers,
    FMOD_BOOL inputsIdle, FMOD_DSP_PROCESS_OPERATION op) {

    // 内部データを取得
    if (!dsp_state || !inBuffers || !outBuffers) {
        return FMOD_ERR_INVALID_PARAM;
    }

    auto *state = static_cast<TapeStopState*>(dsp_state->plugindata);
    if (!state) {
        return FMOD_ERR_INVALID_PARAM;
    }

    // 入力バッファがない場合、出力バッファを0で埋める
    if (outBuffers->numbuffers == 0 || outBuffers->buffers == nullptr) {
        return FMOD_OK;
    }

    // 出力バッファがない場合、入力バッファを無視して0で埋める
    if (inBuffers->numbuffers == 0 || inBuffers->buffers == nullptr) {
        for (int i = 0 ; i < outBuffers->numbuffers ; ++i) {
            const int chs = outBuffers->buffernumchannels[i];
            float *out = outBuffers->buffers[i];
            for (unsigned int k = 0 ; k < length * static_cast<unsigned int>(chs) ; ++k) {
                out[k] = 0.0f;
            }
        }

        return FMOD_OK;
    }

    // 入力が待機状態の場合、出力バッファを0で埋める
    if (inputsIdle) {
        for (int i = 0 ; i < outBuffers->numbuffers ; ++i) {
            const int chs = outBuffers->buffernumchannels[i];
            float *out = outBuffers->buffers[i];
            for (unsigned int k = 0 ; k < length * static_cast<unsigned int>(chs) ; ++k) {
                out[k] = 0.0f;
            }
        }

        return FMOD_OK;
    }

    const float gain = state->volume;

    // FMOD_DSP_PROCESS_PERFORMの場合のみエフェクト処理を入れる
    if (op == FMOD_DSP_PROCESS_PERFORM) {
        const int nb = std::min(inBuffers->numbuffers, outBuffers->numbuffers);
        for (int i = 0 ; i < nb ; ++i) {
            const int chs = std::min(inBuffers->buffernumchannels[i], outBuffers->buffernumchannels[i]);
            const float *in = inBuffers->buffers[i];
            float *out = outBuffers->buffers[i];
            for (unsigned int j = 0 ; j < length * static_cast<unsigned int>(chs) ; ++j) {
                out[j] = in[j] * gain;
            }
        }
    }
    // FMOD_DSP_PROCESS_QUERYの場合、単純にバッファをコピーする
    else {
        const int nb = std::min(inBuffers->numbuffers, outBuffers->numbuffers);
        for (int i = 0 ; i < nb ; ++i) {
            const int chs = std::min(inBuffers->buffernumchannels[i], outBuffers->buffernumchannels[i]);
            const float *in = inBuffers->buffers[i];
            float *out = outBuffers->buffers[i];
            std::memcpy(out, in, sizeof(float) * length * static_cast<unsigned int>(chs));
        }
    }

    return FMOD_OK;
}