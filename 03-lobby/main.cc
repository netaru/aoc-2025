#include <cstddef>
#include <iostream>
#include <print>
#include <ranges>
#include <span>
#include <vector>

#include "util.h"

using namespace std;

size_t find_largest(span<i64> bank, size_t index, int end) {
    int max = 0;
    for (size_t u = index; u < end; u++) {
        if (bank[u] > max) {
            index = u;
            max   = bank[u];
        }
    }
    return index;
}

i64 max_voltage(span<i64> bank, size_t n) {
    i64 sum = 0;
    size_t index = 0;
    for (size_t u = 0; u < n; ++u) {
        size_t where = find_largest(bank, index, bank.size() - (n - (u + 1)));
        sum = sum * 10 + bank[where];
        index = where + 1;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    i64 part1 = 0, part2 = 0;
    for (const auto line : read_lines(cin)) {
        auto bank = line | vs::transform([](char c) -> i64 { return c - '0'; }) | rs::to<vector>();
        part1 += max_voltage(bank, 2);
        part2 += max_voltage(bank, 12);
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
