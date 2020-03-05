#ifndef A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP
#define A_SOFTWARE_TOOL_IN_VARIOUS_LANGUAGES_PATTERN_MATCHER_HPP

#include <string>
#include <vector>
#include <functional>

enum class match_type {
    Bol,
    Literal
};

class matcher {
public:
    typedef typename std::function<bool(const std::string&, size_t)> match_fn;

    matcher(match_fn fn, size_t advance) :
      fn_(fn),
      advance_(advance) {
    }

    bool match(const std::string& line, size_t& index) const {
      auto ok = fn_(line, index);
      if (ok) index += advance_;
      return ok;
    }

private:
    match_fn fn_;
    size_t advance_;
};

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
