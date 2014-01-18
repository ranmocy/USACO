/*
  PROG: fence
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
typedef enum { false, true } bool;
#define N 500
#define MAX_F N*N/2

FILE *fin, *fout;
int map[N+1][N+1], path[MAX_F], F;


void dfs(int current, int depth)
{
    printf("%d:%d\n", depth, current);
    int i;
    for (i = 1; i <= N; i++)
        while (map[current][i] > 0) {
            map[current][i]--; map[i][current]--;
            dfs(i, depth+1);
        }
    path[++path[0]] = current;
}


int main()
{
    {
        fin = fopen("fence.in", "r");
        int i, j, k;
        fscanf(fin, "%d", &F);

        for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) map[i][j] = 0;

        for (i = 1; i <= F; i++) {
            fscanf(fin, "%d %d", &j, &k);
            map[j][k]++; map[k][j]++;
        }
        fclose(fin);
    }

    {
        int i, j, start = 1;
        for (i = 1; i <= N; i++){
            for (j = 1; j<=N; j++) map[i][0] += map[i][j];
            if (map[i][0] % 2 == 1) {start = i; break;}
        }
        dfs(start, 1);
    }


    {
        fout = fopen("fence.out", "w");
        if (path[0] != F) printf("Wrong:%d\n", path[0]);
        int i;
        for (i = path[0]; i >= 1; i--) fprintf(fout, "%d\n", path[i]);
        fclose(fout);
    }

    return 0;
}
