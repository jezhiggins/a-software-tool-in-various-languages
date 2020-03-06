#include "pattern_matcher.hpp"
#include "matcher.hpp"
#include "string_walker.hpp"

///////////////////////////////
bool pattern_matcher::match(
    std::string const& line
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
    std::string const& line,
    size_t index
) const {
    auto walker = string_walker(line, index);
    for (auto m : matchers_)
        if (!m.match(walker))
            return false;

    return true;
}

///////////////////////////////
auto const closure_char = '*';

pattern_matcher make_pattern_matcher(std::string const& pattern) {
  auto matchers = std::vector<matcher> { };

  for (auto pw = string_walker { pattern, 0 }; !pw.eol(); ++pw) {
    if (*pw == closure_char && !pw.bol()) {
      matchers.back().closure();
      continue;
    }

    auto m = make_matcher(pw);
    matchers.push_back(m);
  }

  return pattern_matcher { matchers };
}
