/*
  PROG: concom
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define N 100

int E;                  /* edges in graph */
int shares[N+1][N+1];   /* totally have */
bool controls[N+1][N+1]; /* whether can controls */


/* search how many shares of j which i can controls */
void control(int i, int j)
{
    if (controls[i][j]) return;
    controls[i][j] = true;

    int k;
    for (k = 1; k <= N; k++){
        /* add shares of j to i */
        shares[i][k] += shares[j][k];
        /* control k if i chould */
        if (shares[i][k] > 50) control(i, k);
    }

    return;
}


int main()
{
    FILE *fin = fopen("concom.in", "r");
    FILE *fout = fopen("concom.out", "w");

    int i,j,k,t,l;
    for (i = 1; i <= N; i++) controls[i][i] = true;

    fscanf(fin, "%d", &E);
    for (l = 1; l <= E; l++){
        fscanf(fin, "%d %d %d", &i, &j, &t);
        /* add shares p[i][j] to k if k controlss i */
        for (k = 1; k <= N; k++){
            if (controls[k][i]) shares[k][j] += t;
        }
        /* update controls */
        for (k = 1; k <= N; k++){
            if (shares[k][j] > 50) control(k, j);
        }
    }

    for (i = 1; i <= N; i++){
        for (j = 1; j <= N; j++){
            if ((i != j) && (controls[i][j])){
                fprintf(fout, "%d %d\n", i, j);
            }
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
