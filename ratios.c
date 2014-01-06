/*
  PROG: ratios
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define N 4
#define MAX_N 100

short a[N], b[N], c[N];

int main()
{
    FILE *fin = fopen("ratios.in", "r");
    FILE *fout = fopen("ratios.out", "w");

    short i, j, k, l;
    for (i = 0; i < N; i++)
        fscanf(fin, "%hd %hd %hd", &a[i], &b[i], &c[i]);
    fclose(fin);

    for (l = 1; l < MAX_N; l++){
        for (i = 0; i < MAX_N; i++){
            for (j = 0; j < MAX_N; j++){
                for (k = 0; k < MAX_N; k++){
                    if ((i * a[1] + j * a[2] + k * a[3] == l * a[0]) &&
                        (i * b[1] + j * b[2] + k * b[3] == l * b[0]) &&
                        (i * c[1] + j * c[2] + k * c[3] == l * c[0])){
                        fprintf(fout, "%hd %hd %hd %hd\n", i, j, k, l);
                        fclose(fout);
                        return 0;
                    }
                }
            }
        }
    }

    fprintf(fout, "NONE\n");
    fclose(fout);
    return 0;
}
