#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "methods.c"

int main(void)
{
    int order, i;
    double start_clock, end_clock;
    number arctan, term, tmp, pi;
    FILE *fp;

    order = 1005;

    start_clock = (double)clock() / CLOCKS_PER_SEC;

    clearByZero(&pi);

    // 88 * atan(1/28)
    setInt(&tmp, 28);
    arcTan(&tmp, &arctan, order);
    setInt(&tmp, 88);
    multiple(&tmp, &arctan, &term);
    add(&pi, &term, &pi);

    printf("term1 complete\n");
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    // 8 * atan(1/443)
    setInt(&tmp, 443);
    arcTan(&tmp, &arctan, order);
    setInt(&tmp, 8);
    multiple(&tmp, &arctan, &term);
    add(&pi, &term, &pi);

    printf("term2 complete\n");
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    // -20 * atan(1/1393)
    setInt(&tmp, 1393);
    arcTan(&tmp, &arctan, order);
    setInt(&tmp, -20);
    multiple(&tmp, &arctan, &term);
    add(&pi, &term, &pi);

    printf("term3 complete\n");
    end_clock = (double)clock() / CLOCKS_PER_SEC;
    printf("time: %f\n", end_clock - start_clock);

    // -40 * atan(1/11018)
    setInt(&tmp, 11018);
    arcTan(&tmp, &arctan, order);
    setInt(&tmp, -40);
    multiple(&tmp, &arctan, &term);
    add(&pi, &term, &pi);

    printf("term4 complete\n");
    end_clock = (double)clock() / CLOCKS_PER_SEC;

    dispNumber(&pi);
    printf("digit: %d\n", getDigit(&pi));
    printf("time: %f\n", end_clock - start_clock);

    fp = fopen("pi.txt", "w");

    for (i = getDigit(&pi) - 1; i >= 0; i--)
    {
        fputc('0' + pi.n[i], fp);
    }

    fclose(fp);

    return 0;
}
