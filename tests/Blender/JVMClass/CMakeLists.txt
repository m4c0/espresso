add_subdirectory(FindMethod)

add_executable(espresso-blender-jvmclass-clinit-testdriver clinit-driver.cpp)
target_compile_features(espresso-blender-jvmclass-clinit-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-blender-jvmclass-clinit-testdriver PUBLIC espresso-blender)
set_target_properties(espresso-blender-jvmclass-clinit-testdriver PROPERTIES FOLDER "tests/Blender/JVMClass")

espresso_java_test(blender-jvmclass-clinit ClinitTest -g:none)

