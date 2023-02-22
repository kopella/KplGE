add_subdirectory(common)
add_subdirectory(graphic)
add_subdirectory(scene)

add_library(framework INTERFACE)

target_link_libraries(framework INTERFACE
    common
    graphic
)