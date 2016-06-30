add_library(espresso-vm-static STATIC
    Class/Base.cpp
    Class/DlOpen.cpp
    Class/Parsed.cpp
    ClassResolver.cpp
    )
target_include_directories(espresso-vm-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(espresso-vm-static PRIVATE cxx_auto_type)
set_target_properties(espresso-vm-static PROPERTIES OUTPUT_NAME espresso-vm)
# TODO: Put "VM::Parsed" into another lib to break this dependency
target_link_libraries(espresso-vm-static PUBLIC espresso-classparser-static)

add_library(espresso-vm SHARED)
target_link_libraries(espresso-vm PUBLIC espresso-vm-static)

