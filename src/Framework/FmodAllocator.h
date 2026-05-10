#ifndef FMODTAPESTOPPLUGIN_FMODALLOCATOR_H
#define FMODTAPESTOPPLUGIN_FMODALLOCATOR_H

#include "fmod_dsp.h"
#include <cstddef>
#include <new>

namespace tapestop::framework {

template <class T>
struct FmodAllocator {
    typedef T value_type;
    FMOD_DSP_STATE* dsp_state;

    FmodAllocator(FMOD_DSP_STATE* state) noexcept : dsp_state(state) {}

    template <class U> constexpr FmodAllocator(const FmodAllocator<U>& other) noexcept : dsp_state(other.dsp_state) {}

    [[nodiscard]] T* allocate(std::size_t n) {
        if (n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
        if (dsp_state && dsp_state->functions && dsp_state->functions->alloc) {
            if (auto p = static_cast<T*>(dsp_state->functions->alloc(n * sizeof(T), FMOD_MEMORY_NORMAL, __FILE__))) {
                return p;
            }
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept {
        if (p && dsp_state && dsp_state->functions && dsp_state->functions->free) {
            dsp_state->functions->free(p, FMOD_MEMORY_NORMAL, __FILE__);
        }
    }
};

template <class T, class U>
bool operator==(const FmodAllocator<T>& a, const FmodAllocator<U>& b) { return a.dsp_state == b.dsp_state; }

template <class T, class U>
bool operator!=(const FmodAllocator<T>& a, const FmodAllocator<U>& b) { return !(a == b); }

} // namespace tapestop::framework

#endif //FMODTAPESTOPPLUGIN_FMODALLOCATOR_H
