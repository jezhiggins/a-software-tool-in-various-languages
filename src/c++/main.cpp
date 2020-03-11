#include <iostream>

#include "arguments.hpp"
#include "pattern_matcher.hpp"

std::string get_pattern(int argc, const char* argv[]);
std::string read_line(std::istream& is);

void do_main(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {
    try {
        do_main(argc, argv);
    } catch(std::exception& ex) {
        std::cerr << "OOPS! " << ex.what() << "\n";
        return -1;
    }
}

void do_main(int argc, const char* argv[]) {
    auto const pattern_string = get_pattern(argc, argv);

    auto const pattern = make_pattern_matcher(pattern_string);

    while(std::cin) {
        auto const line = read_line(std::cin);
        if (pattern.match(line))
            std::cout << line << '\n';
    } // while
}

std::string get_pattern(int argc, const char* argv[]) {
    auto const args = make_arguments(argc, argv);
    if (args.size() != 1) {
        std::cout << "usage: find pattern\n";
        std::exit(-1);
    }

    return args[0];
} // get_pattern

std::string read_line(std::istream& is) {
    std::string line;
    std::getline(is, line);
    return line;
}