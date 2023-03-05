set(FRAMEWORK_TEST_CASES common-asset-loader-test scene-gltf-loader-test scene-manager-test)

foreach(TEST_CASE IN LISTS FRAMEWORK_TEST_CASES)
    add_executable(${TEST_CASE} ${TEST_CASE}.cc)
    
    target_link_libraries(${TEST_CASE} utility)
    target_link_libraries(${TEST_CASE} framework)

    target_include_directories(${TEST_CASE} PRIVATE
        "${KPL_IDGEN_INCLUDE_DIR}"
        "${KPL_CALCT_INCLUDE_DIR}"
        "${KPL_LOGT_INCLUDE_DIR}"
    )

    target_include_directories(${TEST_CASE} PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
    target_include_directories(${TEST_CASE} PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
endforeach(TEST_CASE)
