cmake_minimum_required(VERSION 3.0.0)
project(kpl-ge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gfx api : empty, ogl, dx11, dx12
set(KPLEG_GFX_API "ogl")

# platform : empty, windows, linux
if(WIN32)
    set(KPLGE_TARGET_PLATFORM "windows")
endif(WIN32)

if(UNIX)
    set(KPLGE_TARGET_PLATFORM "linux")
endif(UNIX)


# framework
include_directories(
    ${CMAKE_SOURCE_DIR}/framework/interface
    ${CMAKE_SOURCE_DIR}/framework/common
    ${CMAKE_SOURCE_DIR}/framework/memory
    ${CMAKE_SOURCE_DIR}/framework/graphic
    # utility
    ${CMAKE_SOURCE_DIR}/framework/utility/log
    ${CMAKE_SOURCE_DIR}/framework/utility/math
)

# platform
include_directories(
    ${CMAKE_SOURCE_DIR}/platform/windows
)



# external
include_directories(
    ${CMAKE_SOURCE_DIR}/external/all
)

set(KPLGE_EXTERNAL_ROOT "${PROJECT_SOURCE_DIR}/external/${KPLGE_TARGET_PLATFORM}")
message(STATUS "KPLGE_EXTERNAL_ROOT: ${KPLGE_EXTERNAL_ROOT}")
include_directories(
    ${KPLGE_EXTERNAL_ROOT}
)

# subdirectory
add_subdirectory(framework)
add_subdirectory(platform)
add_subdirectory(program)
add_subdirectory(test)

