#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include "Framework/DSPCallbacks.h"
#include "Framework/TapeStopInternalData.h"
#include "InterfaceAdapter/ParameterDesc.h"

using namespace tapestop;

void test_TapeStop_Process_NullParams() {
    std::cout << "Running test_TapeStop_Process_NullParams..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};

    assert(framework::TapeStop_Process(nullptr, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    assert(framework::TapeStop_Process(&dsp_state, 1024, nullptr, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    assert(framework::TapeStop_Process(&dsp_state, 1024, &inBuffers, nullptr, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_ZeroBuffers() {
    std::cout << "Running test_TapeStop_Process_ZeroBuffers..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    framework::TapeStopState state;
    dsp_state.plugindata = &state;

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 0;
    outBuffers.buffers = nullptr;

    FMOD_RESULT result = framework::TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_ERR_INVALID_PARAM); // because engine is null here, but if we mock engine it would be OK
    std::cout << "Passed!" << std::endl;
}

int main() {
    test_TapeStop_Process_NullParams();
    test_TapeStop_Process_ZeroBuffers();
    std::cout << "All DSPCallbacks tests passed!" << std::endl;
    return 0;
}
