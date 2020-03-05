#ifndef BRUMJS_STRING_WALKER_HPP
#define BRUMJS_STRING_WALKER_HPP

#include <string>

class string_walker {
public:
    string_walker(std::string const& line) :
        line_(line) {
    }

    bool eol() const { return pos_ == line_.length(); }
    char peek() const {
        throw_if_eol();
        return line_[pos_]
    }
    char operator*() {
        throw_if_eol();
        return line_[pos_];
    }
    void advance(size_t count) {
        pos_ += count;
    }

private:
    void throw_if_eol() {
        if (eol())
            throw std::runtime_error("End of input");
    }

    std::string const& line_;
    size_t pos_;
};

#endif //BRUMJS_STRING_WALKER_HPP
