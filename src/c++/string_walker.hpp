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
        if (eol()) return 0;
        return line_[pos_];
    }
    string_walker& operator++() {
      throw_if_eol();

      advance(1);
      return *this;
    }
    void advance(size_t count) {
        if (count)
          throw_if_eol();
        pos_ += count;
    }

private:
    void throw_if_eol() const {
        if (eol())
            throw std::runtime_error("End of input : " + line_);
    }

    std::string const& line_;
    size_t pos_;
};

#endif //BRUMJS_STRING_WALKER_HPP
