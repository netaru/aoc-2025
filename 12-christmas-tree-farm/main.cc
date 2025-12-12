#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>

#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto ss = split(read(cin), "\n\n");

    auto brackets = bind(dave::count_occurrences<false>, placeholders::_1, "#");
    vector<size_t> sizes = ss | vs::take(ss.size() - 1) | vs::transform(brackets) | rs::to<vector>();

    auto spacefn = [&](auto v) { return sizes[get<0>(v)] * get<1>(v); };
    auto pred = [&](auto xs) {
        auto capacity = rs::fold_left(xs | vs::take(2), 1, multiplies<>());
        auto required_space = rs::fold_left(vs::enumerate(xs | vs::drop(2)) | vs::transform(spacefn), 0, plus<>());
        return required_space < capacity;
    };
    println("Part1: {}", rs::count_if(split(ss.back(), "\n") | vs::transform(ints<i64>), pred));
    return 0;
}
