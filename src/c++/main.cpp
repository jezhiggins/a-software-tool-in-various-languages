#include <iostream>

#include "arguments.hpp"
#include "pattern_matcher.hpp"

std::string get_pattern(int argc, const char* argv[]);
pattern_matcher make_pattern_matcher(std::string const& pattern);
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
    auto const pattern = get_pattern(argc, argv);

    auto const matcher = make_pattern_matcher(pattern);

    while(std::cin) {
        auto const line = read_line(std::cin);
        if (matcher.match(line))
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