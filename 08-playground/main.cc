#include <iostream>
#include <print>
#include <queue>

#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<pos3> points;
    priority_queue<edge, vector<edge>, greater<edge>> edges;
    for (auto values : ints<i64>(read(cin)) | vs::chunk(3)) { points.emplace_back(values[0], values[1], values[2]); }
    for (size_t i = 0; i < points.size(); ++i) {
        for (auto j = i + 1; j < points.size(); ++j) { edges.emplace(i, j, points[i].euclidean_distance(points[j])); }
    }

    i64 n = 0, part1, part2;
    auto uf = union_find(points.size());
    for (; !edges.empty() and uf.size() > 1; edges.pop(), ++n) {
        edge e = edges.top();
        if (!uf.connected(e.i, e.j)) {
            if (uf.merge(e.i, e.j) == 1) {
                part2 = points[e.i].x * points[e.j].x;
            } else if (n == 1000) {
                auto sz = uf.sz;
                rs::sort(sz, greater<>());
                part1 = rs::fold_left(sz | vs::take(3), 1l, multiplies<>());
            }
        }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
