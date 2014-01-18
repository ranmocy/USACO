/*
  PROG: shopping
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define MAX_S 99   /* # of offers */
#define MAX_N 5    /* # of different product */
#define MAX_K 5    /* # of product in offer */
#define MAX_C 999  /* range of product id */
#define MAX_P 9999 /* range of product price */
#define INF MAX_N*MAX_K*MAX_P+1
typedef enum { false, true } bool;
/* typedef struct vector { */
/*     int length, value[MAX_P]; */
/* } vector; */
typedef int vector[MAX_C+1];


int S, C;
vector offers[MAX_S], target;


void copy(vector a, vector b)
{int i; for (i = 1; i <= C; i++) b[i] = a[i];}

void add(vector a, vector b, vector c)
{int i; for (i = 1; i <= C; i++) c[i] = a[i] + b[i];}

void minus(vector a, vector b, vector c)
{int i; for (i = 1; i <= C; i++) c[i] = a[i] - b[i];}

int divide(vector a, vector b)
{
    int i, ans = MAX_C;
    for (i = 1; i <= C; i++)
        if ((b[i] != 0) && (a[i]/b[i] < ans))
            ans = a[i]/b[i];
    return ans;
}

void print(vector a)
{int i; for (i = 0; i <= C; i++) printf("%d ", a[i]); printf("\n");}

bool empty(vector a)
{int i; for (i = 1; i <= C; i++) if (a[i] != 0) return false; return true;}

/*
  return the minimal price to build target with offers[s..S]
 */
int search(vector target, int s)
{
    if (s > S) {if (empty(target)) return 0; else return INF;}

    vector next;
    copy(target, next);
    int i, limit = divide(target, offers[s]), ans = INF;
    for (i = 0; i <= limit; i++) {
        int t = offers[s][0] * i + search(next, s + 1);
        if (t < ans) ans = t;
        minus(next, offers[s], next);
    }
    return ans;
}


/*
  S is the number of all offers, include regular ones
  C is the max of all product id in inputs
  offers[i] indicates how many product[i] in the offer
  offers[i][0] indicates the price of the offer
 */
int main()
{
    {
        FILE *fin = fopen("shopping.in", "r");
        fscanf(fin, "%d", &S);
        int i, s, n, k, c;
        for (s = 1; s <= S; s++) {
            fscanf(fin, "%d", &n);
            for (i = 1; i <= n; i++){
                fscanf(fin, "%d %d", &c, &k);
                if (c > C) C = c;
                offers[s][c] = k;
            }
            fscanf(fin, "%d", &offers[s][0]);
        }

        int b;
        fscanf(fin, "%d", &b);
        for (i = 1; i <= b; i++) {
            fscanf(fin, "%d %d", &c, &k);
            if (c > C) C = c;
            target[c] = k;
            S++;
            offers[S][c] = 1;
            fscanf(fin, "%d", &offers[S][0]);
        }
        fclose(fin);
    }

    {
        FILE *fout = fopen("shopping.out", "w");
        fprintf(fout, "%d\n", search(target, 1));
        fclose(fout);
    }
    return 0;
}
