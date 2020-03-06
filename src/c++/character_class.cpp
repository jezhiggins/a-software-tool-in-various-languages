#include "character_class.hpp"
#include "escape_sequences.hpp"

auto const dash_char = '-';
auto const end_class = ']';

bool is_valid_dash_range(
    std::string const&arg,
    std::string::const_iterator const&c
);
bool is_valid_escape_sequence(
    std::string const&arg,
    std::string::const_iterator const&c
);
void expand_escape_sequence(
    std::back_insert_iterator<std::string>& dest,
    std::string::const_iterator& c
);
void expand_dash_range(
    std::back_insert_iterator<std::string>& dest,
    std::string::const_iterator &c
);

std::string read_character_class(
    std::string const& arg,
    size_t& index
) {
  std::string expanded;
  auto insert = std::back_inserter(expanded);

  auto c = arg.begin() + index;

  while (c != arg.end() && *c != end_class) {
    if (is_valid_escape_sequence(arg, c)) {
      expand_escape_sequence(insert, c);
      continue;
    }
    if (is_valid_dash_range(arg, c)) {
      expand_dash_range(insert, c);
      continue;
    }

    insert = *c++;
  }

  if (c == arg.end())
    throw std::runtime_error("Bad pattern - missing ]");

  index += std::distance(arg.begin() + index, c);
  return expanded;
} // read_character_class

bool is_valid_dash_range(
    std::string const&arg,
    std::string::const_iterator const&c
) {
  if (*c != dash_char)
    return false;

  if ((c == arg.begin())
      || (c+1 == arg.end()))
    return false;

  auto prev = *(c - 1);
  auto next = *(c + 1);

  if (prev >= next)
    return false;

  return
      (std::isdigit(prev) && std::isdigit(next))
      || (std::islower(prev) && std::islower(next))
      || (std::isupper(prev) && std::isupper(next));
} // in_valid_dash_range

void expand_dash_range(
    std::back_insert_iterator<std::string>& dest,
    std::string::const_iterator &c) {
  char from = *(c - 1) + 1;
  char to = *++c;

  while (from <= to)
    dest = from++;

  c++;
} // expand_dash_range

bool is_valid_escape_sequence(
    std::string const&arg,
    std::string::const_iterator const&c
) {
  if (*c != escape_char)
    return false;

  return (c+1 != arg.end());
} // is_valid_escape_sequence

void expand_escape_sequence(
    std::back_insert_iterator<std::string>& dest,
    std::string::const_iterator& c
) {
  auto candidate = *++c;
  auto escape = escape_sequences().find(candidate);

  dest = escape != escape_sequences().end()
         ? escape->second
         : candidate;

  ++c;
} // expand_escape_sequence
