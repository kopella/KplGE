add_library(graphics INTERFACE)

target_link_libraries(graphics INTERFACE
    ${KPLEG_GFX_API}
)

add_subdirectory(${KPLEG_GFX_API})