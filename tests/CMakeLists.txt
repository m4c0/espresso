# Hopefully, we will only use Java inside tests, to create .class files
find_package(Java COMPONENTS Development)

add_subdirectory(class-parser)

