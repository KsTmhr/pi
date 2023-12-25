#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "methods.c"

int main(void)
{
    number a, b, c, d;
    int x, y, z, w, m, n, i, r;
    double start_clock, end_clock;
    srand(time(NULL));

    start_clock = (double)clock() / CLOCKS_PER_SEC;
    for (i = 0; i < 100; i++)
    {
#if 0
        x = rand();
        y = rand();

#if 1
        if (rand() % 10 < 5)
            x *= -1;

        if (rand() % 10 < 5)
            y *= -1;
#endif

        setInt(&a, x);
        setInt(&b, y);
#endif

#if 1
        setRnd(&a, 1000);
        setRnd(&b, 5);
#endif

        if (y == 0)
        {
            // puts("divide by 0");
            continue;
        }
        else
        {
            z = x / y;
            w = x % y;
        }
        r = divide4(&a, &b, &c, &d);
        // r = multiple(&a, &b, &c);

        getInt(&c, &m);
        getInt(&d, &n);
#if 0
        printf("x:  %d, y:  %d, z:  %d, w:  %d, r:  %d\n", x, y, z, w, r);
        printf("a: ");
        dispNumberZeroSuppress(&a);
        printf(", b: ");
        dispNumberZeroSuppress(&b);
        printf(", c: ");
        dispNumberZeroSuppress(&c);
        printf(", d: ");
        dispNumberZeroSuppress(&d);
        puts("");
#endif
#if 0
        if (r != -1)
        {
            if (z != m || w != n)
            {
                puts("error!");
                printf("x:  %d, y:  %d, z:  %d, n:  %d, r:  %d\n", x, y, z, r);
                printf("a: ");
                dispNumberZeroSuppress(&a);
                printf(", b: ");
                dispNumberZeroSuppress(&b);
                printf(", c: ");
                dispNumberZeroSuppress(&c);
                printf(", d: ");
                dispNumberZeroSuppress(&d);
                puts("");
            }
        }

#endif
    }
    end_clock = (double)clock() / CLOCKS_PER_SEC;

    puts("Finish!");
    printf("time: %f\n", end_clock - start_clock);
}
