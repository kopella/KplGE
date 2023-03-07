add_library(application base-application.cc)

target_include_directories(application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/common")
target_include_directories(application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/scene")
target_include_directories(application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/graphic")
target_include_directories(application PUBLIC "${KPL_FRAMEWORK_INCLUDE_DIR}/application")
target_include_directories(application PUBLIC
    "${KPL_IDGEN_INCLUDE_DIR}"
    "${KPL_CALCT_INCLUDE_DIR}"
    "${KPL_LOGT_INCLUDE_DIR}"
)
target_include_directories(application PUBLIC "${EXTERNAL_ALL_INCLUDE_DIR}/json")
