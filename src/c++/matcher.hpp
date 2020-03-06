#ifndef A_SOFTWARE_TOOL_MATCHER_HPP
#define A_SOFTWARE_TOOL_MATCHER_HPP

#include <string>
#include <functional>

class string_walker;

class matcher {
public:
    typedef typename std::function<bool(string_walker& line)> match_fn;

    matcher(match_fn fn, size_t advance) :
        fn_(fn),
        advance_(advance) {
    }

    bool match(string_walker& line) const;

private:
    match_fn fn_;
    size_t advance_;
};

matcher make_matcher(std::string const& pattern, size_t& index);

#endif //A_SOFTWARE_TOOL_MATCHER_HPP
