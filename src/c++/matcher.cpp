#include <map>
#include "matcher.hpp"
#include "string_walker.hpp"
#include "escape_sequences.hpp"
#include "character_class.hpp"

bool matcher::match(string_walker& line) const {
    return closure_
        ? closure_match(line)
        : one_match(line);
}

bool matcher::one_match(string_walker& line) const {
    auto ok = fn_(line);
    if (ok) line.advance(advance_);
    return ok;
}

bool matcher::closure_match(string_walker &line) const {
    while (one_match(line));
    return true;
}

///////////////////////////////
bool is_bol(string_walker& line) {
    return line.bol();
}
bool is_eol(string_walker& line) {
    return line.eol();
}
bool is_any(string_walker& line) {
    return !line.eol();
}
auto is_literal(char c) {
    return [c](string_walker& line) {
        return *line == c;
    };
}
auto is_in_class(std::string const& chars) {
    return [chars](string_walker& line) {
        return chars.find(*line) != std::string::npos;
    };
}
auto is_not_in_class(std::string const& chars) {
  return [chars](string_walker& line) {
      return chars.find(*line) == std::string::npos;
  };
}

/////////////////////////////////
auto const match_any = '?';
auto const match_bol = '%';
auto const match_eol = '$';
auto const start_class = '[';
auto const class_negated = '^';

char escape(string_walker& pattern_walker) {
    if (!pattern_walker.available())
        return escape_char;
    char ch = *++pattern_walker;
    auto is_escape = escape_sequences().find(ch);
    return (is_escape != escape_sequences().end())
           ? is_escape->second
           : ch;
}

matcher make_class_matcher(string_walker& pattern_walker) {
    auto character_class = read_character_class(pattern_walker);

    if (character_class[0] == class_negated)
      return matcher(is_not_in_class(character_class.substr(1)), 1);
    return matcher(is_in_class(character_class), 1);
}

matcher make_matcher(string_walker& pattern_walker) {
    char ch = *pattern_walker;

    if (ch == match_any)
        return matcher(is_any, 1);
    if (ch == match_bol && pattern_walker.bol())
        return matcher(is_bol, 0);
    if (ch == match_eol && !pattern_walker.available())
        return matcher(is_eol, 0);
    if (ch == start_class)
        return make_class_matcher(++pattern_walker);

    if (ch == escape_char)
        ch = escape(pattern_walker);
    return matcher(is_literal(ch), 1);
}
