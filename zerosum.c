/*
  PROG: zerosum
  LANG: C
  ID: ranmocy1
*/
#include <stdio.h>
#include <math.h>
typedef enum { false, true } bool;
typedef enum { space, plus, minus } operator;

FILE *fin, *fout;

int N;
operator ops[10];


bool check()
{
    int i;
    long sum = 0, num = N;

    for (i = N-1; i > 0; i--){
        switch (ops[i]) {
            case space:
                if (num == 0){
                    num = i;
                } else {
                    num += i * (int)pow(10, (int)(log(num)/log(10)+1));
                }
                break;
            case plus:
                sum += num;
                num = i;
                break;
            case minus:
                sum -= num;
                num = i;
                break;
        }
    }

    sum += num;
    return sum == 0;
}


void search(int position)
{
    int i;
    if (position >= N){
        if (check()){
            for (i = 1; i < N; i++){
                fprintf(fout, "%d", i);
                switch (ops[i]) {
                    case space:
                        fprintf(fout, " ");
                        break;
                    case plus:
                        fprintf(fout, "+");
                        break;
                    case minus:
                        fprintf(fout, "-");
                        break;
                }
            }
            fprintf(fout, "%d\n", N);
        }
    } else {
        ops[position] = space;
        search(position + 1);
        ops[position] = plus;
        search(position + 1);
        ops[position] = minus;
        search(position + 1);
    }
    return;
}



/*
  3 <= N <= 9
  Bruce force
*/
int main()
{
    fin = fopen("zerosum.in", "r");
    fout = fopen("zerosum.out", "w");
    fscanf(fin, "%d", &N);

    search(1);

    fclose(fin);
    fclose(fout);
    return 0;
}
