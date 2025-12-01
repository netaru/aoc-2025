#!/usr/bin/env bash

if [ -d "$day_folder" ]; then
    echo "$day_folder" Already exists..
    exit 1
fi

source "$HOME/.local/bin/aoc_init"

year=2025
day=$(printf "%2s" $1 | tr ' ' '0')

get-aoc-instruction "$year" "$1" "$(pwd)"

name=$(grep "Day $1:" instructions.org | tr -c -d '[A-Za-z :]' | awk -F: '{print $2}' | tr ' ' '-' | tr '[A-Z]' '[a-z]')
day_folder="$day${name::-1}"

if [ -d "$day_folder" ]; then
    echo "$day_folder" Already exists..
    rm instructions.org
    exit 1
fi

mkdir "$day_folder"
touch "$day_folder/test.txt"
get-aoc-input "$year" "$1" "$day_folder"
mv instructions.org "$day_folder/instructions.org"

cat > "$day_folder/main.cc"  <<EOF
#include <iostream>
#include <print>

#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
    println("This is the result");
    return 0;
}
EOF

cmake -Bbuild -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=Yes .; ln -sf ./build/compile_commands.json compile_commands.json
