/*
  PROG: stamps
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define MAX_N 50
#define INF 201

int K,N;
int v[MAX_N];  /* value of N stamps */
int f[2000000];

/*
  f(i) indicates the minimal amount of stamps to be value i;
  f(i) = f(i - v[j]) + 1 // i >= v[j], f(i - v[j]) + 1 <= K
 */
int main()
{
    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");

    fscanf(fin, "%d %d", &K, &N);
    int i,j;
    for (i = 0; i < N; i++) fscanf(fin, "%d", &v[i]);

    i = 0;
    while (true) {
        f[++i] = INF;
        for (j = 0; j < N; j++)
            if ((i >= v[j]) && (f[i-v[j]]+1 <= K) && (f[i] > f[i-v[j]]+1))
                f[i] = f[i-v[j]] + 1;
        if (f[i] == INF) {
            fprintf(fout, "%d\n", i-1);
            break;
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
