add_subdirectory(common)
add_subdirectory(graphic)

add_library(framework INTERFACE)

target_link_libraries(framework INTERFACE
    common
    graphic
)