#ifndef FMODTAPESTOPPLUGIN_EXPORT_H
#define FMODTAPESTOPPLUGIN_EXPORT_H

/* ---エクスポート関数マクロ--- */
#if defined(_WIN32)
#define FMOD_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
#define FMOD_EXPORT __attribute__((visibility("default")))
#else
#define FMOD_EXPORT
#endif

#endif //FMODTAPESTOPPLUGIN_EXPORT_H

