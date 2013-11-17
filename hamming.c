/*
  PROG: hamming
  LANG: C
  ID: ranmocy1
*/

typedef enum { false, true } bool;
#include <stdio.h>

int n, b, d;
int res[64] = { 0 };  /* n=64 */


int distance(int m, int n){
  int i, d = 0;
  for (i=0; i<b; i++){
    if ((m % 2) != (n % 2)){
      d++;
    }
    m >>= 1;
    n >>= 1;
  }
  return d;
}


bool check(int i, int current)
{
  int j;
  for (j=0; j<i; j++){
    if (distance(res[j], current) < d){
      return false;
    }
  }
  return true;
}


/*
  2^b*n*b=2^8*64*8=131072
  enumerate everything.
 */
int main()
{
  FILE *fin = fopen("hamming.in", "r");
  FILE *fout = fopen("hamming.out", "w");

  fscanf(fin, "%d %d %d", &n, &b, &d);

  res[0] = 0;
  fprintf(fout, "0");
  int current = 1;
  int i;
  for (i=1; i<n; i++){
    while (check(i, current) == false){ current++; }
    res[i] = current;
    if (i % 10 != 0){ fprintf(fout, " "); }
    fprintf(fout, "%d", res[i]);
    /* 10 numbers a line */
    if (i % 10 == 9){ fprintf(fout, "\n"); }
  }

  if (n % 10 != 0){ fprintf(fout, "\n"); }
  fclose(fin);
  fclose(fout);
  return 0;
}
