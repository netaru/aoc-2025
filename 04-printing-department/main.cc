#include <algorithm>
#include <iostream>
#include <iterator>
#include <print>

#include "util.h"

using namespace std;

auto removable_pred(const plane<char> &plane) {
    return [&plane](pos p) -> bool {
        return rs::count_if(add(p, compass), [&plane](pos at) { return plane.get(at) == '@'; }) < 4;
    };
}

auto removable(const plane<char> &plane) {
    vector<pos> result;
    rs::copy_if(plane.find('@'), back_inserter(result), removable_pred(plane));
    return result;
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
