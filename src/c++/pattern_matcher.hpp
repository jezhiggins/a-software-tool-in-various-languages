#ifndef A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
#define A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP

#include <string>
#include <vector>
#include "matcher.hpp"

class string_walker;

class pattern_matcher {
public:
    explicit pattern_matcher(std::vector<matcher> const& matchers) :
      matchers_(matchers) {
    } // pattern_matcher

    bool match(std::string const& line) const;

    typedef std::vector<matcher>::const_iterator matcher_iterator;

private:
    std::vector<matcher> matchers_;
};

pattern_matcher make_pattern_matcher(std::string const& pattern);

#endif //A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
