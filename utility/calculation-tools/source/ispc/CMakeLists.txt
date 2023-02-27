set(ISPC_CODES basic vector matrix)

foreach(ISPC_CODE IN LISTS ISPC_CODES)
    add_custom_command(OUTPUT ${ISPC_CODE}.o
        COMMAND ispc --target=host --arch=x86-64 ${PROJECT_SOURCE_DIR}/utility/calculation-tools/source/ispc/${ISPC_CODE}.ispc -o ${ISPC_CODE}.o
        DEPENDS ${ISPC_CODE}.ispc
        COMMENT "Buliding ${ISPC_CODE}.ispc")
    list(APPEND ISPC_OBJECTS ${ISPC_CODE}.o)
endforeach()

add_library(ispcimp ${ISPC_OBJECTS})

target_include_directories(ispcimp PRIVATE ../../include/private)

SET_TARGET_PROPERTIES(
    ispcimp
    PROPERTIES
    LINKER_LANGUAGE C
)