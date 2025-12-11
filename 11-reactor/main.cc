#include <iostream>
#include <map>
#include <print>
#include <unordered_map>
#include <vector>

#include "util.h"

using namespace std;

using cache_t = map<tuple<size_t, size_t>, i64>;
using edges_t = unordered_map<size_t, vector<size_t>>;

struct reactor {
    vector<string> nodes;
    edges_t edges;
    cache_t cache;

    size_t find(const string &s) {
        if (auto iter = rs::find(nodes, s); iter != nodes.end()) { return distance(nodes.begin(), iter); }
        nodes.emplace_back(s);
        return nodes.size() - 1;
    }

    reactor(istream &is) {
        for (auto e : read_lines(is) | vs::transform([](auto s) { return split(dave::remove(s, ':')); }))
            rs::for_each(e | vs::drop(1), [&, i = find(e[0])](auto s) { edges[i].push_back(find(s)); });
    }

    i64 solve(pair<size_t, size_t> p) {
        if (cache.contains(p)) { return cache[p]; }
        if (p.first == p.second) { return 1; }
        return cache[p] = rs::fold_left(
                       edges[p.first] | vs::transform([&](auto n) { return solve({ n, p.second }); }), 0, plus<>());
    }

    i64 solve(string from, string to) { return solve({ find(from), find(to) }); }
};

int main(int argc, char *argv[]) {
    reactor r(cin);
    i64 path1 = r.solve("svr", "fft") * r.solve("fft", "dac") * r.solve("dac", "out");
    i64 path2 = r.solve("svr", "dac") * r.solve("dac", "fft") * r.solve("fft", "out");
    println("Part1: {}", r.solve("you", "out"));
    println("Part2: {}", path1 + path2);
    return 0;
}
