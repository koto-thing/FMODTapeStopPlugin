#ifndef FMODTAPESTOPPLUGIN_TAPESTOPENGINE_H
#define FMODTAPESTOPPLUGIN_TAPESTOPENGINE_H

#include "../Domain/DelayLine.h"
#include "../Domain/OnePoleLowpass.h"
#include "TapeStopParameters.h"
#include "../Framework/FmodAllocator.h"
#include <vector>

namespace tapestop::usecase {

class TapeStopEngine {
public:
    TapeStopEngine(float sample_rate, float max_seconds, FMOD_DSP_STATE* dsp_state);

    void reset();

    void process(
        const float* input,
        float* output,
        std::size_t num_channels,
        const TapeStopParameters& params,
        double bpm
    );

private:
    float sample_rate_;
    float max_seconds_;
    FMOD_DSP_STATE* dsp_state_;

    std::vector<domain::DelayLine, framework::FmodAllocator<domain::DelayLine>> buffers_;
    std::vector<domain::OnePoleLowpass, framework::FmodAllocator<domain::OnePoleLowpass>> filters_;

    std::size_t write_pos_;
    double read_pos_;

    double phase_;
    double current_speed_;
    float crossfade_gain_;
};

} // namespace tapestop::usecase

#endif //FMODTAPESTOPPLUGIN_TAPESTOPENGINE_H
