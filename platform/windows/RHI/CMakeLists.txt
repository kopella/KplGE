if(${KPLEG_GFX_API} MATCHES "ogl")
    # platform: Windows
    # gfx api: OpenGL
    add_subdirectory(wgl)
endif()

add_library(RHI INTERFACE)

target_link_libraries(RHI INTERFACE
    "rhi_${KPLEG_GFX_API}"
)