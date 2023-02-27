add_library(kplcalct INTERFACE)

if(${ENABLE_ISPC})
    message(STATUS "ISPC is enabled")
    add_subdirectory(ispc)
    target_link_libraries(kplcalct INTERFACE ispcimp)
endif()