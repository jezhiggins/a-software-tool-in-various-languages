#ifndef A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
#define A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP

#include <string>
#include <vector>
#include "matcher.hpp"

class string_walker;

typedef std::vector<matcher> matcher_list;

class pattern_matcher {
public:
    explicit pattern_matcher(matcher_list const& matchers) :
        matchers_(matchers) {
    } // pattern_matcher

    bool match(std::string const& line) const;

private:
    matcher_list matchers_;
};

pattern_matcher make_pattern_matcher(std::string const& pattern);

#endif //A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
