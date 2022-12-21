add_library(${KPLGE_TARGET_PLATFORM}
    win-ogl-application.cc
)

add_subdirectory(RHI)

target_link_libraries(${KPLGE_TARGET_PLATFORM}
    RHI
)