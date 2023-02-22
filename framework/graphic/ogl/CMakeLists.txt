add_library(ogl
    ogl-manager.cc
)

target_link_libraries(ogl
    ${OPENGL_LIBRARIES}
)