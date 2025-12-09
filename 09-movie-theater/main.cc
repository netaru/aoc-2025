#include <algorithm>
#include <iostream>
#include <print>
#include <queue>
#include <ranges>

#include "util.h"

using namespace std;

struct theater {
    vector<pos> points;
    vector<pair<size_t, size_t>> lines;
    priority_queue<edge> rects;

    theater(istream &is) : points(ints<i64>(read(is)) | vs::chunk(2) | vs::transform(dave::to_pos) | rs::to<vector>()) {
        for (size_t i = 0; i < points.size(); ++i) { lines.emplace_back(i, (i + 1) % points.size()); }
        auto area = [](pos p, pos q) -> i64 { return (abs(p.real() - q.real()) + 1) * (abs(p.imag() - q.imag()) + 1); };
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) { rects.emplace(i, j, area(points[i], points[j])); }
        }
    }

    bool less(auto xs) { return max(xs[0], xs[1]) <= min(xs[2], xs[3]); }
    bool greater(auto xs) { return min(xs[0], xs[1]) >= max(xs[2], xs[3]); }

    bool is_inside(edge e) {
        return rs::all_of(lines, [&](auto p) {
            vector<pos> xs{ points[e.i], points[e.j], points[p.first], points[p.second] };
            return less(xs | vs::transform(dave::x)) or greater(xs | vs::transform(dave::x)) or
                   less(xs | vs::transform(dave::y)) or greater(xs | vs::transform(dave::y));
        });
    }

    int solve() {
        i64 part1 = rects.top().weight;
        for (; !rects.empty() and !is_inside(rects.top()); rects.pop());
        println("Part1: {}", part1);
        println("Part2: {}", rects.top().weight);
        return 0;
    }
};

int main(int argc, char *argv[]) { return theater(cin).solve(); }
