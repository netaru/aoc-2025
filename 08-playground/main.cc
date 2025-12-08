#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <set>

#include "util.h"

using namespace std;

struct point {
    i64 x, y, z;

    i64 euclidean_distance(const point &other) const {
        return sqrt(powl(x - other.x, 2) + powl(y - other.y, 2) + powl(z - other.z, 2));
    }
};

bool operator<(const point &lhs, const point &rhs) {
    if (lhs.x != rhs.x) { return lhs.x < rhs.x; }
    if (lhs.y != rhs.y) { return lhs.y < rhs.y; }
    return lhs.z < rhs.z;
}

struct connection {
    point p, q;
    i64 distance;
    connection(point p1, point p2) : p(p1), q(p2), distance(p.euclidean_distance(q)) {}
};

int main(int argc, char *argv[]) {
    vector<point> points;
    vector<connection> connections;
    vector<set<point>> circuits;
    for (auto values : ints<i64>(read(cin)) | vs::chunk(3)) {
        points.emplace_back(values[0], values[1], values[2]);
        set<point> circuit;
        circuit.insert(points.back());
        circuits.emplace_back(circuit);
    }
    for (auto first = points.cbegin(); first < points.cend(); ++first) {
        for (auto second = first + 1; second < points.cend(); ++second) { connections.emplace_back(*first, *second); }
    }
    rs::sort(connections, [](auto lhs, auto rhs) { return lhs.distance < rhs.distance; });
    auto find_circuit(
            [&](point p) { return rs::find_if(circuits, [&p](auto circuit) { return circuit.contains(p); }); });

    i64 n = 0, part1, part2;
    for (auto iter = connections.cbegin(); true; iter++, n++) {
        connection c = *iter;
        auto first = find_circuit(c.p);
        auto second = find_circuit(c.q);
        if (first == second) { continue; }
        for (auto p : *second) { first->insert(p); }
        circuits.erase(second);
        if (circuits.size() == 1) {
            part2 = c.p.x * c.q.x;
            break;
        }
        if (n == 1000) {
            rs::sort(circuits, [](auto lhs, auto rhs) { return lhs.size() > rhs.size(); });
            part1 = rs::fold_left(
                    circuits | vs::take(3) | vs::transform([](auto x) { return x.size(); }), 1l, multiplies<>());
        }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
