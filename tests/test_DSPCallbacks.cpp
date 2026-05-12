#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include "Framework/DSPCallbacks.h"
#include "Framework/TapeStopInternalData.h"
#include "InterfaceAdapter/ParameterDesc.h"

using namespace tapestop;


// Mock allocators for testing
static int alloc_count = 0;
static bool fail_alloc_on_count = false;
static int fail_count_target = 0;

void* mock_alloc(unsigned int size, unsigned int type, const char* sourcestr) {
    if (fail_alloc_on_count && alloc_count == fail_count_target) {
        alloc_count++;
        return nullptr;
    }
    alloc_count++;
    return malloc(size);
}

void mock_free(void* ptr, unsigned int type, const char* sourcestr) {
    free(ptr);
}

void mock_getsamplerate(FMOD_DSP_STATE* dsp_state, int* rate) {
    if (rate) *rate = 48000;
}

void test_TapeStop_Create_NullState() {
    std::cout << "Running test_TapeStop_Create_NullState..." << std::endl;
    assert(framework::TapeStop_Create(nullptr) == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Create_MissingFunctions() {
    std::cout << "Running test_TapeStop_Create_MissingFunctions..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    assert(framework::TapeStop_Create(&dsp_state) == FMOD_ERR_INTERNAL);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Create_MissingAlloc() {
    std::cout << "Running test_TapeStop_Create_MissingAlloc..." << std::endl;
    FMOD_DSP_STATE_FUNCTIONS funcs = {0};
    FMOD_DSP_STATE dsp_state = {0};
    dsp_state.functions = &funcs;

    assert(framework::TapeStop_Create(&dsp_state) == FMOD_ERR_INTERNAL);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Create_StateAllocFailure() {
    std::cout << "Running test_TapeStop_Create_StateAllocFailure..." << std::endl;
    FMOD_DSP_STATE_FUNCTIONS funcs = {0};
    funcs.alloc = mock_alloc;
    funcs.free = mock_free;
    FMOD_DSP_STATE dsp_state = {0};
    dsp_state.functions = &funcs;

    alloc_count = 0;
    fail_alloc_on_count = true;
    fail_count_target = 0; // Fail the first allocation (TapeStopState)

    assert(framework::TapeStop_Create(&dsp_state) == FMOD_ERR_MEMORY);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Create_EngineAllocFailure() {
    std::cout << "Running test_TapeStop_Create_EngineAllocFailure..." << std::endl;
    FMOD_DSP_STATE_FUNCTIONS funcs = {0};
    funcs.alloc = mock_alloc;
    funcs.free = mock_free;
    funcs.getsamplerate = mock_getsamplerate;
    FMOD_DSP_STATE dsp_state = {0};
    dsp_state.functions = &funcs;

    alloc_count = 0;
    fail_alloc_on_count = true;
    fail_count_target = 1; // Fail the second allocation (TapeStopEngine)

    assert(framework::TapeStop_Create(&dsp_state) == FMOD_ERR_MEMORY);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Create_Success() {
    std::cout << "Running test_TapeStop_Create_Success..." << std::endl;
    FMOD_DSP_STATE_FUNCTIONS funcs = {0};
    funcs.alloc = mock_alloc;
    funcs.free = mock_free;
    funcs.getsamplerate = mock_getsamplerate;
    FMOD_DSP_STATE dsp_state = {0};
    dsp_state.functions = &funcs;

    alloc_count = 0;
    fail_alloc_on_count = false;

    assert(framework::TapeStop_Create(&dsp_state) == FMOD_OK);
    assert(dsp_state.plugindata != nullptr);

    // Test Release
    assert(framework::TapeStop_Release(&dsp_state) == FMOD_OK);
    assert(dsp_state.plugindata == nullptr);
    std::cout << "Passed!" << std::endl;
}

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
    test_TapeStop_Create_NullState();
    test_TapeStop_Create_MissingFunctions();
    test_TapeStop_Create_MissingAlloc();
    test_TapeStop_Create_StateAllocFailure();
    test_TapeStop_Create_EngineAllocFailure();
    test_TapeStop_Create_Success();
    test_TapeStop_Process_NullParams();
    test_TapeStop_Process_ZeroBuffers();
    std::cout << "All DSPCallbacks tests passed!" << std::endl;
    return 0;
}
