#ifndef FMODTAPESTOPPLUGIN_TAPESTOPINTERNALDATA_H
#define FMODTAPESTOPPLUGIN_TAPESTOPINTERNALDATA_H

#include "../UseCase/TapeStopEngine.h"
#include "../UseCase/TapeStopParameters.h"

namespace tapestop::framework {

struct TapeStopState {
    usecase::TapeStopParameters params;
    usecase::TapeStopEngine* engine;

    TapeStopState() : engine(nullptr) {}
};

} // namespace tapestop::framework

#endif //FMODTAPESTOPPLUGIN_TAPESTOPINTERNALDATA_H
