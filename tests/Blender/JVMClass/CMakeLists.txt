add_executable(espresso-blender-jvmclass-testdriver class-driver.cpp)
target_compile_features(espresso-blender-jvmclass-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-blender-jvmclass-testdriver PUBLIC espresso-blender)
set_target_properties(espresso-blender-jvmclass-testdriver PROPERTIES FOLDER "tests/Blender/JVMClass")

espresso_java_test(blender-jvmclass EmptyClass -g:none
    "<init>" "()V")
espresso_java_test(blender-jvmclass EmptyStaticInitializer -g:none 
    "<clinit>" "()V"
    "<init>" "()V")
espresso_java_test(blender-jvmclass ClassWithMethods -g:none
    "<init>" "()V"
    "voidMethod" "()V"
    "intMethod" "(F)I")

espresso_java_test(blender-jvmclass NonExistentMethod -g:none "noSuchMethod" "()V")
set_tests_properties(blender-jvmclass-NonExistentMethod PROPERTIES WILL_FAIL TRUE)

espresso_java_test(blender-jvmclass NonExistentSignature -g:none "exists" "(I)V")
set_tests_properties(blender-jvmclass-NonExistentSignature PROPERTIES WILL_FAIL TRUE)

