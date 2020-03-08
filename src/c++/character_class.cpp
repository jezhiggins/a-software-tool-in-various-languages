#include "character_class.hpp"
#include "escape_sequences.hpp"
#include "string_walker.hpp"

auto const dash_char = '-';
auto const end_class = ']';

bool is_valid_dash_range(string_walker& pw);
bool is_valid_escape_sequence(string_walker& pw);
void expand_escape_sequence(
    std::back_insert_iterator<std::string>& dest,
    string_walker& pw
);
void expand_dash_range(
    std::back_insert_iterator<std::string>& dest,
    string_walker& pw
);

std::string read_character_class(
    string_walker& pw
) {
    std::string expanded;
    auto insert = std::back_inserter(expanded);

    while (!pw.eol() && *pw != end_class) {
        if (is_valid_escape_sequence(pw)) {
            expand_escape_sequence(insert, pw);
            continue;
        }
        if (is_valid_dash_range(pw)) {
            expand_dash_range(insert, pw);
            continue;
        }

        insert = *pw++;
    }

    if (pw.eol())
        throw std::runtime_error("Bad pattern - missing ]");

    return expanded;
} // read_character_class

bool is_valid_dash_range(string_walker& pw) {
    if (*pw != dash_char)
        return false;

    if (pw.bol() || !pw.available())
        return false;

    auto prev = pw.peek_before();
    auto next = pw.peek_ahead();

    if (prev >= next)
        return false;

    return
        (std::isdigit(prev) && std::isdigit(next))
        || (std::islower(prev) && std::islower(next))
        || (std::isupper(prev) && std::isupper(next));
} // in_valid_dash_range

void expand_dash_range(
    std::back_insert_iterator<std::string>& dest,
    string_walker& pw
) {
    char from = pw.peek_before() + 1;
    char to = *++pw;

    while (from <= to)
        dest = from++;

    pw++;
} // expand_dash_range

bool is_valid_escape_sequence(string_walker& pw) {
    if (*pw != escape_char)
        return false;

    return pw.available();
} // is_valid_escape_sequence

void expand_escape_sequence(
    std::back_insert_iterator<std::string>& dest,
    string_walker& pw
) {
    auto candidate = *++pw;
    auto escape = escape_sequences().find(candidate);

    dest = escape != escape_sequences().end()
        ? escape->second
        : candidate;

    ++pw;
} // expand_escape_sequence
