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

// TapeStop_GetParameterInt tests
void test_int_null_dsp_state();
void test_int_null_plugindata();
void test_int_valid_parameter_sync_beat();
void test_int_valid_parameter_curve();
void test_int_valid_parameter_null_pointers();
void test_int_invalid_parameter_index();

// TapeStop_GetParameterBool tests
void test_bool_null_dsp_state();
void test_bool_null_plugindata();
void test_bool_valid_parameter_trigger();
void test_bool_valid_parameter_use_sync();
void test_bool_valid_parameter_enable_filter();
void test_bool_valid_parameter_null_pointers();
void test_bool_invalid_parameter_index();

int main() {
    // Float tests
    test_null_dsp_state();
    test_null_plugindata();
    test_valid_parameter_stop_time();
    test_valid_parameter_stop_time_null_pointers();
    test_invalid_parameter_index();

    // Int tests
    test_int_null_dsp_state();
    test_int_null_plugindata();
    test_int_valid_parameter_sync_beat();
    test_int_valid_parameter_curve();
    test_int_valid_parameter_null_pointers();
    test_int_invalid_parameter_index();

    // Bool tests
    test_bool_null_dsp_state();
    test_bool_null_plugindata();
    test_bool_valid_parameter_trigger();
    test_bool_valid_parameter_use_sync();
    test_bool_valid_parameter_enable_filter();
    test_bool_valid_parameter_null_pointers();
    test_bool_invalid_parameter_index();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

// TapeStop_GetParameterInt tests
void test_int_null_dsp_state() {
    std::cout << "Running test_int_null_dsp_state..." << std::endl;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(nullptr, interface_adapter::PARAM_SYNC_BEAT, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_int_null_plugindata() {
    std::cout << "Running test_int_null_plugindata..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    dsp_state.plugindata = nullptr;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(&dsp_state, interface_adapter::PARAM_SYNC_BEAT, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_int_valid_parameter_sync_beat() {
    std::cout << "Running test_int_valid_parameter_sync_beat..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.sync_beat = usecase::SyncBeat::TwoBars;
    dsp_state.plugindata = &state;

    int value = 0;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(&dsp_state, interface_adapter::PARAM_SYNC_BEAT, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == static_cast<int>(usecase::SyncBeat::TwoBars));
    std::cout << "Passed!" << std::endl;
}

void test_int_valid_parameter_curve() {
    std::cout << "Running test_int_valid_parameter_curve..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.curve = usecase::TapeCurve::Smooth;
    dsp_state.plugindata = &state;

    int value = 0;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(&dsp_state, interface_adapter::PARAM_CURVE, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == static_cast<int>(usecase::TapeCurve::Smooth));
    std::cout << "Passed!" << std::endl;
}

void test_int_valid_parameter_null_pointers() {
    std::cout << "Running test_int_valid_parameter_null_pointers..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.sync_beat = usecase::SyncBeat::Half;
    dsp_state.plugindata = &state;

    // Test with null pointers for outputs
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(&dsp_state, interface_adapter::PARAM_SYNC_BEAT, nullptr, nullptr);
    assert(result == FMOD_OK);
    std::cout << "Passed!" << std::endl;
}

void test_int_invalid_parameter_index() {
    std::cout << "Running test_int_invalid_parameter_index..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.sync_beat = usecase::SyncBeat::Quarter;
    dsp_state.plugindata = &state;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterInt(&dsp_state, 999, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

// TapeStop_GetParameterBool tests
void test_bool_null_dsp_state() {
    std::cout << "Running test_bool_null_dsp_state..." << std::endl;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(nullptr, interface_adapter::PARAM_TRIGGER, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_bool_null_plugindata() {
    std::cout << "Running test_bool_null_plugindata..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    dsp_state.plugindata = nullptr;
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, interface_adapter::PARAM_TRIGGER, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_bool_valid_parameter_trigger() {
    std::cout << "Running test_bool_valid_parameter_trigger..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.trigger = true;
    dsp_state.plugindata = &state;

    FMOD_BOOL value = 0;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, interface_adapter::PARAM_TRIGGER, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == 1); // FMOD_BOOL is typically int, true is 1
    std::cout << "Passed!" << std::endl;
}

void test_bool_valid_parameter_use_sync() {
    std::cout << "Running test_bool_valid_parameter_use_sync..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.use_sync = false;
    dsp_state.plugindata = &state;

    FMOD_BOOL value = 1;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, interface_adapter::PARAM_USE_SYNC, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == 0); // false is 0
    std::cout << "Passed!" << std::endl;
}

void test_bool_valid_parameter_enable_filter() {
    std::cout << "Running test_bool_valid_parameter_enable_filter..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.enable_filter = true;
    dsp_state.plugindata = &state;

    FMOD_BOOL value = 0;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, interface_adapter::PARAM_ENABLE_FILTER, &value, nullptr);
    assert(result == FMOD_OK);
    assert(value == 1);
    std::cout << "Passed!" << std::endl;
}

void test_bool_valid_parameter_null_pointers() {
    std::cout << "Running test_bool_valid_parameter_null_pointers..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.trigger = true;
    dsp_state.plugindata = &state;

    // Test with null pointers for outputs
    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, interface_adapter::PARAM_TRIGGER, nullptr, nullptr);
    assert(result == FMOD_OK);
    std::cout << "Passed!" << std::endl;
}

void test_bool_invalid_parameter_index() {
    std::cout << "Running test_bool_invalid_parameter_index..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    framework::TapeStopState state;
    state.params.trigger = true;
    dsp_state.plugindata = &state;

    FMOD_RESULT result = interface_adapter::TapeStop_GetParameterBool(&dsp_state, 999, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}
