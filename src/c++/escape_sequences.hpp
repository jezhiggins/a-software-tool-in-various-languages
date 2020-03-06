#ifndef BRUMJS_ESCAPE_SEQUENCES_HPP
#define BRUMJS_ESCAPE_SEQUENCES_HPP

#include <map>

auto const escape_char = '@';

std::map<char, char> const& escape_sequences();

#endif //BRUMJS_ESCAPE_SEQUENCES_HPP
