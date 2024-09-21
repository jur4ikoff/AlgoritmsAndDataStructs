#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

for file in *.c; do
    base=$(basename -s .c "$file")
    clang -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -fno-omit-frame-pointer -fsanitize=undefined -g -c "$path_to_script"/"$file" -o "$path_to_script"/"$base".o
done

clang -fsanitize=undefined -o "$path_to_script"/app.exe "$path_to_script"/*.o
