add_library(graphic INTERFACE)

target_link_libraries(graphic INTERFACE
    ${KPLEG_GFX_API}
)

add_subdirectory(${KPLEG_GFX_API})