add_library(espresso-class-parser-static STATIC
    Attribute.cpp
    Class.cpp
    ClassEntry.cpp
    Field.cpp
    Method.cpp
    Logger.cpp
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
target_include_directories(espresso-class-parser-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(espresso-class-parser-static PRIVATE cxx_auto_type)
set_target_properties(espresso-class-parser-static PROPERTIES OUTPUT_NAME espresso-class-parser)

add_library(espresso-class-parser SHARED)
target_link_libraries(espresso-class-parser PUBLIC espresso-class-parser-static)

