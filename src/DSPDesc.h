#ifndef FMODTAPESTOPPLUGIN_DSPDESC_H
#define FMODTAPESTOPPLUGIN_DSPDESC_H
#include "fmod_common.h"
#include "fmod_dsp.h"

#include "Export.h"
#include "DSPCallbacks.h"
#include "ParameterIndex.h"
#include "ParameterDesc.h"
#include "ParameterGetCallbacks.h"
#include "ParameterSetCallbacks.h"

/**
 * @brief DSPプラグインのDSPディスクリプションの宣言
 */
extern FMOD_DSP_DESCRIPTION tapestopDesc;

extern "C" {
    FMOD_EXPORT FMOD_DSP_DESCRIPTION* FMODGetDSPDescription();
}

#endif //FMODTAPESTOPPLUGIN_DSPDESC_H
