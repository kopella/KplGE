set(ISPC_CODES basic vector matrix)

if(${KPLGE_TARGET_PLATFORM} MATCHES "windows")
    foreach(ISPC_CODE IN LISTS ISPC_CODES)
        add_custom_command(OUTPUT ${ISPC_CODE}.o
            COMMAND ${PROJECT_SOURCE_DIR}/external/windows/bin/ispc/ispc.exe --target=host --arch=x86-64 ${PROJECT_SOURCE_DIR}/framework/utility/math/ispc/${ISPC_CODE}.ispc -o ${ISPC_CODE}.o
            DEPENDS ${ISPC_CODE}.ispc
            COMMENT "Compile ${ISPC_CODE}.ispc")
        list(APPEND ISPC_OBJECTS ${ISPC_CODE}.o)
    endforeach()
elseif(${KPLGE_TARGET_PLATFORM} MATCHES "linux")
endif()

add_library(kpl-math STATIC ${ISPC_OBJECTS})

SET_TARGET_PROPERTIES(
    kpl-math
    PROPERTIES
    LINKER_LANGUAGE C
)