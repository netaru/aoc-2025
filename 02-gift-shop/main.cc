#include <algorithm>
#include <cstddef>
#include <iostream>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.h"

using namespace std;

bool is_valid(i64 x) {
    string s = to_string(x);
    if (s.size() % 2 == 0) {
        size_t      len = s.size() / 2;
        string_view sv{ s };
        return sv.substr(0, len) != sv.substr(len);
    }
    return true;
}

bool is_valid_strict(i64 x) {
    string s     = to_string(x);
    size_t len   = s.size() / 2;
    for (size_t u = 1; u <= len; u++) {
        if (s.size() % u != 0) continue;
        auto ss = s | vs::chunk(u) | rs::to<vector<string>>();
        if (rs::all_of(ss, [&ss](string s) { return s == ss[0]; })) { return false; }
    }
    return true;
}

int main(int argc, char *argv[]) {
    i64 part1 = 0, part2 = 0;
    for (auto rn : ints<i64>(join(split(read(cin), "-"), " ")) | vs::chunk(2)) {
        for (i64 x = rn[0]; x <= rn[1]; x++) {
            if (!is_valid(x)) { part1 += x; }
            if (!is_valid_strict(x)) { part2 += x; }
        }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
