// Seven Eleven Logic Problem
// I bought four items at a Seven Eleven store.
// The sum of the four prices was $7.11.
// The product of the four prices was also 7.11,
// where we treat each price as a number in dollars.
// All the prices are an even number of dollars and cents, 
// e.g. $1.23 is OK, but 1.234 is not.
// What were the prices of the four items?

// Approach: let the prices of the four items in PENNIES
// be given by the variables: x, y, z, w
// Then the problem translates into two equations 
// in four unknowns:
// (Eq. 1) x + y + z + w = 711
// (Eq. 2) x * y * z * w = 7.11 x 10^8 = 711,000,000
// These equations can be solved quickly on the computer

#include <iostream>
#include <algorithm>
#include <fmt/format.h>

using std::cout;
using std::min;
using fmt::print;

int main()
{
    // The sum of x + y + z + w
    constexpr int s = 711;
    // The product of x * y * z * w
    constexpr int p = 711000000;

    // Count the number of solutions found
    int solution_count = 0;

    // Count the number of combinations tested
    int combinations_tested;

    // Iterate over guesses for x
    // int x_max = min(s, p);
    int x_max = s;
    for (int x=1; x <= x_max; ++x)
    {
        // If x is not a factor of p, it's hopeless, so give up
        if (p % x != 0)
            {continue;}

        // Iterate over guesses for y
        int y_max = s-x;
        // Start the iteration from x because we can assume w.l.o.g. that x <= y <= z
        for (int y=x; y <= y_max; ++y)
        {

            // If x*y is not a factor of p, it's hopeless, so give up
            if (p % (x*y) != 0)
                {continue;}

            // Iterate over guesses for z
            int z_max = s-(x+y);
            // Start the iteration from x because we can assume w.l.o.g. that x <= y <= z
            for (int z=y; z<= z_max; ++z)
            {
                // Now that we've guessed x, y, and z we can solve for w using the sum condition
                int w = s - (x+y+z);
                ++combinations_tested;
                // Check whether the product is correct AND it's sorted properly
                int p4 = x*y*z*w;
                if (p4 == p && z <= w)
                {
                    // Convert integer prices in pennies to double prices in dollars
                    double xd = x / 100.0;
                    double yd = y / 100.0;
                    double zd = z / 100.0;
                    double wd = w / 100.0;

                    // Report the four prices
                    print("Found a solution!\n");
                    print("x = {:3.2f}\n", xd);
                    print("y = {:3.2f}\n", yd);
                    print("z = {:3.2f}\n", zd);
                    print("w = {:3.2f}\n", wd);

                    // Increment the solution counter
                    ++solution_count;
                }
            }

        }
    }
    // Report the results
    print("Explored {:d} possible combinations for s={:d}, p={:d}.\n", combinations_tested, s, p);
    print("Found a total of {:d} distinct solutions.\n", solution_count);
    // Indicate normal program exit; 
    return 0;
}
