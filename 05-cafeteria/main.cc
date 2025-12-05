#include <algorithm>
#include <format>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

#include "util.h"

using namespace std;

struct lohi {
    i64 low, high;
    lohi(i64 _low, i64 _high) : low(_low), high(_high) {}
    lohi(const lohi &other) : low(other.low), high(other.high) {}
    bool inside(i64 n) const { return n >= low and n <= high; }
    i64 count() const { return high - low + 1; }
    bool overlap(const lohi &other) { return inside(other.low) or inside(other.high); }

    void new_low(i64 n) { low = min(low, n); }
    void new_high(i64 n) { high = max(high, n); }
};

vector<lohi> merge(vector<lohi> in) {
    vector<lohi> result;
    vector<lohi>::iterator first, second;
    for (first = in.begin(); first < in.end(); first = second) {
        second = first + 1;
        lohi current(*first);
        for (; second < in.end() and current.overlap(*second); ++second) {
            current.new_low(second->low);
            current.new_high(second->high);
        }
        result.push_back(current);
    }
    return result;
}

vector<lohi> parse(vector<string> input) {
    vector<lohi> result;
    for (auto &s : input) {
        vector<i64> current = ints<i64>(s);
        result.emplace_back(current[0], current[1]);
    }
    return merge(dave::sort(result, [](auto lhs, auto rhs) { return lhs.low < rhs.low; }));
}

int main(int argc, char *argv[]) {
    vector<string> input = split(read(cin), "\n\n");
    vector<i64> values = ints<i64>(input[1]);
    vector<lohi> intervals = parse(split(dave::replace(input[0], "-", " "), "\n"));

    i64 part1 = 0;
    for (const auto &v : values) {
        for (const auto &i : intervals) {
            if (i.inside(v)) {
                part1++;
                break;
            }
        }
    }
    println("Part1: {}", part1);
    println("Part2: {}", rs::fold_left(intervals | vs::transform([](auto i) { return i.count(); }), 0ll, plus<i64>()));
    return 0;
}
