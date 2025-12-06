#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <string>

#include "util.h"

using namespace std;

i64 calc(vector<string> row) {
    i64 init = 0;
    function<i64(i64, i64)> fn = plus<i64>();
    if (row[0][0] == '*') {
        init = 1;
        fn = multiplies<i64>();
    }
    return rs::fold_left(row | vs::drop(1) | vs::transform([](string s) { return stoi(s); }), init, fn);
}

i64 cephalopod_maths(vector<string> input) {
    i64 sum = 0;
    vector<i64> tmp;
    for (auto s : input) {
        tmp.push_back(stoi(s));
        if (s.contains("*")) {
            sum += rs::fold_left(tmp, 1ll, multiplies<i64>());
            tmp.clear();
        } else if (s.contains("+")) {
            sum += rs::fold_left(tmp, 0ll, plus<i64>());
            tmp.clear();
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    plane<char> part2(cin);
    plane<string> part1(part2.as_string());
    println("Part1: {}", rs::fold_left(part1.rotate_right().data | vs::transform(calc), 0ll, plus<i64>()));
    println("Part2: {}", cephalopod_maths(split(part2.rotate_left().as_string(), "\n")));
    return 0;
}
