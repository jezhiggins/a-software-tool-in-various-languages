#ifndef A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_MATCHER_HPP
#define A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_MATCHER_HPP

#include <string>

class matcher {
public:
    bool match(const std::string& line) const;
};

matcher make_matcher(const std::string& pattern);

#endif //A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_MATCHER_HPP
