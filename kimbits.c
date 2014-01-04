/*
  PROG: kimbits
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>

/* 1<=N<=31, 1<=L<=N, 1<=I<=sizeof(S) */
int N, L;
unsigned long I, f[32][32];

/*
  f(i,j) indicates the size of S with length i and no more j's 1
  f(i,0) = 1; f(0,j) = 1;
  f(i,j) = f(i-1,j) + f(i-1,j-1) // pick 1 or not pick 1, that's a problem
 */
int main()
{
    FILE *fin = fopen("kimbits.in", "r");
    FILE *fout = fopen("kimbits.out", "w");

    fscanf(fin, "%d %d %lu", &N, &L, &I);

    long i,j;
    for (j = 0; j <= L; j++) f[0][j] = 1;
    for (i = 1; i <= N; i++) {
        f[i][0] = 1;
        for (j = 1; j <= L; j++)
            f[i][j] = f[i-1][j] + f[i-1][j-1];
    }

    do {                     /* Binary search? Similar */
        if (f[N-1][L] >= I){  /* Ith is inside of 0xxx */
            fprintf(fout, "0");
        } else {              /* Ith is inside of 1xxx */
            fprintf(fout, "1");
            I -= f[N-1][L--];  /* one '1' less */
        }
    } while (--N > 0);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}
