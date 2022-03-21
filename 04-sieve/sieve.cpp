#include "sieve.hpp"

// **************************************************************************************************
int main(int argc, char *argv[])
{
    // The upper bound of the prime search; first command line argument, defaults to 100 if missing.
    int N = 100;
    // Parse first command line argument; this is the upper bound N.
    if (argc > 1)
    {
        N = atoi(argv[1]);
    }
    print("Sieving primes up to {:d}.\n", N);

    // Open output file
    string fname = format("primes_{:d}.txt", N);
    fs.open(fname);

    // Allocate vector of N bools and set 0 and 1 to be composite
    is_comp = vector<bool>(N, false);
    is_comp[0] = true;
    is_comp[1] = true;

    // Calculate largest divisor that must be tested.
    // Key idea is that we need only check up to the square root of N.
    double N_dbl = static_cast<double>(N);
    int n_max = static_cast<int>(sqrt(N_dbl));
    print("Checking trial divisors up to {:d}.\n", n_max);

    // Counter for the number of sieving steps
    long steps = 0;

    // Main loop of program
    int n=1;
    while (n <= n_max)
    {
        int p = get_next_prime(n);
        write_prime(p);
        steps += sieve_out(p);
        n=p+1;
    }

    // Status message with number of steps
    print("Completed prime sieving in {:d} steps.\n", steps);

    // Write out the big primes (larger than n_max)
    write_big_primes(n_max);
    
    // Close output file
    fs.close();

    return 0;
}

// **************************************************************************************************
// Search for the first prime number >= n using the table is_comp.
// INPUTS:
//      n: The number where we start the search for primes
// Example: is_comp = [1, 1, 0, 0, 0, 0, 0, 0, 0, 0] (after initialization for N=10)
// get_next_prime(1) returns 2
int get_next_prime(int n)
{
    for (int i=n; i<is_comp.size(); ++i)
    {
        if (!is_comp[i]) {return i;}
    }
    // If we get here, there was a logic error
    string msg = format("Runtime error! get_next_prime({:d}) found no primes. N={:d}.\n", n, is_comp.size());
    throw std::runtime_error(msg);
}

// **************************************************************************************************
int sieve_out(int p)
// Sieve out the composite multiples of a prime number p.
// INPUTS:
//      p: The prime number whose multiples we are sieving out, e.g. 2
// Example: after initialization for N=10,
// is_comp = [1, 1, 0, 0, 0, 0, 0, 0, 0, 0]
// After calling sieve_out(2), 
// is_comp = [1, 1, 0, 0, 1, 0, 1, 0, 1, 0]
// The composites 4, 6, 8 have been sieved out
{
    for (int n=2*p; n<is_comp.size(); n+=p)
    {
        if (!is_comp[n]) {is_comp[n] = true;}
    }
    // Return the number of steps taken by this loop
    return is_comp.size() / p - 1;
}

// **************************************************************************************************
void write_prime(int p)
// Write one prime out to the file with a status update to the console.
{
    std::string row = format("{:d}\n", p);
    cout << row;
    fs << row;
}

// **************************************************************************************************
void write_big_primes(int n_max)
// Write out the big primes (larger than n_max) to the file only.
{
    print("Completed sieving process.  Writing out large primes...\n");
    int p = get_next_prime(n_max);
    for (int n=p+1; n<is_comp.size(); ++n)
    {
        if (!is_comp[n]) {fs << format("{:d}\n", n);}
    }
}
