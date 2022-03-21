#include <iostream>
#include <fmt/format.h>
using fmt::print;

// **************************************************************************************************
bool is_ok(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    // Flag indicating whether these 9 numbers satisfy the puzzle condition
    bool is_ok = true;
    // The four special squares should add up to 17 for the St. Patrick's Day Puzzle
    constexpr int total = 17;
    // Check that each square is OK
    is_ok = ((a+b+d+e) == total);
    is_ok &= ((b+c+e+f) == total);
    is_ok &= ((d+e+g+h) == total);
    is_ok &= ((e+f+h+i) == total);

    return is_ok;
}

// **************************************************************************************************
void print_grid(int a, int b, int c, int d, int e, int f, int g, int h, int i, int sol)
{
    print("****************************************\n");
    print("Solution {:d}:\n", sol);
    print("{:d}{:d}{:d}\n", a, b, c);
    print("{:d}{:d}{:d}\n", d, e, f);
    print("{:d}{:d}{:d}\n", g, h, i);
}

// **************************************************************************************************
int main(int argc, char *argv[])
{
    // 9 number on the puzzle grid
    int a, b, c, d, e, f, g, h, i;
    // These three entries are given with the puzzle
    c = 9;
    e = 2;
    g = 4;

    // Count candidates evaluated and solutions found
    int cand = 0;
    int sols = 0;

    // Iterate through non-overlapping assignments
    for (int a=1; a<10; ++a) {        
        if ((a==c) || (a==e) || (a==g)) {continue;}
        for (int b=1; b<10; ++b) {
            if ((b==a) || (b==c) || (b==e) || (b==g)) {continue;}
            for (int d=1; d<10; ++d) {
                if ((d==a) || (d==b) || (d==c) || (d==e) || (d==g)) {continue;}
                for (int f=1; f<10; ++f) {
                    if ((f==a) || (f==b) || (f==c) || (f==d) || (f==e) || (f==g)) {continue;}
                    for (int h=1; h<10;++h) {
                        if ((h==a) || (h==b) || (h==c) || (h==d) || (h==e) || (h==f) || (h==g)) {continue;}
                        for (int i=1; i<10;++i) {
                            if ((i==a) || (i==b) || (i==c) || (i==d) || (i==e) || (i==f) || (i==g) || (i==h)) {continue;}
                            // If we get here, then a, b, c, d, e, f, g, h are all distinct (different)
                            ++cand;
                            // Now check if these 9 grid entries satisfy the puzzle condition
                            if (is_ok(a, b, c, d, e, f, g, h, i)) 
                            {
                                // If this is a good solution, increment the solutions counter and print it
                                ++sols;
                                print_grid(a, b, c, d, e, f, g, h, i, sols);
                            }
                        }
                    }
                }
            }
        }
    }
    // Report number of solutions found and exit
    print("****************************************\n");
    print("Evaluated {:d} candidate grids.\n", cand);
    print("Found {:d} solutions.\n", sols);
    return 0;
}

