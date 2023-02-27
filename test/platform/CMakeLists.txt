if(${KPLGE_TARGET_PLATFORM} MATCHES "windows")
    if(${KPLGE_GRAPHIC_API} MATCHES "opengl")
        add_executable(windows-opengl-test
            windows-opengl-test.cc)
        target_include_directories(windows-opengl-test PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/application")
        target_include_directories(windows-opengl-test PRIVATE "${KPL_LOGT_INCLUDE_DIR}")
        target_link_libraries(windows-opengl-test
            framework
            platform
        )
    elseif(${KPLGE_GRAPHIC_API} MATCHES "directx11")
        add_executable(windows-dx11-test
            windows-directx11-test.cc)
        target_link_libraries(windows-dx11-test
            framework
            platform
        )
    elseif(${KPLGE_GRAPHIC_API} MATCHES "directx12")
        add_executable(windows-dx12-test
            windows-directx12-test.cc)
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
    if(${KPLGE_GRAPHIC_API} MATCHES "opengl")
        add_executable(linux-opengl-test
            linux-opengl-test.cc)
        target_link_libraries(linux-opengl-test
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
