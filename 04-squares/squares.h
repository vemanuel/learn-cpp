// Libraries
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <fmt/format.h>

// Classes and functions used
using std::cin;
using std::sqrt;
using std::floor;
using fmt::print;

// Count the number of squares in an NxN multiplication table.
int main(int argc, char* argv[]);

// Compute the integer square root of a number (largest integer r such that r^2 <= x)
inline int isqrt(int x);

// Is the integer x a perfect square?
inline bool is_square(int x);

// Count the number of perfect squares on the table by brute force
int count_squares_bf(int n);

// Divide an integer by all perfect square divisors
int factor_out_squares(int x);

// Count the number of perfect squares on the table using factorization
int count_squares(int n);
