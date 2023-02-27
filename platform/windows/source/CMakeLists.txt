add_subdirectory(rhi)

add_library(windows-application
    windows-application.cc
)
target_include_directories(windows-application PUBLIC "../include")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/application")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")
target_include_directories(windows-application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")