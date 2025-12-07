#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <utility>

#include "util.h"

using namespace std;

pair<i64, function<i64(i64, i64)>> setup(char c) {
    if (c == '*') return { 1l, multiplies<i64>() };
    return { 0l, plus<i64>() };
}

i64 calc(span<string> ss) {
    const auto &[init, fn] = setup(ss[0][0]);
    return rs::fold_left(ss | vs::drop(1) | vs::transform([](string s) { return stol(s); }), init, fn);
}

i64 cephalopod_maths(span<string> ss) {
    i64 sum = 0;
    vector<i64> current;
    for (const auto &s : ss) {
        current.push_back(stol(s));
        if (char c = s.back(); "*+"sv.contains(c)) {
            const auto &[init, fn] = setup(c);
            sum += rs::fold_left(current, init, fn);
            current.clear();
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    plane<char> part2(cin);
    plane<string> part1(part2.as_string());
    auto xs = split(part2.rotate_left().as_string(), "\n");
    println("Part1: {}", rs::fold_left(part1.rotate_right().data | vs::transform(calc), 0ll, plus<i64>()));
    println("Part2: {}", cephalopod_maths(xs));
    return 0;
}
