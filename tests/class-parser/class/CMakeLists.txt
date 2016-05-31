add_executable(espresso-class-parser-class-testdriver driver.cpp)
target_compile_features(espresso-class-parser-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-class-parser-class-testdriver PUBLIC espresso-class-parser)
set_target_properties(espresso-class-parser-class-testdriver PROPERTIES FOLDER "tests/class-parser")

file(GLOB TEST_FILES "*.class")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    add_test(classparser-class-${TEST_WE} espresso-class-parser-class-testdriver ${TEST_FILE})
endforeach()

file(GLOB TEST_FILES "*.fail.class")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    set_tests_properties(classparser-class-${TEST_WE} PROPERTIES WILL_FAIL TRUE)
endforeach()

file(GLOB TEST_FILES "*.java")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class"
        MAIN_DEPENDENCY ${TEST_FILE}
        COMMAND "${Java_JAVAC_EXECUTABLE}" -g -d "${CMAKE_CURRENT_BINARY_DIR}" ${TEST_FILE})
    add_test(classparser-class-${TEST_WE} espresso-class-parser-class-testdriver "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class")
    add_custom_target(espresso-classparser-class-${TEST_WE} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class")
endforeach()

