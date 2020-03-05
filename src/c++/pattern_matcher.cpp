#include <map>
#include "pattern_matcher.hpp"

using namespace std::string_literals;

///////////////////////////////
bool isBol(const std::string& line, size_t index) {
  return index == 0;
}
bool isEol(const std::string& line, size_t index) {
  return index == line.length();
}
bool isAny(const std::string& line, size_t index) {
  return true;
}
auto isLiteral(char c) {
  return [c](const std::string &line, size_t index) {
      return line[index] == c;
  };
}

///////////////////////////////
bool pattern_matcher::match(
    const std::string& line
) const {
  size_t index = 0;
  bool matches = false;

  while (index != line.length() && !matches) {
    matches = amatch(line, index);
    ++index;
  }

  return matches;
}

bool pattern_matcher::amatch(
    const std::string& line,
    size_t index
) const {
 for (auto m : matchers_)
    if (!m.match(line, index))
      return false;

  return true;
}

///////////////////////////////
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

  if (ch == '?')
    return matcher(isAny, 0);
  if (ch == '%' && index == 0)
    return matcher(isBol, 0);
  if (ch == '$' && index == pattern.length()-1)
    return matcher(isEol, 0);
  if (ch == '[')
    return make_class_matcher(pattern, ++index);

  if (ch == escape_char)
    ch = escape(pattern, index);
  return matcher(isLiteral(ch), 1);
}

pattern_matcher make_pattern_matcher(std::string const& pattern) {
  std::vector<matcher> matchers;

  for (size_t i = 0; i != pattern.length(); ++i) {
    auto m = make_matcher(pattern, i);
    matchers.push_back(m);
  }

  return pattern_matcher { matchers };
}
