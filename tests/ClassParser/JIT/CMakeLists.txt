# TODO: eventually, merge this and the java, since both seems almost equals
add_executable(espresso-classparser-jit-binary-testdriver binary-driver.cpp)
target_compile_features(espresso-classparser-jit-binary-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-classparser-jit-binary-testdriver PUBLIC espresso-classparser)
set_target_properties(espresso-classparser-jit-binary-testdriver PROPERTIES FOLDER "tests/ClassParser/JIT")

file(GLOB TEST_FILES "*.hex")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    set(BINARY ${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.bin)
    add_custom_command(
        OUTPUT ${BINARY}
        COMMAND xxd -r -p ${TEST_FILE} ${BINARY}
        DEPENDS ${TEST_FILE})
    add_test(classparser-jit-binary-${TEST_WE} espresso-classparser-jit-binary-testdriver ${BINARY})
    add_custom_target(espresso-classparser-jit-binary-${TEST_WE} ALL DEPENDS ${BINARY})
endforeach()

add_executable(espresso-classparser-jit-class-testdriver class-driver.cpp)
target_compile_features(espresso-classparser-jit-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-classparser-jit-class-testdriver PUBLIC espresso-classparser)
set_target_properties(espresso-classparser-jit-class-testdriver PROPERTIES FOLDER "tests/ClassParser/JIT")

file(GLOB TEST_FILES "*.java")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    espresso_java_test(classparser-jit-class ${TEST_WE} -g:none)
endforeach()

