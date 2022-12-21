if(${KPLGE_TARGET_PLATFORM} MATCHES "windows")
    if(${KPLEG_GFX_API} MATCHES "ogl")
        # platform: Windows
        # gfx api: OpenGL
        add_executable(program
            win-ogl-program.cc)
        target_link_libraries(program
            framework
            platform
        )
    elseif(${KPLEG_GFX_API} MATCHES "dx11")
        # platform: Windows
        # gfx api: DirectX 11
    elseif(${KPLEG_GFX_API} MATCHES "dx12")
        # platform: Windows
        # gfx api: DirectX 12
    else()
        # platform: Windows
        # gfx api: Empty
        add_executable(program
            win-program.cc)
    endif()
elseif(${KPLGE_TARGET_PLATFORM} MATCHES "linux")
    if(${KPLEG_GFX_API} MATCHES "ogl")
        # platform: Linux
        # gfx api: OpenGL
    endif()
else()
    # platform: Empty
    # gfx api: Empty
    add_executable(empty
        empty.cc)
endif()
