add_subdirectory(calculation-tools)
add_subdirectory(identifier-generator)

add_library(utility INTERFACE)

target_link_libraries(utility INTERFACE
    kplcalct
    kplidgen
)