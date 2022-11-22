add_subdirectory(${KPLGE_TARGET_PLATFORM})

add_library(platform INTERFACE)

target_link_libraries(platform INTERFACE
    ${KPLGE_TARGET_PLATFORM}
)