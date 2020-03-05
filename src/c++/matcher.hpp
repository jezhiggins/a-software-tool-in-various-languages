#ifndef A_SOFTWARE_TOOL_MATCHER_HPP
#define A_SOFTWARE_TOOL_MATCHER_HPP

#include <string>
#include <functional>

class matcher {
public:
    typedef typename std::function<bool(std::string const&, size_t)> match_fn;

    matcher(match_fn fn, size_t advance) :
        fn_(fn),
        advance_(advance) {
    }

    bool match(std::string const& line, size_t& index) const;

private:
    match_fn fn_;
    size_t advance_;
};

matcher make_matcher(std::string const& pattern, size_t& index);

#endif //A_SOFTWARE_TOOL_MATCHER_HPP
