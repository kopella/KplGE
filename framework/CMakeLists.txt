add_subdirectory(source)

add_library(framework INTERFACE)

target_link_libraries(framework INTERFACE
    common
    graphic
    scene
    application
)