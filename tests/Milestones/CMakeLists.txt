add_executable(espresso-milestone1-testdriver driver.cpp)
target_compile_features(espresso-milestone1-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-milestone1-testdriver PUBLIC espresso-blender)
set_target_properties(espresso-milestone1-testdriver PROPERTIES FOLDER "tests/milestones")

espresso_java_test(milestone1 Milestone1 -g:none)

