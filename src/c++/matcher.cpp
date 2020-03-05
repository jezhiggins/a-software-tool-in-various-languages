#include <map>
#include "matcher.hpp"

bool matcher::match(std::string const& line, size_t& index) const {
    auto ok = fn_(line, index);
    if (ok) index += advance_;
    return ok;
}

///////////////////////////////
bool isBol(std::string const& line, size_t index) {
    return index == 0;
}
bool isEol(std::string const& line, size_t index) {
    return index == line.length();
}
bool isAny(std::string const& line, size_t index) {
    return true;
}
auto isLiteral(char c) {
    return [c](std::string const& line, size_t index) {
        return line[index] == c;
    };
}
auto isInClass(std::string const& chars) {
    return [chars](std::string const& line, size_t index) {
        return chars.find(line[index]) != std::string::npos;
    };
}

/////////////////////////////////
auto const match_any = '?';
auto const match_bol = '%';
auto const match_eol = '$';
auto const start_class = '[';
auto const end_class = ']';
auto const escape_char = '@';

auto escape_sequence = std::map<char, char> {
    { 'n', '\n' },
    { 't', '\t' }
};

char escape(std::string const& pattern, size_t& index) {
    if (index+1 == pattern.length())
        return escape_char;
    char ch = pattern[++index];
    auto is_escape = escape_sequence.find(ch);
    return (is_escape != escape_sequence.end())
           ? is_escape->second
           : ch;
}

matcher make_class_matcher(std::string const& pattern, size_t& index) {
    throw std::runtime_error("Haven't implemented class matcher yet");
}

matcher make_matcher(std::string const& pattern, size_t& index) {
    char ch = pattern[index];

    if (ch == match_any)
        return matcher(isAny, 0);
    if (ch == match_bol && index == 0)
        return matcher(isBol, 0);
    if (ch == match_eol && index == pattern.length()-1)
        return matcher(isEol, 0);
    if (ch == start_class)
        return make_class_matcher(pattern, ++index);

    if (ch == escape_char)
        ch = escape(pattern, index);
    return matcher(isLiteral(ch), 1);
}
