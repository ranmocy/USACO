/*
  PROG: ratios
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true } bool;
#define N 3
#define MAX_N 100

int A[N][N], B[N];
FILE *fin, *fout;


int det(int a[N][N], int n)
{
    int i, j, t, ans = 0, m[N][N];
    if (n == 1) return a[0][0];
    for (t = 0; t < n; t++){
        for (i = 1; i < n; i++){
            for (j = 0; j < t; j++)
                m[i-1][j] = a[i][j];
            for (j = t+1; j < n; j++)
                m[i-1][j-1] = a[i][j];
        }
        if (t % 2 == 0) {
            ans += a[0][t] * det(m, n-1);
        } else {
            ans -= a[0][t] * det(m, n-1);
        }
    }
    return ans;
}

int abs(int a)
{
    return (a > 0) ? a : -a;
}

int gcd(int a, int b)
{
    if (abs(a) < abs(b)) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void print_none()
{
    fprintf(fout, "NONE\n");
    fclose(fout);
    exit(0);
}


int main()
{
    fin = fopen("ratios.in", "r");
    fout = fopen("ratios.out", "w");

    int i, j;
    for (j = 0; j < N; j++)
        fscanf(fin, "%d", &B[j]);
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            fscanf(fin, "%d", &A[i][j]);
    fclose(fin);

    int k = det(A, N);
    if (k == 0) print_none();

    int t, d[N], m[N][N];
    for (t = 0; t < N; t++){
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if (i == t)
                    m[i][j] = B[j];
                else
                    m[i][j] = A[i][j];
        d[t] = det(m, N);
    }

    int g = k;
    for (i = 0; i < N; i++)
        if (d[i] != 0) g = gcd(g, d[i]);

    k /= g;
    for (i = 0; i < N; i++) {
        d[i] /= g;
        if ((d[i] < 0) || (d[i] > MAX_N)) print_none();
    }

    if (k >= MAX_N) print_none();
    for (i = 0; i < N; i++)
        fprintf(fout, "%d ", d[i]);
    fprintf(fout, "%d\n", k);

    fclose(fout);
    return 0;
}
