add_library(rhi INTERFACE)

if(${KPLGE_GRAPHIC_API} MATCHES "empty")
#
elseif(${KPLGE_GRAPHIC_API} MATCHES "opengl")
    add_library(rhi_${KPLGE_GRAPHIC_API} wgl-manager.cc wgl-func-load.cc)
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "../../include")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "../../include/rhi")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/application")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/opengl")
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC
        "${KPL_IDGEN_INCLUDE_DIR}"
        "${KPL_CALCT_INCLUDE_DIR}"
        "${KPL_LOGT_INCLUDE_DIR}"
    )
    target_include_directories(rhi_${KPLGE_GRAPHIC_API} PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/json")

    # external - OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(rhi_${KPLGE_GRAPHIC_API}
        ${OPENGL_LIBRARIES}
    )
elseif(${KPLGE_GRAPHIC_API} MATCHES "directx11")
#
elseif(${KPLGE_GRAPHIC_API} MATCHES "directx12")
#
else()
    message(FATAL_ERROR "Invalid graphic api.")
endif()

target_link_libraries(graphic PUBLIC rhi_${KPLGE_GRAPHIC_API})