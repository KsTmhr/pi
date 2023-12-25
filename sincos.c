#include <stdio.h>
#include <math.h>

double doubleSin(double);
double doubleCos(double);
int intSin(double);
int intCos(double);

int main(void)
{
    double mySin, myCos, theta;
    int myIntSin, myIntCos;

    theta = 1.0;
    mySin = doubleSin(theta);
    myCos = doubleCos(theta);
    myIntSin = intSin(theta);
    myIntCos = intCos(theta);
    printf("mySin  : %.10lf\nmathSin: %.10lf\n", mySin, sin(theta));
    printf("myIntSin  : %d\nmathIntSin: %.10lf\n", myIntSin, sin(theta) * 1.e6);
    printf("myCos  : %.10lf\nmathCos: %.10lf\n", myCos, cos(theta));
    printf("myIntCos  : %d\nmathIntCos: %.10lf\n", myIntCos, cos(theta) * 1.e6);
}

double doubleSin(double theta)
{
    int n;
    double e, s, N;

    e = 1.e-10;

    s = 0;
    n = 1;
    N = theta;
    while (fabs(N) > e)
    {
        s += N;
        n += 2;
        N *= theta * theta / (n - 1) / n * (-1);
    }

    return s;
}

double doubleCos(double theta)
{
    int n;
    double e, c, N;

    e = 1.e-10;

    c = 0;
    n = 0;
    N = 1;
    while (fabs(N) > e)
    {
        c += N;
        n += 2;
        N *= theta * theta / (n - 1) / n * (-1);
    }

    return c;
}

int intSin(double theta)
{
    int n;
    int s, N;

    s = 0;
    n = 1;
    N = theta * 1.e6;
    while (fabs(N) > 0)
    {
        s += N;
        n += 2;
        N *= theta * theta / (n - 1) / n * (-1);
    }

    return s;
}

int intCos(double theta)
{
    int n;
    int c, N;

    c = 0;
    n = 0;
    N = 1 * 1.e6;
    while (fabs(N) > 0)
    {
        c += N;
        n += 2;
        N *= theta * theta / (n - 1) / n * (-1);
    }

    return c;
}