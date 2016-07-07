add_executable(espresso-blender-jvmclass-findmethod-testdriver class-driver.cpp)
target_compile_features(espresso-blender-jvmclass-findmethod-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-blender-jvmclass-findmethod-testdriver PUBLIC espresso-blender)
set_target_properties(espresso-blender-jvmclass-findmethod-testdriver PROPERTIES FOLDER "tests/Blender/JVMClass")

espresso_java_test(blender-jvmclass-findmethod EmptyClass -g:none
    "<init>" "()V")
espresso_java_test(blender-jvmclass-findmethod EmptyStaticInitializer -g:none 
    "<clinit>" "()V"
    "<init>" "()V")
espresso_java_test(blender-jvmclass-findmethod ClassWithMethods -g:none
    "<init>" "()V"
    "voidMethod" "()V"
    "intMethod" "(F)I")

espresso_java_test(blender-jvmclass-findmethod NonExistentMethod -g:none "noSuchMethod" "()V")
set_tests_properties(blender-jvmclass-findmethod-NonExistentMethod PROPERTIES WILL_FAIL TRUE)

espresso_java_test(blender-jvmclass-findmethod NonExistentSignature -g:none "exists" "(I)V")
set_tests_properties(blender-jvmclass-findmethod-NonExistentSignature PROPERTIES WILL_FAIL TRUE)

