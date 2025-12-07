#include <cstddef>
#include <iostream>
#include <print>
#include <ranges>
#include <string_view>

#include "util.h"

using namespace std;

bool repeated(string_view s, size_t u) {
    if (u == 0 or s.size() % u != 0) return false;
    return dave::count_occurrences<false>(s, s.substr(0, u)) == s.size() / u;
}

template <int part>
bool is_valid(i64 x) {
    string s = to_string(x);
    size_t len = s.size() / 2;
    if constexpr (part == 1) {
        if (s.size() % 2 != 0) return true;
        return !repeated(s, len);
    } else {
        for (size_t u = 1; u <= len; u++) {
            if (repeated(s, u)) return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    i64 part1 = 0, part2 = 0;
    for (auto rn : ints<i64>(dave::replace(read(cin), "-", " ")) | vs::chunk(2)) {
        for (i64 x = rn[0]; x <= rn[1]; x++) {
            if (!is_valid<1>(x)) { part1 += x; }
            if (!is_valid<2>(x)) { part2 += x; }
        }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
