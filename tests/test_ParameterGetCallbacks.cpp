#include <iostream>
#include <cassert>
#include "ParameterGetCallbacks.h"
#include "ParameterIndex.h"
#include "TapeStopInternalData.h"

void test_null_dsp_state() {
    std::cout << "Running test_null_dsp_state..." << std::endl;
    FMOD_RESULT result = tapestop::interface_adapter::TapeStop_GetParameterFloat(
        nullptr, tapestop::interface_adapter::PARAM_STOP_TIME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_null_plugindata() {
    std::cout << "Running test_null_plugindata..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    dsp_state.plugindata = nullptr;
    FMOD_RESULT result = tapestop::interface_adapter::TapeStop_GetParameterFloat(
        &dsp_state, tapestop::interface_adapter::PARAM_STOP_TIME, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_valid_float_parameters() {
    std::cout << "Running test_valid_float_parameters..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    tapestop::framework::TapeStopState state;
    state.params.stop_time = 1.23f;
    state.params.start_time = 0.75f;
    dsp_state.plugindata = &state;

    float stop_time = 0.0f;
    float start_time = 0.0f;

    FMOD_RESULT result_stop = tapestop::interface_adapter::TapeStop_GetParameterFloat(
        &dsp_state, tapestop::interface_adapter::PARAM_STOP_TIME, &stop_time, nullptr);
    FMOD_RESULT result_start = tapestop::interface_adapter::TapeStop_GetParameterFloat(
        &dsp_state, tapestop::interface_adapter::PARAM_START_TIME, &start_time, nullptr);
    assert(result_stop == FMOD_OK);
    assert(result_start == FMOD_OK);
    assert(stop_time == 1.23f);
    assert(start_time == 0.75f);
    std::cout << "Passed!" << std::endl;
}

void test_valid_int_and_bool_parameters() {
    std::cout << "Running test_valid_int_and_bool_parameters..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    tapestop::framework::TapeStopState state;
    state.params.sync_beat = tapestop::usecase::SyncBeat::Half;
    state.params.curve = tapestop::usecase::TapeCurve::QuickCut;
    state.params.trigger = true;
    state.params.use_sync = true;
    state.params.enable_filter = false;
    dsp_state.plugindata = &state;

    int sync_beat = 0;
    int curve = 0;
    FMOD_BOOL trigger = 0;
    FMOD_BOOL use_sync = 0;
    FMOD_BOOL enable_filter = 1;

    FMOD_RESULT result_sync = tapestop::interface_adapter::TapeStop_GetParameterInt(
        &dsp_state, tapestop::interface_adapter::PARAM_SYNC_BEAT, &sync_beat, nullptr);
    FMOD_RESULT result_curve = tapestop::interface_adapter::TapeStop_GetParameterInt(
        &dsp_state, tapestop::interface_adapter::PARAM_CURVE, &curve, nullptr);
    FMOD_RESULT result_trigger = tapestop::interface_adapter::TapeStop_GetParameterBool(
        &dsp_state, tapestop::interface_adapter::PARAM_TRIGGER, &trigger, nullptr);
    FMOD_RESULT result_use_sync = tapestop::interface_adapter::TapeStop_GetParameterBool(
        &dsp_state, tapestop::interface_adapter::PARAM_USE_SYNC, &use_sync, nullptr);
    FMOD_RESULT result_filter = tapestop::interface_adapter::TapeStop_GetParameterBool(
        &dsp_state, tapestop::interface_adapter::PARAM_ENABLE_FILTER, &enable_filter, nullptr);

    assert(result_sync == FMOD_OK);
    assert(result_curve == FMOD_OK);
    assert(result_trigger == FMOD_OK);
    assert(result_use_sync == FMOD_OK);
    assert(result_filter == FMOD_OK);
    assert(sync_beat == static_cast<int>(tapestop::usecase::SyncBeat::Half));
    assert(curve == static_cast<int>(tapestop::usecase::TapeCurve::QuickCut));
    assert(trigger == 1);
    assert(use_sync == 1);
    assert(enable_filter == 0);
    std::cout << "Passed!" << std::endl;
}

void test_invalid_parameter_index() {
    std::cout << "Running test_invalid_parameter_index..." << std::endl;
    FMOD_DSP_STATE dsp_state;
    tapestop::framework::TapeStopState state;
    dsp_state.plugindata = &state;

    FMOD_RESULT result = tapestop::interface_adapter::TapeStop_GetParameterFloat(&dsp_state, 999, nullptr, nullptr);
    assert(result == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

int main() {
    test_null_dsp_state();
    test_null_plugindata();
    test_valid_float_parameters();
    test_valid_int_and_bool_parameters();
    test_invalid_parameter_index();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
