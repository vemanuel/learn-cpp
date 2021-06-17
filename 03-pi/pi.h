// Libraries
#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <cmath>

// Classes and functions used
using std::cout;
using std::string;
using boost::format;
using std::abs;
using std::sqrt;
using std::pow;

// Numerical constants
constexpr double pi = M_PI;

// Data structures
struct estimate {
    double value;
    double error;
};

// Function declarations
void report_results(estimate pi_est, string est_name);
estimate calc_pi_parrot();
estimate calc_pi_area(long n);
estimate calc_pi_archimedes(int k);
// estimate calc_pi_midpoint(int n);
int main();
