cmake_minimum_required(VERSION 3.5) # I tested on 3.5 - feel free to test on lower ones and do a pull-request :)
project(espresso VERSION 0.0.1 LANGUAGES CXX)

enable_testing()

add_subdirectory(sources)
add_subdirectory(tests)

