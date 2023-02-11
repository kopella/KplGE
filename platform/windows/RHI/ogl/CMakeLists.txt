add_library("rhi_${KPLEG_GFX_API}"
    wgl-manager.cc wgl-func-load.cc
)

# external - OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(rhi_${KPLEG_GFX_API}
    ${OPENGL_LIBRARIES}
)