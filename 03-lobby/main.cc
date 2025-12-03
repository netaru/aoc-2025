#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <span>
#include <vector>

#include "util.h"

using namespace std;

template <int n>
i64 max_voltage(span<i64> bank) {
    i64 sum = 0;
    auto index = bank.begin(), end = bank.begin() + (bank.size() - n + 1);
    for (size_t u = 0; u < n; ++u, index += 1, end += 1) {
        index = max_element(index, end);
        sum = sum * 10 + *index;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    auto fun = [](string s) { return s | vs::transform([](char c) -> i64 { return c - '0'; }) | rs::to<vector>(); };
    auto banks = read_lines(cin) | vs::transform(fun) | rs::to<vector>();
    println("Part1: {}", rs::fold_left(banks | vs::transform(max_voltage<2>), 0, plus<i64>()));
    println("Part2: {}", rs::fold_left(banks | vs::transform(max_voltage<12>), 0, plus<i64>()));
    return 0;
}
