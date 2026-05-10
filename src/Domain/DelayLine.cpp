#include "DelayLine.h"
#include <cmath>
#include <algorithm>
#include <bit>

namespace tapestop::domain {

DelayLine::DelayLine(float max_seconds, float sample_rate, FMOD_DSP_STATE* dsp_state)
    : data_(framework::FmodAllocator<float>(dsp_state)) {
    std::size_t size = static_cast<std::size_t>(max_seconds * sample_rate);
    std::size_t power_of_two_size = std::bit_ceil(size);
    if (power_of_two_size == 0) {
        power_of_two_size = 1;
    }

    data_.resize(power_of_two_size, 0.0f);
    mask_ = power_of_two_size - 1;
}

void DelayLine::reset() {
    std::fill(data_.begin(), data_.end(), 0.0f);
}

void DelayLine::write(std::size_t index, float value) {
    data_[index & mask_] = value;
}

float DelayLine::read(double index) const {
    double idx_i_dbl;
    double frac_dbl = std::modf(index, &idx_i_dbl);

    // Handle potential negative remainder for proper positive fraction
    if (frac_dbl < 0.0) {
        frac_dbl += 1.0;
        idx_i_dbl -= 1.0;
    }

    std::size_t idx_i = static_cast<std::size_t>(static_cast<long long>(idx_i_dbl));
    float frac = static_cast<float>(frac_dbl);

    std::size_t p0 = (idx_i - 1) & mask_;
    std::size_t p1 = idx_i & mask_;
    std::size_t p2 = (idx_i + 1) & mask_;
    std::size_t p3 = (idx_i + 2) & mask_;

    float s0 = data_[p0];
    float s1 = data_[p1];
    float s2 = data_[p2];
    float s3 = data_[p3];

    // 4-point Hermite interpolation
    float c0 = s1;
    float c1 = 0.5f * (s2 - s0);
    float c2 = s0 - 2.5f * s1 + 2.0f * s2 - 0.5f * s3;
    float c3 = 0.5f * (s3 - s0) + 1.5f * (s1 - s2);

    return ((c3 * frac + c2) * frac + c1) * frac + c0;
}

} // namespace tapestop::domain
