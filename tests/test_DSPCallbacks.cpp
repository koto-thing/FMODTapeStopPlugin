#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include "DSPCallbacks.h"
#include "TapeStopInternalData.h"
#include "ParameterDesc.h"

void test_TapeStop_Process_NullParams() {
    std::cout << "Running test_TapeStop_Process_NullParams..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};

    assert(TapeStop_Process(nullptr, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    assert(TapeStop_Process(&dsp_state, 1024, nullptr, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    assert(TapeStop_Process(&dsp_state, 1024, &inBuffers, nullptr, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM) == FMOD_ERR_INVALID_PARAM);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_ZeroBuffers() {
    std::cout << "Running test_TapeStop_Process_ZeroBuffers..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {1.0f};
    dsp_state.plugindata = &state;

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 0;
    outBuffers.buffers = nullptr;

    FMOD_RESULT result = TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_OK);
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_ZeroLength() {
    std::cout << "Running test_TapeStop_Process_ZeroLength..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {0.5f};
    dsp_state.plugindata = &state;

    float inData[1024];
    float outData[1024];
    for(int i=0; i<1024; ++i) {
        inData[i] = 1.0f;
        outData[i] = 0.0f;
    }
    float* inBuffersPtr[] = { inData };
    float* outBuffersPtr[] = { outData };
    int numChannels[] = { 1 };

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    inBuffers.numbuffers = 1;
    inBuffers.buffers = inBuffersPtr;
    inBuffers.buffernumchannels = numChannels;

    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 1;
    outBuffers.buffers = outBuffersPtr;
    outBuffers.buffernumchannels = numChannels;

    // length = 0 should work fine and not modify any data
    FMOD_RESULT result = TapeStop_Process(&dsp_state, 0, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_OK);
    for(int i=0; i<1024; ++i) {
        assert(outData[i] == 0.0f);
    }
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_InputsIdle() {
    std::cout << "Running test_TapeStop_Process_InputsIdle..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {1.0f};
    dsp_state.plugindata = &state;

    float outData[1024];
    for(int i=0; i<1024; ++i) outData[i] = 1.0f;
    float* buffers[] = { outData };
    int numChannels[] = { 1 };

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 1;
    outBuffers.buffers = buffers;
    outBuffers.buffernumchannels = numChannels;

    // inputsIdle = FMOD_TRUE should zero the output
    FMOD_RESULT result = TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_TRUE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_OK);
    for(int i=0; i<1024; ++i) {
        assert(outData[i] == 0.0f);
    }
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_EmptyInBuffers() {
    std::cout << "Running test_TapeStop_Process_EmptyInBuffers..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {1.0f};
    dsp_state.plugindata = &state;

    float outData[1024];
    for(int i=0; i<1024; ++i) outData[i] = 1.0f;
    float* buffers[] = { outData };
    int numChannels[] = { 1 };

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    inBuffers.numbuffers = 0;
    inBuffers.buffers = nullptr;

    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 1;
    outBuffers.buffers = buffers;
    outBuffers.buffernumchannels = numChannels;

    FMOD_RESULT result = TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_OK);
    for(int i=0; i<1024; ++i) {
        assert(outData[i] == 0.0f);
    }
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_Perform() {
    std::cout << "Running test_TapeStop_Process_Perform..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {0.5f};
    dsp_state.plugindata = &state;

    float inData[1024];
    float outData[1024];
    for(int i=0; i<1024; ++i) {
        inData[i] = 1.0f;
        outData[i] = 0.0f;
    }
    float* inBuffersPtr[] = { inData };
    float* outBuffersPtr[] = { outData };
    int numChannels[] = { 1 };

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    inBuffers.numbuffers = 1;
    inBuffers.buffers = inBuffersPtr;
    inBuffers.buffernumchannels = numChannels;

    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 1;
    outBuffers.buffers = outBuffersPtr;
    outBuffers.buffernumchannels = numChannels;

    FMOD_RESULT result = TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_PERFORM);
    assert(result == FMOD_OK);
    for(int i=0; i<1024; ++i) {
        assert(outData[i] == 0.5f);
    }
    std::cout << "Passed!" << std::endl;
}

void test_TapeStop_Process_Query() {
    std::cout << "Running test_TapeStop_Process_Query..." << std::endl;
    FMOD_DSP_STATE dsp_state = {0};
    TapeStopState state = {0.5f};
    dsp_state.plugindata = &state;

    float inData[1024];
    float outData[1024];
    for(int i=0; i<1024; ++i) {
        inData[i] = 1.0f;
        outData[i] = 0.0f;
    }
    float* inBuffersPtr[] = { inData };
    float* outBuffersPtr[] = { outData };
    int numChannels[] = { 1 };

    FMOD_DSP_BUFFER_ARRAY inBuffers = {0};
    inBuffers.numbuffers = 1;
    inBuffers.buffers = inBuffersPtr;
    inBuffers.buffernumchannels = numChannels;

    FMOD_DSP_BUFFER_ARRAY outBuffers = {0};
    outBuffers.numbuffers = 1;
    outBuffers.buffers = outBuffersPtr;
    outBuffers.buffernumchannels = numChannels;

    // QUERY should copy without gain
    FMOD_RESULT result = TapeStop_Process(&dsp_state, 1024, &inBuffers, &outBuffers, FMOD_FALSE, FMOD_DSP_PROCESS_QUERY);
    assert(result == FMOD_OK);
    for(int i=0; i<1024; ++i) {
        assert(outData[i] == 1.0f);
    }
    std::cout << "Passed!" << std::endl;
}

int main() {
    test_TapeStop_Process_NullParams();
    test_TapeStop_Process_ZeroBuffers();
    test_TapeStop_Process_ZeroLength();
    test_TapeStop_Process_InputsIdle();
    test_TapeStop_Process_EmptyInBuffers();
    test_TapeStop_Process_Perform();
    test_TapeStop_Process_Query();
    std::cout << "All DSPCallbacks tests passed!" << std::endl;
    return 0;
}
