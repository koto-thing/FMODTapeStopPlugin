#include <iostream>
#include <cassert>
#include <cstring>
#include "InterfaceAdapter/ParameterGetCallbacks.h"
#include "InterfaceAdapter/ParameterIndex.h"
#include "Framework/TapeStopInternalData.h"

using namespace tapestop;

void test_null_dsp_state() {
    std::cout << "Running test_null_dsp_state..." << std::endl;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterFloat(nullptr, interface_adapter::PARAM_STOP_TIME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_null_plugindata() {
    std::cout << "Running test_null_plugindata..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    dsp_state.plugindata = nullptr;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterFloat(&dsp_state, interface_adapter::PARAM_STOP_TIME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_valid_parameter_stop_time() {
    std::cout << "Running test_valid_parameter_stop_time..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.stop_time = 1.23f;
    dsp_state.plugindata = &state;

    float value = 0.0f;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterFloat(&dsp_state, interface_adapter::PARAM_STOP_TIME, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == 1.23f);
    std::cout << "Passed!" << std::endl;
}

void test_valid_parameter_stop_time_null_pointers() {
    std::cout << "Running test_valid_parameter_stop_time_null_pointers..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.stop_time = 0.5f;
    dsp_state.plugindata = &state;

    // Test with null pointers for outputs
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterFloat(&dsp_state, interface_adapter::PARAM_STOP_TIME, nullptr, nullptr);
    assert(result == FMOD_OK);
    std::cout << "Passed!" << std::endl;
}

void test_invalid_parameter_index() {
    std::cout << "Running test_invalid_parameter_index..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.stop_time = 1.0f;
    dsp_state.plugindata = &state;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterFloat(&dsp_state, 999, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

int main() {
    test_null_dsp_state();
    test_null_plugindata();
    test_valid_parameter_stop_time();
    test_valid_parameter_stop_time_null_pointers();
    test_invalid_parameter_index();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
