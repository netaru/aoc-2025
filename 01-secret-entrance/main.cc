#include <iostream>
#include <print>
#include <ranges>
#include <string>

#include "util.h"

using namespace std;

int get_number(const string& s) { return stoi(s.substr(1)) * (s[0] == 'L' ? -1 : 1); }

int main(int argc, char* argv[]) {
    int  x = 50, part1 = 0, part2 = 0;
    auto turn = [&part2](int x, int dx) {
        int change = dx < 0 ? -1 : 1;
        for (int i = 0; i < abs(dx); ++i) {
            x += change;
            if (x == 100) {
                x = 0;
            } else if (x < 0) {
                x = 99;
            }
            if (x == 0) { part2++; }
        }
        return x;
    };
    for (int dx : read_lines(cin) | vs::transform(get_number)) {
        x = turn(x, dx);
        if (x == 0) { part1++; }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
