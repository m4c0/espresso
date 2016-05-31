add_library(espresso-class-parser-static STATIC
    Class.cpp
    constant-pool/ClassInfo.cpp
    constant-pool/FieldRefInfo.cpp
    constant-pool/InterfaceMethodRefInfo.cpp
    constant-pool/Item.cpp
    constant-pool/Manager.cpp
    constant-pool/MethodRefInfo.cpp
    constant-pool/NameAndType.cpp
    constant-pool/RefInfo.cpp
    constant-pool/StringInfo.cpp
    constant-pool/Utf8.cpp
    )
target_include_directories(espresso-class-parser-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(espresso-class-parser-static PRIVATE cxx_auto_type)
set_target_properties(espresso-class-parser-static PROPERTIES OUTPUT_NAME espresso-class-parser)

add_library(espresso-class-parser SHARED)
target_link_libraries(espresso-class-parser PUBLIC espresso-class-parser-static)

