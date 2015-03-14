#include <iostream>
#include <mpfr.h>

#define ITERATIONS 1100
#define PRECISION 1100

using namespace std;

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

    mpfr_sub_d(*src, *src, 3, MPFR_RNDD);
}

int main()
{
    mpfr_t pi;
    mpfr_init_set_d(pi, 0.0, MPFR_RNDD);
    mpfr_set_prec(pi, PRECISION);

    calculate_pi(&pi);

    mpfr_out_str(stdout, 10, 162, pi, MPFR_RNDD);
    cout << endl;
    cout << endl;
    mpfr_out_str(stdout, 10, 272, pi, MPFR_RNDD);
    cout << endl;
    cout << endl;
    mpfr_out_str(stdout, 10, 315, pi, MPFR_RNDD);
    cout << endl;
    cout << endl;
    mpfr_clear(pi);

    return 0;
}
