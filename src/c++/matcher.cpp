#include <map>
#include "matcher.hpp"
#include "string_walker.hpp"
#include "escape_sequences.hpp"
#include "character_class.hpp"

bool matcher::match(string_walker& line) const {
    auto ok = fn_(line);
    if (ok) line.advance(advance_);
    return ok;
}

///////////////////////////////
bool is_bol(string_walker& line) {
    return line.bol();
}
bool is_eol(string_walker& line) {
    return line.eol();
}
bool is_any(string_walker& line) {
    return true;
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

/////////////////////////////////
auto const match_any = '?';
auto const match_bol = '%';
auto const match_eol = '$';
auto const start_class = '[';

char escape(std::string const& pattern, size_t& index) {
    if (index+1 == pattern.length())
        return escape_char;
    char ch = pattern[++index];
    auto is_escape = escape_sequences().find(ch);
    return (is_escape != escape_sequences().end())
           ? is_escape->second
           : ch;
}

matcher make_class_matcher(std::string const& pattern, size_t& index) {
    auto character_class = read_character_class(pattern, index);

    return matcher(is_in_class(character_class), 1);
}

matcher make_matcher(std::string const& pattern, size_t& index) {
    char ch = pattern[index];

    if (ch == match_any)
        return matcher(is_any, 0);
    if (ch == match_bol && index == 0)
        return matcher(is_bol, 0);
    if (ch == match_eol && index == pattern.length()-1)
        return matcher(is_eol, 0);
    if (ch == start_class)
        return make_class_matcher(pattern, ++index);

    if (ch == escape_char)
        ch = escape(pattern, index);
    return matcher(is_literal(ch), 1);
}
