/*
  PROG: subset
  LANG: C
  ID: ranmocy1
*/
typedef enum { false, true } bool;
#include <stdio.h>
#define MAX_N 39

int n,h,p,q;
long long f[MAX_N+1][MAX_N*(MAX_N+1)/2+1] = {{0}};


/*
  1<=n<=39
  f[i][j] indicats how many ways with first i numbers to sum as j
  f[i][j] = f[i-1][j] + f[i-1][j-i]
  f[0][0] = 1
*/
int main()
{
  FILE *fin = fopen("subset.in", "r");
  FILE *fout = fopen("subset.out", "w");
  fscanf(fin, "%d", &n);

  if ((n*(n+1)) % 4 != 0){
    fprintf(fout, "0\n");
    goto OUT;
  }

  h = n*(n+1)/4;
  int i,j;
  f[0][0] = 1;

  for (i=1; i<=n; i++){
    for (j=0; j<=h; j++){
      f[i][j] += f[i-1][j];
      if (i<=j){
        f[i][j] += f[i-1][j-i];
      }
    }
  }

  fprintf(fout, "%lld\n", f[n][h]/2);

OUT:
  fclose(fin);
  fclose(fout);
  return 0;
}
