set(ISPC_CODES basic vector)

foreach(ISPC_CODE IN LISTS ISPC_CODES)
    add_custom_command(OUTPUT ${ISPC_CODE}.o
        COMMAND ispc --target-os=windows --arch=x86-64 ${CMAKE_SOURCE_DIR}/framework/utility/math/ispc/${ISPC_CODE}.ispc -o ${ISPC_CODE}.o
        DEPENDS ${ISPC_CODE}.ispc
        COMMENT "Compile ${ISPC_CODE}.ispc")
    list(APPEND ISPC_OBJECTS ${ISPC_CODE}.o)
endforeach()

add_library(kpl-math STATIC ${ISPC_OBJECTS})

SET_TARGET_PROPERTIES(
    kpl-math
    PROPERTIES
    LINKER_LANGUAGE C
)