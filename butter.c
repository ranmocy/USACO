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
typedef struct heap {
    int index;
    int * dist;
} HEAP;

int N, P, C;
int cows[MAX_P+1], dist[MAX_P+1][MAX_P+1], neighbor[MAX_P+1][MAX_P+1];


void shift(HEAP heap[MAX_P+1], int index, int hash[MAX_P+1])
{
    while (index <= heap[0].index) {
        int left = index*2, right = index*2+1, smallest = index;
        if ((left <= heap[0].index) && (*heap[left].dist < *heap[smallest].dist)) smallest = left;
        if ((right <= heap[0].index) && (*heap[right].dist < *heap[smallest].dist)) smallest = right;
        if (smallest != index) {
            HEAP t = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = t;
            hash[heap[index].index] = index;
            hash[heap[smallest].index] = smallest;
            index = smallest;
        } else break;
    }
}

void shift_up(HEAP heap[MAX_P+1], int index, int hash[MAX_P+1])
{
    while (index > 1)
        if (*heap[index].dist < *heap[index/2].dist) {
            HEAP t = heap[index];
            heap[index] = heap[index/2];
            heap[index/2] = t;
            hash[heap[index].index] = index;
            hash[heap[index/2].index] = index/2;
            index /= 2;
        } else break;
}


int main()
{
    {
        FILE *fin = fopen("butter.in", "r");
        fscanf(fin, "%d %d %d", &N, &P, &C);
        int i, j, k, t;
        for (i = 1; i <= N; i++){
            fscanf(fin, "%d", &t);
            cows[t]++;
        }
        for (i = 1; i <= P; i++)
            for (j = 1; j <= P; j++)
                if (i == j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = INF;
        for (i = 1; i <= C; i++){
            fscanf(fin, "%d %d %d", &j, &k, &t);
            dist[j][k] = dist[k][j] = t;
            neighbor[j][++neighbor[j][0]] = k;
            neighbor[k][++neighbor[k][0]] = j;
        }
        fclose(fin);
    }

    { /* Dijkstra to find the shortest path betwen all pairs in O(VE)
         Not Floyd because O(V^3) is slower in sparse graph */
        int i, j, u, v;
        for (u = 1; u <= P; u++) {
            HEAP heap[MAX_P+1];
            int hash[MAX_P+1];
            heap[0].index = P;
            for (i = 1; i <= P; i++) {
                heap[i].index = i;
                heap[i].dist = &dist[u][i];
                hash[i] = i;
            }
            for (i = P/2; i >= 1; i--) shift(heap, i, hash);

            for (j = 1; j <= P; j++) {
                v = heap[1].index;
                heap[1] = heap[heap[0].index--];
                shift(heap, 1, hash);

                for (i = 1; i <= neighbor[v][0]; i++){
                    int m = neighbor[v][i], t = dist[u][v] + dist[v][m];
                    if (t < dist[u][m]) {
                        dist[u][m] = t;
                        shift_up(heap, hash[m], hash);
                    }
                }
            }
        }
    }

    {  /* Enum the answer */
        int i, k, ans = 0, d = INF;
        for (k = 1; k <= P; k++){
            int t = 0;
            for (i = 1; i <= P; i++)
                t += cows[i] * dist[i][k];
            if (t < d) {
                ans = k;
                d = t;
            }
        }

        FILE *fout = fopen("butter.out", "w");
        fprintf(fout, "%d\n", d);
        fclose(fout);
    }

    return 0;
}
