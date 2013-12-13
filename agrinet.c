/*
  PROG: agrinet
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define MAX_N 100
#define INF 100001
typedef enum { false, true } bool;

int n;
int g[MAX_N+1][MAX_N+1];
int d[MAX_N+1];  /* shortest distance to the tree */
int s[MAX_N+1];  /* source of the shortest edge */
bool f[MAX_N+1]; /* if in the tree already */
long ans;


/*
  Minimal Spanning Tree
 */
int main()
{
    FILE *fin = fopen("agrinet.in", "r");
    FILE *fout = fopen("agrinet.out", "w");
    int i,j,k;

    fscanf(fin, "%d", &n);
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            fscanf(fin, "%d", &g[i][j]);
        }
    }

    ans = 0;
    d[1] = 0;
    f[1] = true;
    for (i = 2; i <= n; i++){
        d[i] = g[1][i];
        s[i] = 1;
        f[i] = false;
    }

    for (k = 2; k <= n; k++){
        int min = INF, index = 0;
        for (i = 1; i <= n; i++){
            if (!f[i] && d[i] < min) {
                min = d[i];
                index = i;
            }
        }

        f[index] = true;
        ans += g[index][s[index]];

        for (i = 1; i <= n; i++){
            if (!f[i] && g[index][i] < d[i]) {
                d[i] = g[index][i];
                s[i] = index;
            }
        }
    }


    fprintf(fout, "%ld\n", ans);
    fclose(fin);
    fclose(fout);
    return 0;
}
