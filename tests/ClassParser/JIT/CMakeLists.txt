file(GLOB TEST_FILES "[0-9]*.cpp")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
    set(TEST_NAME classparser-jit-${TEST_WE})
    set(TEST espresso-${TEST_NAME})
    add_executable(${TEST} ${TEST_FILE})
    target_compile_features(${TEST} PRIVATE cxx_auto_type)
    target_link_libraries(${TEST} PUBLIC espresso-classparser)
    set_target_properties(${TEST} PROPERTIES FOLDER "tests/ClassParser/JIT")

    add_test(${TEST_NAME} ${TEST})
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

