add_executable(espresso-classparser-jit-testdriver driver.cpp)
target_compile_features(espresso-classparser-jit-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-classparser-jit-testdriver PUBLIC espresso-classparser)
set_target_properties(espresso-classparser-jit-testdriver PROPERTIES FOLDER "tests/ClassParser/Class")

file(GLOB TEST_FILES "*.java")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    espresso_java_test(classparser-jit ${TEST_WE} -g:none)
endforeach()

