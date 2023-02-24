cmake_minimum_required(VERSION 3.0.0)
project(kpl-ge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gfx api : empty, ogl, dx11, dx12
set(KPLEG_GFX_API "ogl")

# platform : windows, linux
if(${UNIX})
    set(KPLGE_TARGET_PLATFORM "linux")
elseif(${WIN32})
    set(KPLGE_TARGET_PLATFORM "windows")
endif()

option(ENABLE_ISPC ON)

include_directories(
    "${PROJECT_SOURCE_DIR}/framework/utility/log"
    "${PROJECT_SOURCE_DIR}/framework/utility/math"
    "${PROJECT_SOURCE_DIR}/framework/interface"
    "${PROJECT_SOURCE_DIR}/framework/common"
    "${PROJECT_SOURCE_DIR}/framework/memory"
    "${PROJECT_SOURCE_DIR}/framework/graphic"
)
include_directories(
    "${PROJECT_SOURCE_DIR}/platform/${KPLGE_TARGET_PLATFORM}"
)
include_directories(
    "${PROJECT_SOURCE_DIR}/external/all"
    "${PROJECT_SOURCE_DIR}/external/${KPLGE_TARGET_PLATFORM}"
)

add_subdirectory(framework)
add_subdirectory(platform)
add_subdirectory(test)