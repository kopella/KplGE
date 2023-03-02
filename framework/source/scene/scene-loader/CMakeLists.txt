add_library(scene-loader gltf-loader.cc)
target_include_directories(scene-loader PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/scene/scene-loader")
target_include_directories(scene-loader PUBLIC "${KPL_CALCT_INCLUDE_DIR}")