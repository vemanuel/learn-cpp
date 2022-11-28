// squares.cpp
// Count the number of perfect squares in an NxN multiplication table
// Inspired by a question asked by Victor on the bus to Fenway park
// to see his first baseball game.
//
// Michael S. Emanuel
// 2021-09-19

#include "squares.h"

// ************************************************************************************************
inline int isqrt(int x)
{
    // Convert x to a double and take its square root
    double x_dbl = static_cast<double>(x);
    double r_dbl = sqrt(x_dbl);
    // Take the floor function of the square root and convert back to an integer
    return int(floor(r_dbl));
}

// ************************************************************************************************
inline bool is_square(int x)
{
    int r = isqrt(x);
    return (r*r == x);
}

// ************************************************************************************************
int count_squares_bf(int n)
{
    // The number of squares found
    int squares {0};
    // Iterate over the rows of the multiplication table
    for (int i=1; i <= n; ++i)
    {
        // The entry on the table
        int x=i;
        // Iterate over the rows of the multiplication table
        for (int j=1; j <= n; ++j)
        {
            // Is x a perfect square? If so increment squares counter.
            if (is_square(x))
                {++squares;}
            // Update the entry x of the table
            x += i;
        }
    }
    return squares;
}

// ************************************************************************************************
int factor_out_squares(int x)
{
    // First get rid of powers of 2
    int r2 = 4;
    while (x % r2 == 0)
        {x /= r2;}

    // Test odd divisors of x up to its integer square root
    for (int r=3; r <= isqrt(x);  r+= 2)
    {
        r2 = r*r;
        while (x % r2 == 0)
            {x /= r2;}
    }
    return x;
}

// ************************************************************************************************
int count_squares(int n)
{
    // The number of squares found
    int squares {0};
    // Iterate over the rows of the multiplication table
    for (int i=1; i <= n; ++i)
    {
        // Factor out the squares from i
        int k = factor_out_squares(i);
        // Add the number of squares in row i
        squares += isqrt(n / k);
    }
    return squares;
}

// ************************************************************************************************
int main(int argc, char* argv[])
{
    // The size of multiplication table n
    int n;
    // Process command line arguments
    if (argc == 1)
    {
        print("Enter the size of the multiplication table:\n");
        cin >> n;
        print("Counting perfect squares in a multiplication table of size {:d}.\n", n);
    }
    else if (argc == 2)
    {
        std::string arg = argv[1];
        n = std::stoi(arg);
    }
    else
    {
        print("Bad input! usage is either 0 or 1 command line arguments.\n");
        print("\"squares.x\" - interactively enter n at the command line.\n");
        print("\"squares.x n\" - count squares in nxn multiplication table.\n");
    }

    // Set up timers
    std::chrono::time_point<std::chrono::system_clock> t0, t1;
    std::chrono::microseconds dt;

    // Count squares using factorization
    t0 = std::chrono::system_clock::now(); 
    int squares = count_squares(n);
    t1 = std::chrono::system_clock::now();
    dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    print("Found {:d} squares by factorization method. Elapsed time {:d} microseconds.\n", squares, dt.count());

    // Count squares using brute force if n is small enough
    if (n <= 10000)
    {
        t0 = std::chrono::system_clock::now(); 
        int squares_bf = count_squares_bf(n);
        t1 = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        print("Found {:d} squares by brute force. Elapsed time {:d} microseconds.\n", squares_bf, dt.count());
    }
}
