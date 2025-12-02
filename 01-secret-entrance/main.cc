#include <iostream>
#include <print>
#include <string>

#include "util.h"

using namespace std;

int main(int argc, char* argv[]) {
    int  x = 50, part1 = 0, part2 = 0;
    auto turn = [&part2](int x, string line) {
        int dx = line[0] == 'L' ? -1 : 1;
        for (int i = 0; i < stoi(line.substr(1)); ++i) {
            x += dx;
            if (x == 100) {
                x = 0;
            } else if (x < 0) {
                x = 99;
            }
            if (x == 0) { part2++; }
        }
        return x;
    };
    for (string line : read_lines(cin)) {
        if ((x = turn(x, line)) == 0) { part1++; }
    }
    println("Part1: {}", part1);
    println("Part2: {}", part2);
    return 0;
}
