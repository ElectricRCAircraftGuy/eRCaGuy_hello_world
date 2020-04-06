#!/bin/bash

echo "=========================="
echo "1/2: C tests"
echo "gcc -Wall -Werror -g3 -std=c11 -o rounding_integer_division rounding_integer_division.c && ./rounding_integer_division"
echo "=========================="
echo ""
gcc -Wall -Werror -g3 -std=c11 -o rounding_integer_division rounding_integer_division.c && ./rounding_integer_division

echo ""
echo ""
echo "=========================="
echo "2/2: C++ tests"
echo "g++ -Wall -Werror -g3 -std=c++17 -o rounding_integer_division rounding_integer_division.cpp && ./rounding_integer_division"
echo "=========================="
echo ""
g++ -Wall -Werror -g3 -std=c++17 -o rounding_integer_division rounding_integer_division.cpp && ./rounding_integer_division

