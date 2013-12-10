/*
  PROG: concom
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define N 100
typedef enum { false, true } bool;

bool changed = true;
short E,i,j,k;
short p[N+1][N+1];       /* directly have */
short shares[N+1][N+1];  /* totally have */
bool controls[N+1][N+1]; /* whether can control */


int main()
{
    FILE *fin = fopen("concom.in", "r");
    FILE *fout = fopen("concom.out", "w");

    fscanf(fin, "%hd", &E);
    while (E--){
        fscanf(fin, "%hd %hd %hd", &i, &j, &k);
        p[i][j] = shares[i][j] = k;
    }

    while (changed){
        changed = false;
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++)
                if (shares[i][j] >= 50 && !controls[i][j]){
                    controls[i][j] = true;
                    for (k = 1; k <= N; k++)
                        if (p[j][k]) {
                            shares[i][k] += p[j][k];
                            changed = true;
                        }
                }
    }

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
            if (i != j && controls[i][j])
                fprintf(fout, "%hd %hd\n", i, j);

    return 0;
}
