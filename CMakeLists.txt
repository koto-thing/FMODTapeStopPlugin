cmake_minimum_required(VERSION 3.28)
project(FMODTapeStopPlugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---FMOD SDKのパスを指定---
set(FMOD_SDK_PATH "${CMAKE_SOURCE_DIR}/ThirdParty")

# ---インクルードディレクトリを設定---
if (EXISTS "${FMOD_SDK_PATH}/inc")
    set(FMOD_INCLUDE_DIR "${FMOD_SDK_PATH}/inc")
else()
    # It's common that ThirdParty is not in the repo, but let's just make it a soft warning or assume it will be there at build time
    message(WARNING "FMOD SDK include directory not found at ${FMOD_SDK_PATH}/inc")
    set(FMOD_INCLUDE_DIR "${FMOD_SDK_PATH}/inc")
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

# Windows specific library linking
if (WIN64)
    # ---ライブラリディレクトリを設定---
    if (EXISTS "${FMOD_SDK_PATH}/lib")
        set(FMOD_LIBRARY_DIR "${FMOD_SDK_PATH}/lib")
    else ()
        message(WARNING "FMOD SDK library directory not found at ${FMOD_SDK_PATH}/lib")
        set(FMOD_LIBRARY_DIR "${FMOD_SDK_PATH}/lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
        set(FMOD_CORE_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
    else()
        set(FMOD_CORE_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmod_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
        set(FMOD_CORE_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
    else()
        set(FMOD_CORE_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodL_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
        set(FMOD_STUDIO_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
    else()
        set(FMOD_STUDIO_LIBRARY_RELEASE "${FMOD_LIBRARY_DIR}/fmodstudio_vc.lib")
    endif()

    if (EXISTS "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
        set(FMOD_STUDIO_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
    else()
        set(FMOD_STUDIO_LIBRARY_DEBUG "${FMOD_LIBRARY_DIR}/fmodstudioL_vc.lib")
    endif()

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
