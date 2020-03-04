#include <iostream>

#include "arguments.hpp"
#include "matcher.hpp"

std::string get_pattern(int argc, const char* argv[]);
matcher make_matcher(const std::string& pattern);
std::string read_line(std::istream& is);

int main(int argc, const char* argv[]) {
  auto const pattern = get_pattern(argc, argv);

  auto const matcher = make_matcher(pattern);

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