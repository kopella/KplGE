add_executable(kplcalct-test main.cc)
target_include_directories(kplcalct-test PRIVATE "../include")
target_link_libraries(kplcalct-test kplcalct)