/*
  PROG: fact4
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;

int N;


int main()
{
    FILE *fin = fopen("fact4.in", "r");
    FILE *fout = fopen("fact4.out", "w");

    fscanf(fin, "%d", &N);

    int i, mul, five = 0, two = 0, ans = 1;
    for (i = 2; i <= N; i++){
        mul = i;
        while (mul % 5 == 0){mul /= 5; five++;}
        while (mul % 2 == 0){mul /= 2; two++;}
        ans = (ans * mul) % 10;
    }

    while (five > two) {ans = (ans * 5) % 10; five--;}
    while (two > five) {ans = (ans * 2) % 10; two--;}

    fprintf(fout, "%d\n", ans);
    fclose(fin);
    fclose(fout);
    return 0;
}
