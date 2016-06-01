# Hopefully, we will only use Java inside tests, to create .class files
find_package(Java COMPONENTS Development)

# A basic Java test. Compiles the .java to a .class and runs it with a driver
function(espresso_java_test FOLDER TEST_WE DEBUG_FLAG)
    set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_WE}.java")
    set(BINARY "${CMAKE_CURRENT_BINARY_DIR}/${TEST_WE}.class")
    add_custom_command(
        OUTPUT ${BINARY}
        MAIN_DEPENDENCY ${SOURCE}
        COMMAND "${Java_JAVAC_EXECUTABLE}" ${DEBUG_FLAG} -d "${CMAKE_CURRENT_BINARY_DIR}" ${SOURCE})
    add_test(${FOLDER}-${TEST_WE} espresso-${FOLDER}-testdriver ${BINARY})
    add_custom_target(espresso-${FOLDER}-${TEST_WE} ALL DEPENDS ${BINARY})
endfunction()

add_subdirectory(ClassParser)
add_subdirectory(Milestones)

