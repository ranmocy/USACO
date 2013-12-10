/*
  PROG: cowtour
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <math.h>
typedef enum { false, true } bool;
#define MAX_N 150
#define INF 200000

int n,i,j,k,l;
int x[MAX_N+1], y[MAX_N+1];  /* coordinates */
int c[MAX_N+1];              /* color */
bool g[MAX_N+1][MAX_N+1];    /* connections */
double d[MAX_N+1][MAX_N+1];  /* euler dist */
double s[MAX_N+1][MAX_N+1];  /* shortest dist */
double min_diameter = INF;   /* final answer */


int main()
{
    FILE *fin = fopen("cowtour.in", "r");
    FILE *fout = fopen("cowtour.out", "w");

    fscanf(fin, "%d", &n);

    for (i = 1; i <= n; i++){
        fscanf(fin, "%d %d\n", &x[i], &y[i]);
    }

    for (i = 1; i <= n; i++){
        char t;
        for (j = 1; j <= n; j++){
            fscanf(fin, "%c", &t);
            g[i][j] = t - 48;
        }
        fscanf(fin, "\n");
        g[i][i] = 1;  /* i->i should be treated as 1 */
    }

    /* calc directly distance between all vertices */
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            d[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            d[j][i] = d[i][j];
        }
    }

    /* shortest path by floyd */
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if (g[i][j] == 1){
                s[i][j] = d[i][j];
            } else {
                s[i][j] = INF;
            }
        }
    }
    for (k = 1; k <= n; k++){
        for (i = 1; i <= n; i++){
            for (j = 1; j <= n; j++){
                if (s[i][j] > s[i][k] + s[k][j]) s[i][j] = s[i][k] + s[k][j];
            }
        }
    }

    /* colorize by DFS */
    for (i = 1; i <= n; i++){
        if (c[i] != 0) continue;
        c[i] = i;
        int top = 0;
        int stack[MAX_N+1] = {i};
        while (top >= 0){
            int current = stack[top];
            top--;
            for (j = 1; j <= n; j++){
                if ((g[current][j] == 1) && (c[j] == 0)){
                    c[j] = i;
                    top++;
                    stack[top] = j;
                }
            }
        }
    }


    /* from the original graph */
    double orig_diameter = 0;
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if ((c[i] == c[j]) && (s[i][j] > orig_diameter)) {
                orig_diameter = s[i][j];
            }
        }
    }

    /* try to add a edge between different colored node */
    double diameter;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (c[i] != c[j]){
                /* assume g[i][j] = true */
                diameter = orig_diameter;
                for (k = 1; k <= n; k++)
                    if (c[i] == c[k])
                        for (l = 1; l <= n; l++)
                            if ((c[j] == c[l]) && (s[k][i] + d[i][j] + s[j][l] > diameter))
                                diameter = s[k][i] + d[i][j] + s[j][l];
                if (diameter < min_diameter) min_diameter = diameter;
            }

    fprintf(fout, "%.6f\n", min_diameter);
    fclose(fin);
    fclose(fout);
    return 0;
}
