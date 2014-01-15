/*
  PROG: butter
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define MAX_N 500     /* # of cows */
#define MAX_P 800     /* # of pastures */
#define MAC_C 1450    /* # of pathes */
#define INF 225*MAX_P /* 225 is direct path length limit */

int N, P, C;
int cows[MAX_P+1];
int map[MAX_P+1][MAX_P+1];


int main()
{
    FILE *fin = fopen("butter.in", "r");
    FILE *fout = fopen("butter.out", "w");

    fscanf(fin, "%d %d %d", &N, &P, &C);
    int i, j, k, t;
    for (i = 1; i <= N; i++){
        fscanf(fin, "%d", &t);
        cows[t]++;
    }
    for (i = 1; i <= P; i++)
        for (j = 1; j <= P; j++)
            if (i == j)
                map[i][j] = 0;
            else
                map[i][j] = INF;
    for (i = 1; i <= C; i++){
        fscanf(fin, "%d %d %d", &j, &k, &t);
        map[j][k] = t;
        map[k][j] = t;
    }
    fclose(fin);

    /* Floyd - to find the shortest path between all pairs */
    for (k = 1; k <= P; k++)
        for (i = 1; i <=P; i++)
            for (j = i+1; j <= P; j++)
                if (map[i][k] + map[k][j] < map[i][j])
                    map[j][i] = map[i][j] = map[i][k] + map[k][j];

    /* Enum the answer */
    int ans = 0, d = INF;
    for (k = 1; k <= P; k++){
        int t = 0;
        for (i = 1; i <= P; i++)
            t += cows[i] * map[i][k];
        if (t < d) {
            ans = k;
            d = t;
        }
    }

    fprintf(fout, "%d\n", d);
    fclose(fout);
    return 0;
}
