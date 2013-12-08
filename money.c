/*
  PROG: money
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;

FILE *fin, *fout;
int V, N;
int v[26];
long long f[10001][26];
long long ans;


/*
  DP
  f[i][j] indicates how many ways can generate i with jth first coins
  f[i<=0] = 0;
  f[0][j] = 1;
  f[i][j] = f[i-v[j]][j-1] + f[i][j-1];
 */
int main()
{
    fin = fopen("money.in", "r");
    fout = fopen("money.out", "w");

    int i, j, k;
    fscanf(fin, "%d %d", &V, &N);
    for (i = 1; i <= V; i++){
        fscanf(fin, "%d", &v[i]);
    }


    for (j = 0; j <= V; j++) f[0][j] = 1;

    for (j = 1; j <= V; j++){
        for (i = 1; i <= N; i++){
            for (k = 0; k <= i/v[j]; k++){
                f[i][j] += f[i-k*v[j]][j-1];
            }
        }
    }

    fprintf(fout, "%lld\n", f[N][V]);

    fclose(fin);
    fclose(fout);
    return 0;
}
