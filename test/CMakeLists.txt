set(FRAMEWORK_TEST_CASES asset-loader-test)

foreach(TEST_CASE IN LISTS FRAMEWORK_TEST_CASES)
    add_executable(${TEST_CASE} ${TEST_CASE}.cc)
    target_link_libraries(${TEST_CASE} framework)
    add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
endforeach(TEST_CASE)

if(${KPLGE_TARGET_PLATFORM} MATCHES "windows")
    if(${KPLEG_GFX_API} MATCHES "ogl")
        add_executable(windows-ogl-test
            windows-ogl-test.cc)
        target_link_libraries(windows-ogl-test
            framework
            platform
        )
    elseif(${KPLEG_GFX_API} MATCHES "dx11")
        add_executable(windows-dx11-test
            windows-ogl-test.cc)
        target_link_libraries(windows-dx11-test
            framework
            platform
        )
    elseif(${KPLEG_GFX_API} MATCHES "dx12")
        add_executable(windows-dx12-test
            windows-ogl-test.cc)
        target_link_libraries(windows-dx12-test
            framework
            platform
        )
    else()
        add_executable(windows-empty-test
            windows-empty-test.cc)
        target_link_libraries(windows-empty-test
            framework
            platform
        )
    endif()
elseif(${KPLGE_TARGET_PLATFORM} MATCHES "linux")
    if(${KPLEG_GFX_API} MATCHES "ogl")
        add_executable(linux-ogl-test
            linux-ogl-test.cc)
        target_link_libraries(linux-ogl-test
            framework
            platform
        )
    else()
        add_executable(linux-empty-test
            windows-empty-test.cc)
        target_link_libraries(linux-empty-test
            framework
            platform
        )
    endif()
endif()
