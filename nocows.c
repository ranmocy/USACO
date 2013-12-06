/*
  PROG: nocows
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define MAX_K 100
#define MAX_N 200
#define MOD 9901

int n,k,ans;
short f[MAX_N+1][MAX_K+1][MAX_N+1];


short g(int i, int j, int t)
{
    if ((i<=0) || (j<=0) || (t<=0)) {return 0;}
    if ((i==1) && (j==1) && (t==1)) {
        f[i][j][t] = 1;
        return 1;
    }
    if (f[i][j][t] >= 0){return f[i][j][t];}

    long temp = 0;
    int p,q,r;
    for (p=1; p<=i; p+=2) {
        if (f[p][j][1] == 0){ continue; }
        for (q=1; q<=j-1; q++) {
            for (r=1; r<=t/p; r++) {
                temp += f[p][j][1]*g(i-r*p, q, t-r);
            }
        }
    }

    f[i][j][t] = temp % MOD;
    return f[i][j][t];
}


/*
  DP
  Table:
  f[i][j][t] indicates how many possible structures of t trees with i nodes and j height.
  Base: f[i][j][1] = 1
  Function:
  // 1<=p<=i-2, 1<=q<=j-2
  f(i,j,1) = f(p,j-1,1) * f(i-1-p,j-1,1) + sum(f(p,q,1) * f(i-1-p,j-1,1) * 2)
  // 1<=i<=n: i nodes
  // 1<=j<=k: j height
  // 2<=t<=i: t trees
  // 1<=p<=i: p nodes for one tree
  // 1<=q<=j-1: q height for rest trees
  // 1<=r<=t/p: r trees are same
  f(i,j,t) = sum(f(p,j,1)*f(i-r*p,q,t-r))
*/
int main()
{
    FILE *fin = fopen("nocows.in", "r");
    FILE *fout = fopen("nocows.out", "w");
    fscanf(fin, "%d %d", &n, &k);

    int i,j,t,p,q;
    long temp;

    for (i = 1; i <= n; i++){
        for (j = 1; j <= k; j++){
            for (t = 2; t <= n; t++){
                f[i][j][t] = -1;
            }
        }
    }

    /* one tree */
    f[1][1][1] = 1;
    for (i=1; i<=n; i+=2){
        for (j=1; j<=k; j++) {
            for (p=1; p<=i-2; p+=2) {
                if (f[p][j-1][1] == 0){ continue; }
                temp = f[i][j][1] + f[p][j-1][1]*f[i-1-p][j-1][1];
                f[i][j][1] = temp % MOD;
            }
            for (q=1; q<=j-2; q++) {
                for (p=1; p<=i-2; p++) {
                    if (f[p][j-1][1] == 0){ continue; }
                    temp = f[i][j][1] + f[p][j-1][1]*f[i-1-p][q][1]*2;
                    f[i][j][1] = temp % MOD;
                }
            }
        }
    }

    /* more trees */
    ans = 0;
    for (i=1; i<=n; i++) {
        ans += g(n,k,i);
        ans %= MOD;
    }

    fprintf(fout, "%d\n", ans % MOD);
    fclose(fin);
    fclose(fout);
    return 0;
}
