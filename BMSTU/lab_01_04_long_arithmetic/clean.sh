#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

rm -f "$path_to_script"/*.exe
rm -f "$path_to_script"/*.exec
rm -f "$path_to_script"/*.out
rm -f "$path_to_script"/*.o
rm -f "$path_to_script"/*.gc*
rm -f "$path_to_script"/func_tests/scripts/*temp.txt*
rm -f "$path_to_script"/func_tests/data/*.bin
rm -f "$path_to_script"/*.bin

rm -f "$path_to_script"/src/*.exe
rm -f "$path_to_script"/src/*.exec
rm -f "$path_to_script"/src/*.out
rm -f "$path_to_script"/src/*.o
rm -f "$path_to_script"/src/*.gc*
rm -f "$path_to_script"/func_tests/scripts/*temp.txt*
rm -f "$path_to_script"/func_tests/data/*.bin
rm -f "$path_to_script"/src/*.bin
exit 0
