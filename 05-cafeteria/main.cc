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
    lohi(vector<i64> in) : low(in[0]), high(in[1]) {}
    lohi(const lohi &other) : low(other.low), high(other.high) {}
    bool inside(i64 n) const { return n >= low and n <= high; }
    i64 count() const { return high - low + 1; }
    bool overlap(const lohi &other) const { return inside(other.low) or inside(other.high); }
    void merge(const auto &other) {
        low = min(low, other.low);
        high = max(high, other.high);
    }
};

vector<lohi> merge(vector<lohi> in) {
    vector<lohi> result;
    vector<lohi>::iterator first, second;
    for (first = in.begin(); first < in.end(); first = second) {
        second = first + 1;
        lohi current(*first);
        for (; second < in.end() and current.overlap(*second); ++second) { current.merge(*second); }
        result.push_back(current);
    }
    return result;
}

vector<lohi> parse(vector<string> input) {
    vector<lohi> intervals = input | vs::transform([](string s) { return lohi(ints<i64>(s)); }) | rs::to<vector>();
    return merge(dave::sort(intervals, [](auto lhs, auto rhs) { return lhs.low < rhs.low; }));
}

int main(int argc, char *argv[]) {
    vector<string> input = split(read(cin), "\n\n");
    vector<lohi> intervals = parse(split(dave::replace(input[0], "-", " "), "\n"));
    auto in_any_range = [&intervals](i64 n) {
        return rs::find_if(intervals, [&n](lohi obj) { return obj.inside(n); }) != intervals.end();
    };
    auto is_fresh = [&in_any_range](i64 v) -> i64 { return in_any_range(v) ? 1 : 0; };
    println("Part1: {}", rs::fold_left(ints<i64>(input[1]) | vs::transform(is_fresh), 0ll, plus<i64>()));
    println("Part2: {}", rs::fold_left(intervals | vs::transform([](auto i) { return i.count(); }), 0ll, plus<i64>()));
    return 0;
}
