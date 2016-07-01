find_library(JIT jit)
if(NOT EXISTS ${JIT})
    message(FATAL_ERROR "libjit not found")
endif()

add_library(espresso-classparser-static STATIC
    Attributed.cpp
    Class.cpp
    ClassEntry.cpp
    DataStream.cpp
    Field.cpp
    JIT.cpp
    Method.cpp
    Logger.cpp
    Attribute/Base.cpp
    Attribute/Code.cpp
    ConstantPool/ClassInfo.cpp
    ConstantPool/Double.cpp
    ConstantPool/Float.cpp
    ConstantPool/FieldRefInfo.cpp
    ConstantPool/Integer.cpp
    ConstantPool/InterfaceMethodRefInfo.cpp
    ConstantPool/Long.cpp
    ConstantPool/Manager.cpp
    ConstantPool/MethodRefInfo.cpp
    ConstantPool/NameAndType.cpp
    ConstantPool/RefInfo.cpp
    ConstantPool/StringInfo.cpp
    ConstantPool/Utf8.cpp
    )
target_include_directories(espresso-classparser-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(espresso-classparser-static PRIVATE cxx_auto_type)
set_target_properties(espresso-classparser-static PROPERTIES OUTPUT_NAME espresso-classparser)

add_library(espresso-classparser SHARED)
target_link_libraries(espresso-classparser PUBLIC espresso-classparser-static)
target_link_libraries(espresso-classparser PUBLIC ${JIT})

