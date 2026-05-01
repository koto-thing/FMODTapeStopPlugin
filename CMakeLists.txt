cmake_minimum_required(VERSION 4.2)
project(FMODTapeStopPlugin)

set(CMAKE_CXX_STANDARD 20)

# ---FMOD SDKのパスを指定---
set(FMOD_SDK_PATH "${CMAKE_SOURCE_DIR}/ThirdParty")

# ---インクルードディレクトリを設定---
if (EXISTS "${FMOD_SDK_PATH}/inc")
    set(FMOD_INCLUDE_DIR "${FMOD_SDK_PATH}/inc")
else()
    message(FATAL_ERROR "FMOD SDK include directory not found at ${FMOD_SDK_PATH}/inc")
endif()

# ---ライブラリディレクトリを設定---
if (EXISTS "${FMOD_SDK_PATH}/lib")
    set(FMOD_LIBRARY_DIR "${FMOD_SDK_PATH}/lib")
else ()
    message(FATAL_ERROR "FMOD SDK library directory not found at ${FMOD_SDK_PATH}/lib")
endif()

# ---FMODのライブラリを確認---
if (WIN64)
    if (EXISTS "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
        set(FMOD_CORE_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
    else()
        message(FATAL_ERROR "FMOD library not found at ${FMOD_LIBRARY_DIR}/fmod_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
        set(FMOD_CORE_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
    else()
        message(FATAL_ERROR "FMOD library not found at ${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
        set(FMOD_STUDIO_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
    else()
        message(FATAL_ERROR "FMOD Studio library not found at ${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
        set(FMOD_STUDIO_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
    else()
        message(FATAL_ERROR "FMOD Studio library not found at ${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
    endif()
endif()

# ---ソースファイルの設定---
set(SOURCE_FILES
        src/TapeStop.cpp
        src/TapeStopInternalData.h
        src/ParameterIndex.h
        src/ParameterDesc.h
        src/ParameterDesc.cpp
        src/DSPDesc.h
        src/DSPCallbacks.cpp
        src/DSPCallbacks.h
        src/ParameterSetCallbacks.cpp
        src/ParameterSetCallbacks.h
        src/ParameterGetCallbacks.cpp
        src/ParameterGetCallbacks.h
        src/Export.h
        src/DSPDesc.cpp
)

# ---ライブラリを追加---
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# ---インクルードディレクトリを追加---
target_include_directories(${PROJECT_NAME} PRIVATE "${FMOD_INCLUDE_DIR}")

if (WIN64)
    add_library(FMOD::Core UNKNOWN IMPORTED)
    set_target_properties(FMOD::Core PROPERTIES
            IMPORTED_LOCATION_RELEASE "${FMOD_CORE_LIBRARY_RELEASE}"
            IMPORTED_LOCATION_DEBUG "${FMOD_CORE_LIBRARY_DEBUG}"
            MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
            MAP_IMPORTED_CONFIG_MINSIZEREL Release
    )

    add_library(FMOD::Studio UNKNOWN IMPORTED)
    set_target_properties(FMOD::Studio PROPERTIES
            IMPORTED_LOCATION_RELEASE "${FMOD_STUDIO_LIBRARY_RELEASE}"
            IMPORTED_LOCATION_DEBUG "${FMOD_STUDIO_LIBRARY_DEBUG}"
            MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
            MAP_IMPORTED_CONFIG_MINSIZEREL Release
    )

    # ---ライブラリをリンク---
    target_link_libraries(${PROJECT_NAME} PRIVATE FMOD::Core FMOD::Studio)
endif()
