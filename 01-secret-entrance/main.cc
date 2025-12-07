#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <string>

#include "util.h"

using namespace std;

int part1(span<int> xs) {
    return rs::count_if(
            xs | vs::transform([dial = 50](int x) mutable { return (dial = dave::mod(dial + x, 100)); }),
            [](int x) { return x == 0; });
}

int part2(span<int> xs) {
    auto fn = [dial = 50](int x) mutable {
        int count = abs(x / 100), mod = x % 100;
        if ((x < 0 and dial != 0 and dial + mod <= 0) or (x > 0 and dial + mod >= 100)) count++;
        dial = dave::mod(dial + x, 100);
        return count;
    };
    return rs::fold_left(xs | vs::transform(fn), 0, plus<>());
}

int main(int argc, char* argv[]) {
    vector<int> xs = read_lines(cin) |
                     vs::transform([](string s) { return stoi(s.substr(1)) * (s[0] == 'L' ? -1 : 1); }) |
                     rs::to<vector>();
    println("Part1: {}", part1(xs));
    println("Part2: {}", part2(xs));
    return 0;
}
