#ifndef FMOD_COMMON_H
#define FMOD_COMMON_H

typedef enum {
    FMOD_OK = 0,
    FMOD_ERR_INVALID_PARAM = 1,
    FMOD_ERR_INTERNAL = 2,
    FMOD_ERR_MEMORY = 3
} FMOD_RESULT;

typedef int FMOD_BOOL;
#define FMOD_TRUE 1
#define FMOD_FALSE 0

#ifndef F_CALL
#define F_CALL
#endif

#endif
