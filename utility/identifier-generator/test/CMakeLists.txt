add_executable(kplidgen-test main.cc)
target_include_directories(kplidgen-test PRIVATE "../include")
target_link_libraries(kplidgen-test kplidgen)