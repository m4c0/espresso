espresso_run_cpp_tests(vm-class espresso-vm "VM/Class")

add_executable(espresso-vm-class-testdriver class-driver.cpp)
target_compile_features(espresso-vm-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-vm-class-testdriver PUBLIC espresso-vm)
set_target_properties(espresso-vm-class-testdriver PROPERTIES FOLDER "tests/VM/Class")

file(GLOB TEST_FILES "*.java")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    espresso_java_test(vm-class ${TEST_WE} -g:none)
endforeach()


