add_library(scene-loader
    gltf-loader.cc
    gltf-tools.cc
)

target_include_directories(scene-loader PRIVATE
    "${KPL_IDGEN_INCLUDE_DIR}"
    "${KPL_CALCT_INCLUDE_DIR}"
    "${KPL_LOGT_INCLUDE_DIR}"
)

target_include_directories(scene-loader PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
target_include_directories(scene-loader PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene/scene-loader")
target_include_directories(scene-loader PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/json")
