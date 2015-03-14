#include <iostream>
#include <mpfr.h>

#define ITERATIONS 1100
#define PRECISION 1100
#define NUMERIC_SYSTEM 10

void print_digit(mpfr_t num, int digit)
{
    char pi_str[digit + 1];
    mpfr_exp_t exponent; //not needed for program to work, but required by function
    mpfr_get_str(pi_str, &exponent, NUMERIC_SYSTEM, digit + 1, num, MPFR_RNDD);
    std::cout << pi_str[digit] << std::endl;
}

void calculate_pi(mpfr_t *src)
{
    mpfr_set_d(*src, 0.0, MPFR_RNDD);

    mpfr_t supporter;
    mpfr_init_set_d(supporter, 0.0, MPFR_RNDD);
    mpfr_set_prec(supporter, PRECISION);

    mpfr_t current;
    mpfr_init(current);
    mpfr_set_prec(current, PRECISION);

    for(double n = 1; n < ITERATIONS; ++n)
    {
        mpfr_set_d(current, 0.0, MPFR_RNDD);

        mpfr_set_d(current, n, MPFR_RNDD);

        mpfr_ui_pow_ui(supporter, 2, n, MPFR_RNDD);
        mpfr_mul(current, current, supporter, MPFR_RNDD);

        mpfr_fac_ui(supporter, n, MPFR_RNDD);
        mpfr_pow_ui(supporter, supporter, 2, MPFR_RNDD);
        mpfr_mul(current, current, supporter, MPFR_RNDD);

        mpfr_fac_ui(supporter, 2 * n, MPFR_RNDD);
        mpfr_div(current, current, supporter, MPFR_RNDD);

        mpfr_add(*src, *src, current, MPFR_RNDD);
    }

    mpfr_clear(supporter);
    mpfr_clear(current);

    mpfr_sub_d(*src, *src, 3, MPFR_RNDD);
}

int main()
{
    mpfr_t pi;
    mpfr_init_set_d(pi, 0.0, MPFR_RNDD);
    mpfr_set_prec(pi, PRECISION);

    calculate_pi(&pi);

    int n;
    std::cout << "Which digit do you want? Validity of numbers not guaranteed after 315." << std::endl;
    std::cin >> n;

    print_digit(pi, n);
    mpfr_clear(pi);

    return 0;
}
