cmake_minimum_required(VERSION 3.0.0)
project(kpl-ge VERSION 0.1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# gfx api : empty, ogl, dx11, dx12
set(KPLEG_GFX_API "empty")

# platform : empty, windows, linux
set(KPLGE_TARGET_PLATFORM "empty")

# framework
include_directories(
    ${CMAKE_SOURCE_DIR}/framework/interface
    ${CMAKE_SOURCE_DIR}/framework/common
    ${CMAKE_SOURCE_DIR}/framework/memory
    ${CMAKE_SOURCE_DIR}/framework/graphics
)

# utility
include_directories(
    ${CMAKE_SOURCE_DIR}/framework/utility/log
    ${CMAKE_SOURCE_DIR}/framework/utility/math
)

# platform
include_directories(
    ${CMAKE_SOURCE_DIR}/platform/windows
    ${CMAKE_SOURCE_DIR}/platform/windows/graphics
)

# external
set(KPLGE_EXTERNAL_ROOT "${PROJECT_SOURCE_DIR}/external/${KPLGE_TARGET_PLATFORM}")
message(STATUS "KPLGE_EXTERNAL_ROOT:${KPLGE_EXTERNAL_ROOT}")

# external - spdlog
include_directories(
    ${KPLGE_EXTERNAL_ROOT}/../all/spdlog/include
)
link_directories(
    ${KPLGE_EXTERNAL_ROOT}/../all/spdlog/lib
)

# external - OpenGL
find_package(OpenGL REQUIRED)

add_subdirectory(program)
