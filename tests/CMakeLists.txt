# Hopefully, we will only use Java inside tests, to create .class files
find_package(Java COMPONENTS Development)

### Start of "this should go into a module"

# A basic Java test. Compiles the .java to a .class and runs it with a driver
function(espresso_java_test FOLDER TEST_WE DEBUG_FLAG)
    set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_WE}.java")
    set(BINARY "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class")
    set(TEST_NAME ${FOLDER}-${TEST_WE})
    add_custom_command(
        OUTPUT ${BINARY}
        MAIN_DEPENDENCY ${SOURCE}
        COMMAND "${Java_JAVAC_EXECUTABLE}" ${DEBUG_FLAG} -d "${CMAKE_CURRENT_BINARY_DIR}" ${SOURCE})
    add_test(${TEST_NAME} espresso-${FOLDER}-testdriver ${BINARY} ${ARGN})
    add_custom_target(espresso-${TEST_NAME} ALL DEPENDS ${BINARY})
    set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 4)
endfunction()

function(espresso_run_cpp_tests TEST_INFIX TEST_LIB TEST_SUBFOLDER)
    file(GLOB TEST_FILES "[0-9]*.cpp")
    foreach(TEST_FILE ${TEST_FILES})
        get_filename_component(TEST_WE ${TEST_FILE} NAME_WE)
        set(TEST_NAME ${TEST_INFIX}-${TEST_WE})
        set(TEST espresso-${TEST_NAME})

        add_executable(${TEST} ${TEST_FILE})
        target_compile_features(${TEST} PRIVATE cxx_auto_type)
        target_link_libraries(${TEST} PUBLIC ${TEST_LIB})
        set_target_properties(${TEST} PROPERTIES FOLDER "tests/${TEST_SUBFOLDER}")

        add_test(${TEST_NAME} ${TEST})
        set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 4)
    endforeach()
endfunction()

### End of "this should go into a module"

add_subdirectory(ClassParser)
add_subdirectory(VM)
add_subdirectory(Milestones)

