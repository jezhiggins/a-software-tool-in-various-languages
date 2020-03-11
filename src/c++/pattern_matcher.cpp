#include "pattern_matcher.hpp"
#include "matcher.hpp"
#include "string_walker.hpp"

bool amatch(
    string_walker line,
    pattern_matcher::matcher_iterator from,
    pattern_matcher::matcher_iterator end
);

bool closure_match(
    string_walker& line,
    pattern_matcher::matcher_iterator from,
    pattern_matcher::matcher_iterator end
);

///////////////////////////////
bool pattern_matcher::match(
    std::string const& line
) const {
  auto matches = false;

  auto walker = string_walker(line);

  while (!walker.eol() && !matches) {
      matches = amatch(
          walker.clone(),
          matchers_.begin(),
          matchers_.end()
      );
      ++walker;
  }

  return matches;
}

bool amatch(
    string_walker line,
    pattern_matcher::matcher_iterator from,
    pattern_matcher::matcher_iterator end
) {
    if (from == end)
        return false;

    for ( ; from != end; ++from) {
        if (from->is_closure())
            return closure_match(line, from, end);

        if (!from->match(line))
            return false;
    }

    return true;
}

bool closure_match(
    string_walker& line,
    pattern_matcher::matcher_iterator from,
    pattern_matcher::matcher_iterator end
) {
  line.snapshot();
  while (from->match(line));
  do {
      if (amatch(line.clone(), from + 1, end))
          return true;
  } while (line.rewind());

  return false;
}

///////////////////////////////
auto const closure_char = '*';

pattern_matcher make_pattern_matcher(std::string const& pattern) {
    auto matchers = std::vector<matcher> { };

    for (auto pw = string_walker { pattern, 0 }; !pw.eol(); ++pw) {
        if (*pw == closure_char && !pw.bol()) {
            matchers.back().make_closure();
            continue;
        }

        auto m = make_matcher(pw);
        matchers.push_back(m);
    }

    return pattern_matcher { matchers };
}
