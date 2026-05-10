#ifndef FMODTAPESTOPPLUGIN_TAPESTOPPARAMETERS_H
#define FMODTAPESTOPPLUGIN_TAPESTOPPARAMETERS_H

namespace tapestop::usecase {

enum class TapeCurve : int {
    Linear = 0,
    Smooth = 1,
    SlowStart = 2,
    QuickCut = 3
};

enum class SyncBeat : int {
    Eight = 0,      // 1/8
    Quarter = 1,    // 1/4
    Half = 2,       // 1/2
    OneBar = 3,     // 1 Bar
    TwoBars = 4     // 2 Bars
};

struct TapeStopParameters {
    bool trigger = false;
    bool use_sync = false;
    float stop_time = 0.5f;
    SyncBeat sync_beat = SyncBeat::Quarter;
    float start_time = 0.5f;
    TapeCurve curve = TapeCurve::Linear;
    bool enable_filter = true;
};

} // namespace tapestop::usecase

#endif //FMODTAPESTOPPLUGIN_TAPESTOPPARAMETERS_H
