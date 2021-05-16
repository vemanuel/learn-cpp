// Libraries
#include <cmath>
#include <iostream>
#include <string>
#include <boost/format.hpp>

// Classes and functions used
using std::cout;
using std::string;
using boost::format;
using std::abs;
using std::sqrt;

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
estimate calc_pi_area(int n);
int main();
