# Hopefully, we will only use Java inside tests, to create .class files
find_package(Java COMPONENTS Development)

# A basic Java test. Compiles the .java to a .class and runs it with a driver
function(espresso_java_test FOLDER TEST_WE DEBUG_FLAG)
    set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_WE}.java")
    set(BINARY "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class")
    set(TEST_NAME ${FOLDER}-${TEST_WE})
    add_custom_command(
        OUTPUT ${BINARY}
        MAIN_DEPENDENCY ${SOURCE}
        COMMAND "${Java_JAVAC_EXECUTABLE}" ${DEBUG_FLAG} -d "${CMAKE_CURRENT_BINARY_DIR}" ${SOURCE})
    add_test(${TEST_NAME} espresso-${FOLDER}-testdriver ${BINARY})
    add_custom_target(espresso-${TEST_NAME} ALL DEPENDS ${BINARY})
endfunction()

add_subdirectory(ClassParser)
add_subdirectory(Milestones)

