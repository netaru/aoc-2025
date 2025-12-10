#include <deque>
#include <format>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <unordered_set>

#include "util.h"

using namespace std;

using button = vector<size_t>;

struct machine {
    vector<bool> facit;
    vector<button> buttons;
    vector<size_t> voltage;

    machine(string line) {
        for (auto s : split(line, " ")) {
            if (s[0] == '[') {
                facit = s | vs::filter([](char c) { return !"[]"sv.contains(c); }) |
                        vs::transform([](char c) { return c == '#'; }) | rs::to<vector>();
            } else if (s[0] == '(') {
                buttons.push_back(ints<size_t>(s));
            } else {
                voltage = ints<size_t>(s);
            }
        }
    }

    string as_string() const {
        return format("machine [lights: {}, buttons: {}, voltage: {}]", facit, buttons, voltage);
    }

    i64 shortest() {
        deque<pair<vector<bool>, i64>> queue{ { vector<bool>(facit.size(), false), 0 } };
        unordered_set<vector<bool>> seen;
        while (!queue.empty()) {
            const auto &[lights, n] = pop(queue);
            if (seen.contains(lights)) { continue; }
            if (lights == facit) { return n; }
            seen.insert(lights);
            for (const auto b : buttons) {
                auto nlights = lights;
                for (const auto u : b) { nlights[u] = !nlights[u]; }
                queue.push_back({ nlights, n + 1 });
            }
        }
        return 0;
    }
};

int main(int argc, char *argv[]) {
    vector<machine> machines = read_lines(cin) | vs::transform([](auto s) { return machine(s); }) | rs::to<vector>();
    println("Part1: {}", rs::fold_left(machines | vs::transform(&machine::shortest), 0, plus<>()));
    return 0;
}
