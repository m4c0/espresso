function(espresso_milestone TEST_NAME CLASS_NAME)
    add_executable(espresso-${TEST_NAME}-testdriver ${TEST_NAME}.cpp)
    target_compile_features(espresso-${TEST_NAME}-testdriver PRIVATE cxx_auto_type)
    target_link_libraries(espresso-${TEST_NAME}-testdriver PUBLIC espresso-blender)
    set_target_properties(espresso-${TEST_NAME}-testdriver PROPERTIES FOLDER "tests/milestones")

    espresso_java_test(${TEST_NAME} ${CLASS_NAME} -g:none)
endfunction()

espresso_milestone(milestone1 Milestone1)
espresso_milestone(milestone2 Milestone2)
espresso_milestone(milestone3 Milestone3)

