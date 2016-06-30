espresso_run_cpp_tests(vm-class espresso-vm "VM/Class")

add_executable(espresso-vm-class-testdriver class-driver.cpp)
target_compile_features(espresso-vm-class-testdriver PRIVATE cxx_auto_type)
target_link_libraries(espresso-vm-class-testdriver PUBLIC espresso-classparser)
target_link_libraries(espresso-vm-class-testdriver PUBLIC espresso-vm)
set_target_properties(espresso-vm-class-testdriver PROPERTIES FOLDER "tests/VM/Class")

espresso_java_test(vm-class EmptyClass -g:none
    "<init>" "()V")
espresso_java_test(vm-class EmptyStaticInitializer -g:none 
    "<clinit>" "()V"
    "<init>" "()V")
espresso_java_test(vm-class ClassWithMethods -g:none
    "<init>" "()V"
    "voidMethod" "()V"
    "intMethod" "(F)I")

espresso_java_test(vm-class NonExistentMethod -g:none "noSuchMethod" "()V")
set_tests_properties(vm-class-NonExistentMethod PROPERTIES WILL_FAIL TRUE)

espresso_java_test(vm-class NonExistentSignature -g:none "exists" "(I)V")
set_tests_properties(vm-class-NonExistentSignature PROPERTIES WILL_FAIL TRUE)

