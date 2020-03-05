project(brumjs)
cmake_minimum_required(VERSION 3.15)

add_executable(brumjs_find main.cpp arguments.cpp pattern_matcher.cpp pattern_matcher.hpp matcher.cpp matcher.hpp string_walker.hpp)
set_property(TARGET brumjs_find PROPERTY CXX_STANDARD 17)
