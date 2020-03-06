#ifndef BRUMJS_STRING_WALKER_HPP
#define BRUMJS_STRING_WALKER_HPP

#include <string>

class string_walker {
public:
    string_walker(std::string const& line, size_t initial_offset) :
        line_(line),
        pos_(initial_offset) {
    }
    string_walker(string_walker const&) = delete;
    string_walker& operator=(string_walker const&) = delete;

    bool bol() const { return pos_ == 0; }
    bool eol() const { return pos_ == line_.length(); }
    char operator*() const {
        throw_if_eol();
        return line_[pos_];
    }
    void advance(size_t count) {
        pos_ += count;
    }

private:
    void throw_if_eol() const {
        if (eol())
            throw std::runtime_error("End of input");
    }

    std::string const& line_;
    size_t pos_;
};

#endif //BRUMJS_STRING_WALKER_HPP
