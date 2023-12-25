#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "methods.c"

int main(void)
{
    int x, order;
    number a, b, c, d;
    srand(time(NULL));
    double start_clock, end_clock;

    setRnd(&a, 5);
    setRnd(&b, 2);
    // setInt(&a, 76028);
    // setInt(&b, -69);
    // setIntFromString(&a, "74763856");
    // setIntFromString(&b, "3");
    setInt(&c, 0);
    setInt(&d, 0);

    start_clock = (double)clock() / CLOCKS_PER_SEC;
    dispNumberZSLN(&a);
    dispNumberZSLN(&b);
    divide3(&a, &b, &c, &d);
    dispNumberZSLN(&c);
    dispNumberZSLN(&d);
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    start_clock = (double)clock() / CLOCKS_PER_SEC;
    dispNumberZSLN(&a);
    dispNumberZSLN(&b);
    divide4(&a, &b, &c, &d);
    dispNumberZSLN(&c);
    dispNumberZSLN(&d);
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);
}
