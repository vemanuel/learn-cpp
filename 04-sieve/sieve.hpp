// Libraries
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <fmt/format.h>

// Names used from libraries
using std::vector;
using std::sqrt;
using std::string;
using std::cout;
using std::ofstream;
using std::atoi;
using fmt::format, fmt::print;

// Global variables
// Table indicating whether a number is "composite" (not prime)
vector<bool> is_comp;
// Handle to write to the output file
std::ofstream fs;

// Function prototypes
int get_next_prime(int n);
int sieve_out(int p);
void write_prime(int p);
void write_big_primes(int n_max);
