project(brumjs)
cmake_minimum_required(VERSION 3.15)

add_executable(brumjs_find
        main.cpp
        arguments.cpp arguments.hpp
        pattern_matcher.cpp pattern_matcher.hpp
        matcher.cpp matcher.hpp
        character_class.cpp character_class.hpp
        string_walker.hpp
        escape_sequences.cpp escape_sequences.hpp)
set_property(TARGET brumjs_find PROPERTY CXX_STANDARD 17)
