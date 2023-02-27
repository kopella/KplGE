if(${KPLGE_TARGET_PLATFORM} MATCHES "windows")
    add_subdirectory(windows)
elseif(${KPLGE_TARGET_PLATFORM} MATCHES "linux")
    add_subdirectory(linux)
else()
    message(FATAL_ERROR "Invalid platform.")
endif()

add_library(platform INTERFACE)

target_link_libraries(platform INTERFACE
    ${KPLGE_TARGET_PLATFORM}-application
)