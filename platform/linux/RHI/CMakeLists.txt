add_subdirectory(${KPLEG_GFX_API})

add_library(RHI INTERFACE)

target_link_libraries(RHI INTERFACE
    "rhi_${KPLEG_GFX_API}"
)