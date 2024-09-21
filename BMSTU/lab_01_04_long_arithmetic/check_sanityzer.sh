#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")
# Проверка тестов санитайзером build_debug_asan
echo "Build adress sanitizer"
./build_debug_asan.sh
res=$?
if [[ "$res" != 0 ]]; then
    echo "Error while compiling"
    exit 1
fi

"$path_to_script"/func_tests/scripts/func_tests.sh
echo

# Проверка тестов санитайзером build_debug_msan
echo "Build memory sanitizer"
./build_debug_msan.sh
res=$?
if [[ "$res" != 0 ]]; then
    echo "Error while compiling"
    exit 1
fi

"$path_to_script"/func_tests/scripts/func_tests.sh
echo

# Проверка тестов санитайзером build_debug_ubsan
echo "Build undefined behaviour sanitizer"
./build_debug_ubsan.sh
res=$?
if [[ "$res" != 0 ]]; then
    echo "Error while compiling"
    exit 1
fi

"$path_to_script"/func_tests/scripts/func_tests.sh s
