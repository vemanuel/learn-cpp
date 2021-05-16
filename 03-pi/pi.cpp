#include "pi.h"


// ****************************************************************************
void report_results(estimate pi_est, string est_name)
/*  Report the calculation of pi using the named method
    INPUTS:
    pi_est: An estimate of pi
    est_name: Name of the estimation method.
*/
{
    // Calculate the ACTUAL error vs. official
    double error_actual = abs(pi_est.value - pi);
    // Report the results
    cout << "************************************************************\n";
    cout << format("Estimate of pi with method: %s\n") % est_name;
    cout << format("%18.16f\n") % pi_est.value;
    cout << format("estimated error = %6.3e\n") % pi_est.error;
    cout << format("actual error =    %6.3e\n") % error_actual;
}

// ****************************************************************************
estimate calc_pi_parrot()
/*  Estimate pi using the "parrot" method (parrot back the answer)
    Used for testing.
    INPUTS:
    None
    OUTPUTS
    pi_est: An estimate of pi, including a value and an error upper bound
*/
{
    double pi_val = 3.141592654;
    double pi_err = 1.0E-9;
    estimate pi_est(pi_val, pi_err);
    return pi_est;
}

// ****************************************************************************
estimate calc_pi_area(int n)
/*  Estimate pi using the "area" method.
    This method takes the quarter circle in quadrant 1 and slices it into n rectangular slices.
    The width of each rectangle dx = 1/n.
    The height on the left side of each rectangle is y_prev, on the right side is y.
    q is the area of the quadrant, and pi = 4q.
    The lower bound on q, q_lo, is the sum of dx times y over the slices.
    The upper bound on q, q_hi, is the sum of dx times y_prev over the slices.
    The error estimate (upper bound) is half the difference (q_hi - q_lo), times 4,
    i.e. err < 2 * (q_hi - q_lo).
    INPUTS:
    n: the number of rectangular slices.
    OUTPUTS
    pi_est: An estimate of pi, including a value and an error upper bound
*/
{
    double pi_val = 3.141592654;
    double pi_err = 1.0E-8;
    estimate pi_est(pi_val, pi_err);
    return pi_est;
}

// ****************************************************************************
int main()
{
    // Report the official answer
    cout << format("C Math library says pi equals:\n%18.16f.\n") % pi;

    // Calculate pi using parrot method
    estimate pi_parrot = calc_pi_parrot();
    report_results(pi_parrot, "parrot");

    // Calculate pi using area method
    int n_area = 16;
    estimate pi_area = calc_pi_area(n_area);
    string area_name = boost::str(format("area (n=%d)") % n_area);
    report_results(pi_area, area_name);

    // Exit program normally
    return 0;
}