#include <iostream>
#include <unordered_map>
#include <vector>

#include "util.h"

using namespace std;

using simple_cache_t = unordered_map<size_t, i64>;
using cache_t = unordered_map<size_t, array<i64, 4>>;
using edges_t = unordered_map<size_t, vector<size_t>>;

struct reactor {
    vector<string> nodes;
    array<size_t, 5> xs;
    edges_t edges;
    cache_t cache;
    simple_cache_t simple;

    size_t add(string s) {
        size_t u = nodes.size();
        nodes.emplace_back(s);
        cache[u] = { -1, -1, -1, -1 };
        return u;
    }

    size_t find(const string &s) {
        if (auto iter = rs::find(nodes, s); iter != nodes.end()) { return distance(nodes.begin(), iter); }
        return add(s);
    }

    reactor(istream &is) {
        for (auto e : read_lines(is) | vs::transform([](auto s) { return split(dave::remove(s, ':')); }))
            rs::for_each(e | vs::drop(1), [&, i = find(e[0])](auto s) { edges[i].push_back(find(s)); });
        xs = { find("you"), find("svr"), find("dac"), find("fft"), find("out") };
    }

    size_t part1(size_t current) {
        if (simple.contains(current)) { return simple[current]; }
        if (current == xs[4]) { return simple[current] = 1; }
        return simple[current] =
                       rs::fold_left(edges[current] | vs::transform([&](auto n) { return part1(n); }), 0, plus<>());
    }

    int nstate(size_t n, int state) { return state | (n == xs[2] ? 1 : 0) | (n == xs[3] ? 2 : 0); }
    size_t part2(size_t current, int state = 0) {
        if (cache[current][state] != -1) { return cache[current][state]; }
        if (current == xs[4]) { return cache[current][state] = static_cast<i64>(state == 3); }
        return cache[current][state] = rs::fold_left(
                       edges[current] | vs::transform([&](auto n) { return part2(n, nstate(n, state)); }), 0, plus<>());
    }
};

int main(int argc, char *argv[]) {
    reactor r(cin);
    println("Part1: {}", r.part1(r.xs[0]));
    println("Part2: {}", r.part2(r.xs[1]));
    return 0;
}
