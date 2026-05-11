#include "DSPDesc.h"
#include "DSPCallbacks.h"
#include "../InterfaceAdapter/ParameterDesc.h"
#include "../InterfaceAdapter/ParameterIndex.h"
#include "../InterfaceAdapter/ParameterSetCallbacks.h"
#include "../InterfaceAdapter/ParameterGetCallbacks.h"

namespace tapestop::framework {

FMOD_DSP_DESCRIPTION tapestopDesc = {
    FMOD_PLUGIN_SDK_VERSION,
    "TapeStop",
    0x00010000,
    1,
    1,
    TapeStop_Create,
    TapeStop_Release,
    TapeStop_Reset,
    nullptr,
    TapeStop_Process,
    nullptr,
    interface_adapter::NUM_PARAMETERS,
    interface_adapter::s_Params,
    interface_adapter::TapeStop_SetParameterFloat,
    interface_adapter::TapeStop_SetParameterInt,
    interface_adapter::TapeStop_SetParameterBool,
    nullptr,
    interface_adapter::TapeStop_GetParameterFloat,
    interface_adapter::TapeStop_GetParameterInt,
    interface_adapter::TapeStop_GetParameterBool,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};

} // namespace tapestop::framework

extern "C" {
    F_EXPORT FMOD_DSP_DESCRIPTION* FMODGetDSPDescription() {
        tapestop::interface_adapter::InitParameterDescs();
        return &tapestop::framework::tapestopDesc;
    }
}
