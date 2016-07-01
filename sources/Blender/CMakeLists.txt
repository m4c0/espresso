add_library(espresso-blender-static STATIC
    JVMClass.cpp
    )
target_include_directories(espresso-blender-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(espresso-blender-static PRIVATE cxx_auto_type)
set_target_properties(espresso-blender-static PROPERTIES OUTPUT_NAME espresso-blender)
target_link_libraries(espresso-blender-static PUBLIC espresso-classparser-static)
target_link_libraries(espresso-blender-static PUBLIC espresso-vm-static)

add_library(espresso-blender SHARED)
target_link_libraries(espresso-blender PUBLIC espresso-blender-static)

