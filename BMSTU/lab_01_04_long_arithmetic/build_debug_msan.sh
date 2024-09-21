#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

for file in *.c; do
    base=$(basename -s .c "$file")
    clang -std=gnu99 -Wall -Werror -Wpedantic -Wextra -g -fPIE -fno-omit-frame-pointer -fsanitize=memory -c "$path_to_script"/"$file" -o "$path_to_script"/"$base".o
done

clang -fsanitize=memory -pie -o "$path_to_script"/app.exe "$path_to_script"/*.o
