#include <algorithm>
#include <format>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <vector>

#include "util.h"

using namespace std;

struct machine {
    vector<bool> which;
    vector<vector<i64>> buttons;
    vector<i64> voltage;
    map<vector<bool>, vector<pair<vector<bool>, i64>>> patterns;
    map<vector<i64>, i64> cache;

    machine(string line, truth_table &tt) {
        for (auto s : split(line, " ")) {
            if (s[0] == '[') {
                which = s | vs::filter([](char c) { return !"[]"sv.contains(c); }) |
                        vs::transform([](char c) { return c == '#'; }) | rs::to<vector>();
            } else if (s[0] == '(') {
                vector<i64> button(which.size(), 0);
                for (auto i : ints<i64>(s)) { button[i]++; }
                buttons.push_back(button);
            } else {
                voltage = ints<i64>(s);
            }
        }
        for (auto pressed : tt(buttons.size())) {
            vector<bool> m(voltage.size(), false);
            for (auto [current, _] : vs::zip(buttons, pressed) | vs::filter([](auto p) { return get<1>(p); })) {
                for (size_t u = 0; u < current.size(); ++u) {
                    if (current[u] > 0) { m[u] = !m[u]; }
                }
            }
            patterns[m].push_back({ pressed, rs::count(pressed, true) });
        }
    }

    vector<bool> build(vector<i64> values) {
        return values | vs::transform([](auto i) -> bool { return i % 2; }) | rs::to<vector>();
    }

    i64 solve(vector<i64> values) {
        if (cache.contains(values)) { return cache[values]; }
        if (rs::count(values, 0) == values.size()) { return 0; }

        i64 result = 1000000;
        for (const auto &[pattern, cost] : patterns[build(values)]) {
            auto pressed = vs::zip(buttons, pattern) | vs::filter([](auto p) { return get<1>(p); }) | vs::keys;
            vector<i64> delta = rs::fold_left(pressed, vector<i64>(values.size(), 0), dave::vplus<i64>);
            if (rs::all_of(vs::zip(delta, values), [](auto vs) { return get<0>(vs) <= get<1>(vs); })) {
                result = min(result, 2 * solve(dave::divides(dave::vminus(values, delta), 2l)) + cost);
            }
        }
        return cache[values] = result;
    }

    i64 part1() {
        return rs::min(patterns[which] | vs::values);
    }
    i64 part2() { return solve(voltage); }
};

int main(int argc, char *argv[]) {
    truth_table tt;
    vector<machine> machines =
            read_lines(cin) | vs::transform([&](auto s) { return machine(s, tt); }) | rs::to<vector>();
    println("Part1: {}", rs::fold_left(machines | vs::transform(&machine::part1), 0, plus<>()));
    println("Part2: {}", rs::fold_left(machines | vs::transform(&machine::part2), 0, plus<>()));
    return 0;
}
