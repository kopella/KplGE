add_library(scene scene-object.cc mesh.cc)
target_include_directories(scene PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
target_include_directories(scene PUBLIC "${KPL_IDGEN_INCLUDE_DIR}")