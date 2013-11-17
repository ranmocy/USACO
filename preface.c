/*
  PROG: preface
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>

int n;
int i,v,x,l,c,d,m = 0;


void update(int n)
{
  int t=0;

  m += n / 1000;
  n %= 1000;

  if (n / 100 == 9){
    m++;
    c++;
    n -= 900;
  }

  d += n / 500;
  n %= 500;

  t = n / 100;
  if (t == 4){
    c++;
    d++;
  } else {
    c += t;
  }
  n %= 100;

  if (n / 10 == 9){
    c++;
    x++;
    n -= 90;
  }

  l += n / 50;
  n %= 50;

  t = n / 10;
  if (t == 4){
    x++;
    l++;
  } else {
    x += t;
  }
  n %= 10;

  if (n == 9){
    i++;
    x++;
    n -= 9;
  }

  v += n / 5;
  n %= 5;

  if (n == 4){
    v++;
    i++;
  } else {
    i += n;
  }

  return;
}


/*
  1<=n<=3500, brute force.
  The tricky part is the 4x10^n and 9x10^n.
  Take them respectively.
 */
int main()
{
  FILE *fin = fopen("preface.in", "r");
  FILE *fout = fopen("preface.out", "w");

  fscanf(fin, "%d", &n);

  int t;
  for (t=1; t<=n; t++){
    update(t);
  }

  if (i != 0) fprintf(fout, "I %d\n", i);
  if (v != 0) fprintf(fout, "V %d\n", v);
  if (x != 0) fprintf(fout, "X %d\n", x);
  if (l != 0) fprintf(fout, "L %d\n", l);
  if (c != 0) fprintf(fout, "C %d\n", c);
  if (d != 0) fprintf(fout, "D %d\n", d);
  if (m != 0) fprintf(fout, "M %d\n", m);

  fclose(fin);
  fclose(fout);
  return 0;
}
