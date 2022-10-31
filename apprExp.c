#include <stdio.h>
//Adapted from https://gist.github.com/serg06/38760a4b5aceb4c6245d61c56716588c
// Iterations for exp(x) approximation. Higher = more accurate, but higher likelihood of running into inf.
#define EXP_ITERATIONS 100

// Iterations for ln(x) approximation. Higher = more accurate, but slower.
#define LN_ITERATIONS 10000

// Returned if invalid input entered.
#define ERROR_RESULT -999999999

// Super fast base^exponent (integer power) using Exponentiation by Squaring.
double powfi(double base, int exponent) {
    unsigned pos_exponent = 0;
    if(exponent < 0)
        pos_exponent = -exponent;
    else
        pos_exponent = exponent;

    double result = 1;
    while (pos_exponent) {
        if (pos_exponent & 0x1) {
            result *= base;
        }
        base *= base;
        pos_exponent >>= 1;
    }
    if(exponent>0)
        return result;
    else
        return 1/result;
}

// Factorial
double fact2(unsigned n) {
    if (n < 0 || n >= 172) return ERROR_RESULT; // error out (fact(172) = inf)

    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Approximate e^exponent calculation using Taylor series.
// e^exponent = sum_{n=0}^{inf} (exponent^n / n!)  for exponent >= 0 (The reciprocal is taken for exponent<0)
double exp2(double exponent) {
    double pos_exponent = 0;
    if (exponent > 0)
        pos_exponent = exponent;
    else
        pos_exponent = - exponent;
    double result = 0;
    for (int n = 0; n < EXP_ITERATIONS; n++) {
        result += powfi(pos_exponent, n) / fact2(n);
    }
    if (exponent > 0)
        return result;
    else
        return 1/result;
}

// Approximate ln(argument) calculation using Taylor series
// ln(argument) = 2 * sum_{n=0}^{inf} (((argument-1)/(argument+1))^(2n-1))/(2n-1)  for argument > 0
double ln2(double argument) {
    if (argument <= 0) return ERROR_RESULT; // error out

    double result = 0;
    for (int n = 1; n < LN_ITERATIONS; n++) {
        result += powfi((argument-1)/(argument+1), 2*n-1)/(2*n-1);
    }
    return 2*result;
}

// Finally, the custom pow(float x, float y) function.
// Uses the fact that pow(x,y) = exp(y*log(x))
double powff(double base, double exponent) {
    if (base <= 0) return ERROR_RESULT; // error out

    // split the calculation into two to discourage inf
    // y = y - (int)y + (int)y
    // so
    // x^y = x^((int)y) * x^(y-((int)y))

    // first calculate x^((int)y)
    int int_power = (int)exponent;
    double int_pow_result = powfi(base, int_power);

    // then calculate x^(y-((int)y))
    double remaining_power = exponent - int_power;
    double remaining_result = exp2(remaining_power*ln2(base));

    // Then multiply them together!
    return int_pow_result * remaining_result;
}
