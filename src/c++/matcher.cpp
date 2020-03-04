#include "matcher.hpp"

bool matcher::match(const std::string& line) const {
  return false;
}

matcher make_matcher(const std::string& pattern) {
  return matcher();
}
