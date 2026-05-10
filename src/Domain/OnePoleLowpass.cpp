#include "OnePoleLowpass.h"
#include <cmath>
#include <algorithm>

namespace tapestop::domain {

OnePoleLowpass::OnePoleLowpass() : prev_output_(0.0f), alpha_(1.0f) {}

void OnePoleLowpass::setCutoff(float cutoff_hz, float sample_rate) {
    constexpr float PI = 3.14159265358979323846f;
    float y = 1.0f - std::exp(-2.0f * PI * cutoff_hz / sample_rate);
    alpha_ = std::clamp(y, 0.0f, 1.0f);
}

float OnePoleLowpass::process(float input) {
    float output = prev_output_ + alpha_ * (input - prev_output_);
    prev_output_ = output;
    return output;
}

void OnePoleLowpass::reset() {
    prev_output_ = 0.0f;
    alpha_ = 1.0f;
}

} // namespace tapestop::domain
