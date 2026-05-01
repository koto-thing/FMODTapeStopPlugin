#include "DSPDesc.h"

/**
 * @brief DSPプラグインのDSPディスクリプションの定義
 */
FMOD_DSP_DESCRIPTION tapestopDesc = {
    FMOD_PLUGIN_SDK_VERSION,    // プラグインSDKのバージョン
    "TapeStop",                 // プラグインの表示名
    0x00010000,                 // プラグインのバージョン
    1,                          // 入力バッファの数
    1,                          // 出力バッファの数
    TapeStop_Create,            // DSP生成時のコールバック
    TapeStop_Release,           // DSP解放時のコールバック
    nullptr,                    // DSPリセット時のコールバック
    nullptr,                    // DSP読み取り時のコールバック
    TapeStop_Process,           // DSP処理時のコールバック
    nullptr,                    // 位置設定時のコールバック
    NUM_PARAMETERS,             // パラメータの総数
    s_Params,                   // パラメータディスクリプションの配列
    TapeStop_SetParameterFloat, // setFloatによってパラメーターが設定されたときのコールバック
    nullptr,                    // setIntによってパラメータが設定されたときのコールバック
    nullptr,                    // setBoolによってパラメータが設定されたときのコールバック
    nullptr,                    // setDataによってパラメータが設定されたときのコールバック
    TapeStop_GetParameterFloat, // getFloatによってパラメータが取得されたときのコールバック
    nullptr,                    // getIntによってパラメータが取得されたときのコールバック
    nullptr,                    // getBoolによってパラメータが取得されたときのコールバック
    nullptr,                    // getDataによってパラメータが取得されたときのコールバック
    nullptr,                    // shouldiprocessによってプロセスするかどうかを決定するコールバック
    nullptr,                    // userdata
    nullptr,                    // DSPがロードor登録されたときに呼ばれるコールバック
    nullptr,                    // DSPがアンロードor登録されたときに呼ばれるコールバック
    nullptr,                    // ミキサー実行開始時に呼ばれるコールバック
};

extern "C" {
    FMOD_EXPORT FMOD_DSP_DESCRIPTION* FMODGetDSPDescription() {
        InitParameterDescs();
        return &tapestopDesc;
    }
}

