add_subdirectory(scene-loader)

add_library(scene scene-object.cc scene-mesh.cc)

target_link_libraries(scene PUBLIC scene-loader)
target_include_directories(scene PRIVATE "${KPL_IDGEN_INCLUDE_DIR}")
target_include_directories(scene PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
