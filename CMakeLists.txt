cmake_minimum_required(VERSION 3.5) # I tested on 3.5 - feel free to test on lower ones and do a pull-request :)
project(espresso VERSION 0.0.1 LANGUAGES CXX)

enable_testing()

function(espresso_hex2bin TARGET INPUT OUTPUT)
    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND ${CMAKE_SOURCE_DIR}/hex2bin.pl < ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT} > ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT}
        MAIN_DEPENDENCY ${INPUT}
        DEPENDENCIES ${CMAKE_SOURCE_DIR}/hex2bin.pl
        )
    add_custom_target(${TARGET} DEPENDS ${INPUT})
endfunction()

add_subdirectory(class-parser)
add_subdirectory(tests)

