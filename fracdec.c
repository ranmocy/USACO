/*
  PROG: fracdec
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <math.h>
#define max_n 100000

int a,b,i,r;
int rem[max_n+1]; /* the position reminder i appears */
int div;          /* divide part of answer */
int dec[max_n+1]; /* decimal of answer */
int begin,end;    /* loop begin and end positions */


int main()
{
    FILE *fin = fopen("fracdec.in", "r");
    FILE *fout = fopen("fracdec.out", "w");
    fscanf(fin, "%d %d", &a, &b);
    div = a / b;
    r = a % b;

    while (1){
        if (r == 0) break;  /* if we finished */
        if (rem[r] > 0){ begin = rem[r]; break; }
        rem[r] = ++end;
        dec[end] = r * 10 / b;
        r = r * 10 % b;
    }

    fprintf(fout, "%d.", div);
    int linebreaker = 1, temp = div;
    do { linebreaker++; temp /= 10;} while (temp > 0);

    for (i = 1; i <= end; i++){
        if (linebreaker % 76 == 0) fprintf(fout, "\n");
        if (begin == i) {linebreaker++; fprintf(fout, "(");}
        fprintf(fout, "%d", dec[i]);
        linebreaker++;
    }
    if (end == 0) fprintf(fout, "0");
    if (begin != 0) fprintf(fout, ")");
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}
