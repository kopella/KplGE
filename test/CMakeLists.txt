set(FRAMEWORK_TEST_CASES asset-loader-test)

foreach(TEST_CASE IN LISTS FRAMEWORK_TEST_CASES)
    add_executable(${TEST_CASE} ${TEST_CASE}.cc)
    target_link_libraries(${TEST_CASE} framework)
    add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
endforeach(TEST_CASE)