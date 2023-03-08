add_library(kplcalct tools.cc)

target_include_directories(kplcalct PRIVATE ../include/private)

if(${ENABLE_ISPC})
    message(STATUS "ISPC is enabled")
    add_subdirectory(ispc)
    target_link_libraries(kplcalct PRIVATE ispcimp)
endif()