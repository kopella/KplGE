add_subdirectory(rhi)

add_library(windows-application
    windows-application.cc
)
target_include_directories(windows-application PUBLIC "../include")
target_include_directories(windows-application PUBLIC
    "${KPL_IDGEN_INCLUDE_DIR}"
    "${KPL_CALCT_INCLUDE_DIR}"
    "${KPL_LOGT_INCLUDE_DIR}"
)
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/application")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
target_include_directories(windows-application PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/json")