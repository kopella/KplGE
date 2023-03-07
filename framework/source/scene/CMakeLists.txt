add_library(scene scene-manager.cc scene-type.cc scene-object.cc scene-node.cc)

target_include_directories(scene PUBLIC
    "${KPL_IDGEN_INCLUDE_DIR}"
    "${KPL_CALCT_INCLUDE_DIR}"
    "${KPL_LOGT_INCLUDE_DIR}"
)

target_include_directories(scene PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
target_include_directories(scene PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/common")

add_subdirectory(scene-loader)
target_link_libraries(scene PUBLIC scene-loader)
