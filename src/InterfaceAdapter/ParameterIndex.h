#ifndef FMODTAPESTOPPLUGIN_PARAMETERINDEX_H
#define FMODTAPESTOPPLUGIN_PARAMETERINDEX_H

namespace tapestop::interface_adapter {

/**
 * @brief パラメーターインデックス
 */
enum ParameterIndex {
    PARAM_TRIGGER = 0,
    PARAM_USE_SYNC,
    PARAM_STOP_TIME,
    PARAM_SYNC_BEAT,
    PARAM_START_TIME,
    PARAM_CURVE,
    PARAM_ENABLE_FILTER,
    NUM_PARAMETERS
};

} // namespace tapestop::interface_adapter

#endif //FMODTAPESTOPPLUGIN_PARAMETERINDEX_H
