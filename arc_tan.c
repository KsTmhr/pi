#include <stdio.h>
#include <math.h>

double doubletan(double);
double doubletan2(double);

int main(void)
{
    double arctan, x, y;

    x = 9.07605736068252e-5;
    y = 11018;
    arctan = doubletan(x);
    printf("arctan  : %.20lf\nmathTan : %.20lf\n", arctan, atan(1 / y));
}

double doubletan(double x)
{
    int n, cnt, sign;
    double e, s, N, y;

    e = 1.e-20;

    s = 0;
    n = 1;
    N = x;
    y = N;
    sign = 1;
    cnt = 0;
    while (fabs(y) > e)
    {
        s += y;
        n += 2;
        N *= x * x;
        sign *= -1;
        y = N / n * sign;
        printf("%.20lf\n", y);
        cnt++;
    }
    return s;
}

double doubletan2(double x)
{
    int i, order, sign;
    double n, N, xp2, tmp, bunbo, bunsi;

    bunbo = x;

    // 1 * 10^order
    bunsi = 1.0;

    // xp2 = x^2
    xp2 = x * x;

    N = -1;
    for (i = 3; i < 100; i += 2)
    {
        bunsi *= i * xp2;
        bunsi += N;

        N *= i * -1;
        bunbo *= xp2;

        // printf("bunsi: %lf, bunbo: %lf, N: %lf\n", bunsi, bunbo, N);
    }

    bunbo *= fabs(N);
    printf("bunsi: %lf, bunbo: %lf, N: %lf\n", bunsi, bunbo, N);
    return bunsi / bunbo;
}
