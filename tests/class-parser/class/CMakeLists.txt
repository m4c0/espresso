add_executable(espresso-class-parser-class-testdriver driver.cpp)
target_compile_features(espresso-class-parser-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-class-parser-class-testdriver PUBLIC espresso-class-parser)
set_target_properties(espresso-class-parser-class-testdriver PROPERTIES FOLDER "tests/class-parser")

file(GLOB TEST_FILES "*.class")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    add_test(classparser-class-${TEST_WE} espresso-class-parser-class-testdriver ${TEST_FILE})
endforeach()

