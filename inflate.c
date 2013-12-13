/*
  PROG: inflate
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define MAX_N 10000

int m,n;
int s[MAX_N+1];  /* scores */
int t[MAX_N+1];  /* times */
long f[MAX_N+1]; /* the max score */


/*
  f(i) indicates the max score with i time
  f(0) = 0
  f(i) = max(f(i - t[j]) + s[j])
 */
int main()
{
    FILE *fin = fopen("inflate.in", "r");
    FILE *fout = fopen("inflate.out", "w");
    int i,j;

    fscanf(fin, "%d %d", &m, &n);
    for (i = 1; i <= n; i++){
        fscanf(fin, "%d %d", &s[i], &t[i]);
    }

    long ans = 0;
    for (i = 1; i <= m; i++){
        for (j = 1; j <= n; j++){
            if ((i >= t[j]) && (f[i] < f[i - t[j]] + s[j])){
                f[i] = f[i - t[j]] + s[j];
            }
        }
        if (ans < f[i]) ans = f[i];
    }

    fprintf(fout, "%ld\n", ans);
    fclose(fin);
    fclose(fout);
    return 0;
}
