#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "methods.c"

int main(void)
{

    int x, order;
    double start_clock, end_clock;
    number a, b, c, d;

    x = 11018;
    order = 21;
    setInt(&a, x);
    setInt(&b, 0);
    dispNumberZSLN(&a);

    start_clock = (double)clock() / CLOCKS_PER_SEC;
    puts("\narcTan1(using divide4)");
    arcTan(&a, &b, order);
    dispNumberZSLN(&b);
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    start_clock = (double)clock() / CLOCKS_PER_SEC;
    puts("\narcTan2(older)");
    arcTan2(&a, &b, order);
    dispNumberZSLN(&b);
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    printf("\nRight value: %.20lf\n", atan(1 / (double)x));
}
