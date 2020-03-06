#include "escape_sequences.hpp"

static auto escapes = std::map<char, char> {
  { 'n', '\n' },
  { 't', '\t' }
};

std::map<char, char> const& escape_sequences() {
  return escapes;
}
