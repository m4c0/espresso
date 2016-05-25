add_library(espresso-class-parser-static STATIC main.cpp)
set_target_properties(espresso-class-parser-static PROPERTIES OUTPUT_NAME espresso-class-parser)

add_library(espresso-class-parser SHARED)
target_link_libraries(espresso-class-parser PRIVATE espresso-class-parser-static)

