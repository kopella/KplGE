cmake_minimum_required(VERSION 3.19.0)
project(kplGE
    VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gfx api : empty, opengl, directx11, directx12
set(KPLGE_GRAPHIC_API "opengl")

# platform : windows, linux
if(${UNIX})
    set(KPLGE_TARGET_PLATFORM "linux")
elseif(${WIN32})
    set(KPLGE_TARGET_PLATFORM "windows")
endif()

set(ENABLE_ISPC TRUE)

set(KPL_CALCT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/utility/calculation-tools/include")
set(KPL_IDGEN_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/utility/identifier-generator/include")
set(KPL_LOGT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/utility/logging-tools/include")

set(KPL_FRAMEWORK_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/framework/include")


set(EXTERNAL_ALL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/external/all/include")

add_subdirectory(utility)
add_subdirectory(framework)
add_subdirectory(test)
