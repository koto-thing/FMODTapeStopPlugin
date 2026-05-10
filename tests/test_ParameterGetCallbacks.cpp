#include <iostream>
#include <cassert>
#include <cstring>
#include "ParameterGetCallbacks.h"
#include "ParameterIndex.h"
#include "TapeStopInternalData.h"

void test_null_dsp_state() {
    std::cout << "Running test_null_dsp_state..." << std::endl;
    FMOD_RESULT result = TapeStop_GetParameterFloat(nullptr, TAPESTOP_PARAM_VOLUME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_null_plugindata() {
    std::cout << "Running test_null_plugindata..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    dsp_state.plugindata = nullptr;
    FMOD_RESULT result = TapeStop_GetParameterFloat(&dsp_state, TAPESTOP_PARAM_VOLUME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_valid_parameter_volume() {
    std::cout << "Running test_valid_parameter_volume..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    TapeStopState state;
    state.volume = 1.23f;
    dsp_state.plugindata = &state;

    float value = 0.0f;
    char valuestr[32];
    memset(valuestr, 0, sizeof(valuestr));

    FMOD_RESULT result = TapeStop_GetParameterFloat(&dsp_state, TAPESTOP_PARAM_VOLUME, &value, valuestr);
    assert(result == FMOD_OK);
    assert(value == 1.23f);
    assert(strcmp(valuestr, "1.23 x") == 0);
    std::cout << "Passed!" << std::endl;
}

void test_valid_parameter_volume_null_pointers() {
    std::cout << "Running test_valid_parameter_volume_null_pointers..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    TapeStopState state;
    state.volume = 0.5f;
    dsp_state.plugindata = &state;

    // Test with null pointers for outputs
    FMOD_RESULT result = TapeStop_GetParameterFloat(&dsp_state, TAPESTOP_PARAM_VOLUME, nullptr, nullptr);
    assert(result == FMOD_OK);
    std::cout << "Passed!" << std::endl;
}

void test_invalid_parameter_index() {
    std::cout << "Running test_invalid_parameter_index..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    TapeStopState state;
    state.volume = 1.0f;
    dsp_state.plugindata = &state;

    FMOD_RESULT result = TapeStop_GetParameterFloat(&dsp_state, 999, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

int main() {
    test_null_dsp_state();
    test_null_plugindata();
    test_valid_parameter_volume();
    test_valid_parameter_volume_null_pointers();
    test_invalid_parameter_index();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
