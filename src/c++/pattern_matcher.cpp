#include "pattern_matcher.hpp"
#include "matcher.hpp"
#include "string_walker.hpp"

bool amatch(string_walker line, matcher_list const& matchers);

///////////////////////////////
bool pattern_matcher::match(std::string const& line) const {
  for (auto walker = string_walker(line); !walker.eol(); ++walker)
      if (amatch(walker.clone(), matchers_))
          return true;

  return false;
}

bool amatch(string_walker line, matcher_list const& matchers) {
    if (matchers.empty())
        return false;

    for (auto const& matcher : matchers)
        if (!matcher.match(line))
            return false;

    return true;
}

///////////////////////////////
auto const closure_char = '*';

matcher_list make_pattern_matcher(string_walker pattern) {
    auto matchers = matcher_list { };

    for ( ; !pattern.eol(); ++pattern) {
        if (*pattern == closure_char && !pattern.bol()) {
            ++pattern;
            auto remainder = make_pattern_matcher(pattern.clone());
            auto remainder_fn = [remainder](string_walker const& line) { return amatch(line.clone(), remainder); };
            matchers.back().make_closure(remainder_fn);
            break;
        }

        auto m = make_matcher(pattern);
        matchers.push_back(m);
    }

    return matchers;
}

pattern_matcher make_pattern_matcher(std::string const& pattern) {
  auto matchers = make_pattern_matcher(string_walker {pattern, 0});
  return pattern_matcher { matchers };
}

