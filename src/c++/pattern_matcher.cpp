#include "pattern_matcher.hpp"
#include "matcher.hpp"

///////////////////////////////
bool pattern_matcher::match(
    const std::string& line
) const {
  size_t index = 0;
  bool matches = false;

  while (index != line.length() && !matches) {
    matches = amatch(line, index);
    ++index;
  }

  return matches;
}

bool pattern_matcher::amatch(
    const std::string& line,
    size_t index
) const {
 for (auto m : matchers_)
    if (!m.match(line, index))
      return false;

  return true;
}

///////////////////////////////
pattern_matcher make_pattern_matcher(std::string const& pattern) {
  std::vector<matcher> matchers;

  for (size_t i = 0; i != pattern.length(); ++i) {
    auto m = make_matcher(pattern, i);
    matchers.push_back(m);
  }

  return pattern_matcher { matchers };
}
