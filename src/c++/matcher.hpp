#ifndef A_SOFTWARE_TOOL_MATCHER_HPP
#define A_SOFTWARE_TOOL_MATCHER_HPP

#include <string>
#include <functional>
#include <vector>

class string_walker;

class matcher {
public:
    typedef typename std::function<bool(string_walker& line)> match_fn;

    matcher(match_fn fn, size_t advance) :
        fn_(fn),
        advance_(advance) {
    }

    bool match(string_walker& line) const;

    void make_closure(match_fn remainder_fn) {
      remainder_fn_ = remainder_fn;
    }

private:
    bool one_match(string_walker& line) const;
    bool closure_match(string_walker& line) const;

    match_fn fn_;
    match_fn remainder_fn_;
    size_t advance_;
};

matcher make_matcher(string_walker& pattern_walker);

#endif //A_SOFTWARE_TOOL_MATCHER_HPP
