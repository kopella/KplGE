add_library(common
    asset-loader.cc
)

target_include_directories(common PRIVATE "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
target_include_directories(common PRIVATE "${KPL_LOGT_INCLUDE_DIR}")
