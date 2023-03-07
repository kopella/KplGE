add_library(graphic graphic-manager.cc)
target_include_directories(graphic PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")

if(${KPLGE_GRAPHIC_API} MATCHES "empty")
#
elseif(${KPLGE_GRAPHIC_API} MATCHES "opengl")
    add_library(${KPLGE_GRAPHIC_API} opengl-manager.cc)
    target_include_directories(${KPLGE_GRAPHIC_API} PUBLIC
        "${KPL_IDGEN_INCLUDE_DIR}"
        "${KPL_CALCT_INCLUDE_DIR}"
        "${KPL_LOGT_INCLUDE_DIR}"
    )
    target_include_directories(${KPLGE_GRAPHIC_API} PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/json")
    target_include_directories(${KPLGE_GRAPHIC_API} PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
    target_include_directories(${KPLGE_GRAPHIC_API} PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")
    target_include_directories(${KPLGE_GRAPHIC_API} PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
    target_include_directories(${KPLGE_GRAPHIC_API} PRIVATE "${EXTERNAL_ALL_INCLUDE_DIR}/opengl")
elseif(${KPLGE_GRAPHIC_API} MATCHES "directx11")
#
elseif(${KPLGE_GRAPHIC_API} MATCHES "directx12")
#
else()
    message(FATAL_ERROR "Invalid graphic api.")
endif()

target_link_libraries(graphic PUBLIC ${KPLGE_GRAPHIC_API})