#include "TapeStopEngine.h"
#include <cmath>
#include <algorithm>

namespace tapestop::usecase {

TapeStopEngine::TapeStopEngine(float sample_rate, float max_seconds, FMOD_DSP_STATE* dsp_state)
    : sample_rate_(sample_rate),
      max_seconds_(max_seconds),
      dsp_state_(dsp_state),
      buffers_(framework::FmodAllocator<domain::DelayLine>(dsp_state)),
      filters_(framework::FmodAllocator<domain::OnePoleLowpass>(dsp_state)),
      write_pos_(0),
      read_pos_(0.0),
      phase_(1.0),
      current_speed_(1.0),
      crossfade_gain_(1.0) {
}

void TapeStopEngine::reset() {
    for (auto& buffer : buffers_) {
        buffer.reset();
    }
    for (auto& filter : filters_) {
        filter.reset();
    }
    write_pos_ = 0;
    read_pos_ = 0.0;
    phase_ = 1.0;
    current_speed_ = 1.0;
    crossfade_gain_ = 1.0;
}

void TapeStopEngine::process(
    const float* input,
    float* output,
    std::size_t num_channels,
    const TapeStopParameters& params,
    double bpm
) {
    // Dynamically resize buffers and filters if channel count changes
    if (buffers_.size() < num_channels) {
        while (buffers_.size() < num_channels) {
            buffers_.emplace_back(max_seconds_, sample_rate_, dsp_state_);
            filters_.emplace_back();
        }
    }

    double actual_stop_time = params.stop_time;
    if (params.use_sync) {
        double current_bpm = (bpm > 0.0) ? bpm : 120.0;
        double beats = 1.0; // default to Quarter
        switch (params.sync_beat) {
            case SyncBeat::Eight:   beats = 0.5; break;
            case SyncBeat::Quarter: beats = 1.0; break;
            case SyncBeat::Half:    beats = 2.0; break;
            case SyncBeat::OneBar:  beats = 4.0; break;
            case SyncBeat::TwoBars: beats = 8.0; break;
        }
        actual_stop_time = (60.0 / current_bpm) * beats;
    }

    double stop_step = 1.0 / (actual_stop_time * sample_rate_);
    double start_step = 1.0 / (params.start_time * sample_rate_);
    float xfade_step = 1.0f / (0.1f * sample_rate_);

    if (params.trigger) {
        phase_ -= stop_step;
        if (phase_ < 0.0) phase_ = 0.0;
        crossfade_gain_ = 0.0f;
    } else {
        if (phase_ < 1.0) {
            phase_ += start_step;
            if (phase_ > 1.0) phase_ = 1.0;
            crossfade_gain_ = 0.0f;
        } else {
            if (crossfade_gain_ < 1.0f) {
                crossfade_gain_ += xfade_step;
                if (crossfade_gain_ >= 1.0f) {
                    crossfade_gain_ = 1.0f;
                    read_pos_ = static_cast<double>(write_pos_);
                }
            }
        }
    }

    double t = phase_;
    switch (params.curve) {
        case TapeCurve::Linear:
            current_speed_ = t;
            break;
        case TapeCurve::Smooth:
            current_speed_ = t * t * (3.0 - 2.0 * t);
            break;
        case TapeCurve::SlowStart:
            current_speed_ = 1.0 - std::pow(1.0 - t, 2.0);
            break;
        case TapeCurve::QuickCut:
            current_speed_ = std::pow(t, 3.0);
            break;
    }

    if (params.enable_filter) {
        float min_cut = 200.0f;
        float max_cut = 20000.0f;
        float cutoff = min_cut * std::pow(max_cut / min_cut, static_cast<float>(current_speed_));

        for (std::size_t i = 0; i < num_channels; ++i) {
            filters_[i].setCutoff(cutoff, sample_rate_);
        }
    }

    for (std::size_t ch = 0; ch < num_channels; ++ch) {
        float in_sample = input[ch];
        buffers_[ch].write(write_pos_, in_sample);

        float tape_sound = 0.0f;

        if (current_speed_ > 0.0) {
            tape_sound = buffers_[ch].read(read_pos_);

            if (params.enable_filter) {
                tape_sound = filters_[ch].process(tape_sound);
            }
        }

        output[ch] = tape_sound * (1.0f - crossfade_gain_) + in_sample * crossfade_gain_;
    }

    write_pos_++;
    if (current_speed_ > 0.0) {
        read_pos_ += current_speed_;
    }
}

} // namespace tapestop::usecase
