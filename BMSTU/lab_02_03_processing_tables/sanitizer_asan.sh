#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

for file in src/*.c; do
    base=$(basename -s .c "$file")
    clang -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -g -fno-omit-frame-pointer -fsanitize=address -c "$path_to_script"/"$file" -o "$path_to_script"/src/"$base".o
done

clang -fsanitize=address -o "$path_to_script"/app.exe "$path_to_script"/src/*.o
