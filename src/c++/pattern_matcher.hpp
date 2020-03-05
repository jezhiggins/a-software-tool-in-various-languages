#ifndef A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
#define A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP

#include <string>
#include <vector>
#include "matcher.hpp"

class pattern_matcher {
public:
    pattern_matcher(std::vector<matcher> const& matchers) :
      matchers_(matchers) {
    } // pattern_matcher

    bool match(const std::string& line) const;

private:
    bool amatch(const std::string& line, size_t index) const;

    std::vector<matcher> matchers_;
};

pattern_matcher make_pattern_matcher(const std::string& pattern);

#endif //A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
