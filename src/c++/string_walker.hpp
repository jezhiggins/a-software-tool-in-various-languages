#ifndef BRUMJS_STRING_WALKER_HPP
#define BRUMJS_STRING_WALKER_HPP

#include <string>

class string_walker {
public:
    string_walker(std::string const& line, size_t initial_offset = 0) :
        line_(line),
        pos_(initial_offset) {
    }
    string_walker(string_walker const&) = delete;
    string_walker& operator=(string_walker const&) = delete;

    string_walker clone() const {
      return string_walker(line_, pos_);
    }

    bool bol() const { return pos_ == 0; }
    bool eol() const { return pos_ == line_.length(); }
    bool available() const { return pos_ < line_.length()-1; }
    char peek_before() const { return line_[pos_-1]; }
    char peek_ahead() const { return line_[pos_+1]; }
    char operator*() const {
        if (eol()) return 0;
        return line_[pos_];
    }
    string_walker& operator++() {
      throw_if_eol();

      advance(1);
      return *this;
    }
    string_walker const operator++(int) {
      throw_if_eol();

      auto p = pos_;

      advance(1);

      return string_walker { line_, p };
    }
    void advance(size_t count) {
        if (count)
          throw_if_eol();
        pos_ += count;
    }

    void snapshot() {
      snapshot_ = pos_;
    }
    bool rewind() {
      --pos_;
      return pos_ > snapshot_;
    }
private:
    void throw_if_eol() const {
        if (eol())
            throw std::runtime_error("End of input : " + line_);
    }

    std::string const& line_;
    size_t pos_;
    size_t snapshot_;
};

#endif //BRUMJS_STRING_WALKER_HPP
