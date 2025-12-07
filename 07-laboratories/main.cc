#include <algorithm>
#include <functional>
#include <iostream>
#include <print>

#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
    plane plane(cin);
    i64 part1 = 0;
    vector<i64> beams(plane.data[0].size(), 0);
    auto fn = [&](i64 x, i64 y, char ch) {
        if (ch == 'S') {
            beams[x] = 1;
        } else if (ch == '^' and beams[x] > 0) {
            beams[x - 1] += beams[x];
            beams[x + 1] += beams[x];
            beams[x] = 0;
            part1++;
        }
    };
    plane.apply(fn);
    println("Part1: {}", part1);
    println("Part2: {}", rs::fold_left(beams, 0, plus<>()));
    return 0;
}
