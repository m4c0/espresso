add_executable(espresso-classparser-class-testdriver driver.cpp)
target_compile_features(espresso-classparser-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-classparser-class-testdriver PUBLIC espresso-class-parser)
set_target_properties(espresso-classparser-class-testdriver PROPERTIES FOLDER "tests/class-parser")

file(GLOB TEST_FILES "*.class")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    add_test(classparser-class-${TEST_WE} espresso-classparser-class-testdriver ${TEST_FILE})
endforeach()

file(GLOB TEST_FILES "*.fail.class")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    set_tests_properties(classparser-class-${TEST_WE} PROPERTIES WILL_FAIL TRUE)
endforeach()

file(GLOB TEST_FILES "*.java")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    espresso_java_test(classparser-class ${TEST_WE} -g)
endforeach()

