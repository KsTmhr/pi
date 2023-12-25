#include <stdio.h>

int main(void)
{
    FILE *fp;
    FILE *fp2;
    int n, m, dgt;

    fp = fopen("pi.txt", "r");
    fp2 = fopen("right_pi.txt", "r");

    dgt = 0;
    while ((n = fgetc(fp)) != EOF)
    {
        m = fgetc(fp2);
        if (n != m)
        {
            break;
        }
        dgt++;
    }

    printf("%d桁目まで一致\n", dgt);

    fclose(fp);
    fclose(fp2);
}