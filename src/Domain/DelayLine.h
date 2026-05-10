#ifndef FMODTAPESTOPPLUGIN_DELAYLINE_H
#define FMODTAPESTOPPLUGIN_DELAYLINE_H

#include "../Framework/FmodAllocator.h"
#include <vector>
#include <cstddef>

namespace tapestop::domain {

class DelayLine {
public:
    DelayLine(float max_seconds, float sample_rate, FMOD_DSP_STATE* dsp_state);

    void reset();
    void write(std::size_t index, float value);
    float read(double index) const;

private:
    std::vector<float, framework::FmodAllocator<float>> data_;
    std::size_t mask_;
};

} // namespace tapestop::domain

#endif //FMODTAPESTOPPLUGIN_DELAYLINE_H
