cmake_minimum_required(VERSION 3.28)
project(FMODTapeStopPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---FMOD SDKのパスを指定---
set(FMOD_SDK_PATH "${CMAKE_SOURCE_DIR}/ThirdParty" CACHE PATH "Path to the FMOD SDK root")
set(FMOD_INCLUDE_DIR "${FMOD_SDK_PATH}/inc" CACHE PATH "Path to the FMOD SDK include directory")
set(FMOD_LIBRARY_DIR "${FMOD_SDK_PATH}/lib" CACHE PATH "Path to the FMOD SDK library directory")

if (NOT EXISTS "${FMOD_INCLUDE_DIR}")
    message(FATAL_ERROR "FMOD SDK include directory not found at ${FMOD_INCLUDE_DIR}")
endif()

# ---ソースファイルの設定---
set(SOURCE_FILES
    src/Domain/DelayLine.h
    src/Domain/DelayLine.cpp
    src/Domain/OnePoleLowpass.h
    src/Domain/OnePoleLowpass.cpp
    src/UseCase/TapeStopParameters.h
    src/UseCase/TapeStopEngine.h
    src/UseCase/TapeStopEngine.cpp
    src/InterfaceAdapter/ParameterIndex.h
    src/InterfaceAdapter/ParameterDesc.h
    src/InterfaceAdapter/ParameterDesc.cpp
    src/InterfaceAdapter/ParameterSetCallbacks.h
    src/InterfaceAdapter/ParameterSetCallbacks.cpp
    src/InterfaceAdapter/ParameterGetCallbacks.h
    src/InterfaceAdapter/ParameterGetCallbacks.cpp
    src/Framework/TapeStopInternalData.h
    src/Framework/DSPCallbacks.h
    src/Framework/DSPCallbacks.cpp
    src/Framework/DSPDesc.h
    src/Framework/DSPDesc.cpp
)

# ---ライブラリを追加---
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# ---インクルードディレクトリを追加---
target_include_directories(${PROJECT_NAME} PRIVATE "${FMOD_INCLUDE_DIR}")

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

set(FMOD_CORE_LIBRARY_RELEASE "" CACHE FILEPATH "Path to the FMOD Core release library")
set(FMOD_CORE_LIBRARY_DEBUG "" CACHE FILEPATH "Path to the FMOD Core debug library")
set(FMOD_STUDIO_LIBRARY_RELEASE "" CACHE FILEPATH "Path to the FMOD Studio release library")
set(FMOD_STUDIO_LIBRARY_DEBUG "" CACHE FILEPATH "Path to the FMOD Studio debug library")

function(fmod_add_imported_library target_name release_library debug_library)
    add_library(${target_name} UNKNOWN IMPORTED)

    if (NOT release_library)
        message(FATAL_ERROR "${target_name} release library was not found.")
    endif()

    if (NOT debug_library)
        set(debug_library "${release_library}")
    endif()

    set_target_properties(${target_name} PROPERTIES
            IMPORTED_LOCATION "${release_library}"
            IMPORTED_LOCATION_RELEASE "${release_library}"
            IMPORTED_LOCATION_DEBUG "${debug_library}"
            MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
            MAP_IMPORTED_CONFIG_MINSIZEREL Release
    )
endfunction()

if (WIN32)
    if (NOT FMOD_CORE_LIBRARY_RELEASE)
        set(FMOD_CORE_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
    endif()
    if (NOT FMOD_CORE_LIBRARY_DEBUG)
        set(FMOD_CORE_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
    endif()
    if (NOT FMOD_STUDIO_LIBRARY_RELEASE)
        set(FMOD_STUDIO_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
    endif()
    if (NOT FMOD_STUDIO_LIBRARY_DEBUG)
        set(FMOD_STUDIO_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
    endif()
elseif(APPLE)
    set(FMOD_LIBRARY_HINTS
            "${FMOD_LIBRARY_DIR}"
            "${FMOD_SDK_PATH}/api/core/lib/macos"
            "${FMOD_SDK_PATH}/api/studio/lib/macos"
            "${FMOD_SDK_PATH}/api/core/lib"
            "${FMOD_SDK_PATH}/api/studio/lib"
    )

    if (NOT FMOD_CORE_LIBRARY_RELEASE)
        find_library(FMOD_CORE_LIBRARY_RELEASE NAMES fmod PATHS ${FMOD_LIBRARY_HINTS} NO_DEFAULT_PATH)
    endif()
    if (NOT FMOD_CORE_LIBRARY_DEBUG)
        find_library(FMOD_CORE_LIBRARY_DEBUG NAMES fmodL PATHS ${FMOD_LIBRARY_HINTS} NO_DEFAULT_PATH)
    endif()
    if (NOT FMOD_STUDIO_LIBRARY_RELEASE)
        find_library(FMOD_STUDIO_LIBRARY_RELEASE NAMES fmodstudio PATHS ${FMOD_LIBRARY_HINTS} NO_DEFAULT_PATH)
    endif()
    if (NOT FMOD_STUDIO_LIBRARY_DEBUG)
        find_library(FMOD_STUDIO_LIBRARY_DEBUG NAMES fmodstudioL PATHS ${FMOD_LIBRARY_HINTS} NO_DEFAULT_PATH)
    endif()
else()
    message(FATAL_ERROR "This project currently supports Windows and macOS only.")
endif()

fmod_add_imported_library(FMOD::Core "${FMOD_CORE_LIBRARY_RELEASE}" "${FMOD_CORE_LIBRARY_DEBUG}")
fmod_add_imported_library(FMOD::Studio "${FMOD_STUDIO_LIBRARY_RELEASE}" "${FMOD_STUDIO_LIBRARY_DEBUG}")

# ---ライブラリをリンク---
target_link_libraries(${PROJECT_NAME} PRIVATE FMOD::Core FMOD::Studio)
