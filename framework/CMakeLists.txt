add_subdirectory(common)
add_subdirectory(graphics)

add_library(framework INTERFACE)

target_link_libraries(framework INTERFACE
    common
    graphics
)