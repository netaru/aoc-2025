#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>

#include "util.h"

using namespace std;

auto removable_pred(const plane<char> &plane) {
    return [&plane](pos p) -> bool {
        return rs::count_if(add(p, compass), [&plane](pos at) { return plane.get(at) == '@'; }) < 4;
    };
}

auto removable(const plane<char> &plane) {
    return plane.find('@') | vs::filter(removable_pred(plane)) | rs::to<vector>();
}

int main(int argc, char *argv[]) {
    plane plane(cin);
    auto rm = removable(plane);
    size_t part1 = rm.size(), part2 = 0;
    do {
        part2 += rm.size();
        plane.set(rm, '.');
    } while ((rm = removable(plane)).size() > 0);
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
