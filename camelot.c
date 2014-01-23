/*
  PROG: camelot
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define N_OFFSET 8
#define MAX_R 30
#define MAX_C 26
#define INF MAX_R*MAX_C*MAX_R*MAX_C  /* RC knights with RC steps */
typedef enum { false, true } bool;
typedef struct position {int x, y;} position;
typedef int board[MAX_R+1][MAX_C+1];

position offset[N_OFFSET] = {{+1, +2}, {+1, -2}, {-1, +2}, {-1, -2},
                             {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1}};

int R, C, K, ans = INF;      /* K for # of knights */
position pos[MAX_R*MAX_C+1]; /* pos[0] is for king */
board dist[MAX_R+1][MAX_C+1];


int abs(int a)
{return (a >= 0) ? a : -a;}

int min(int a, int b)
{return (a <= b) ? a : b;}

int max(int a, int b)
{return (a >= b) ? a : b;}

/* calc the minimal dist to king */
int dist_to_king(position p)
{
    int x = abs(p.x - pos[0].x), y = abs(p.y - pos[0].y);
    return (x + y - min(x, y));
}

bool update_min(board board, int x, int y, int b)
{
    if ((1 <= x) && (x <= R) &&
        (1 <= y) && (y <= C) &&
        (b < board[x][y])) {
        board[x][y] = b;
        return true;
    } else return false;
}

void bfs(board board, position start)
{
    int i, j;
    for (i = 1; i <= R; i++)
        for (j = 1; j <= C; j++)
            board[i][j] = INF;
    board[start.x][start.y] = 0;

    position queue[MAX_R*MAX_C];
    int qhead = 0, qtail = 0;
    queue[0] = start;

    while (qhead <= qtail) {
        position current = queue[qhead++];
        int cost = board[current.x][current.y];

        int i;
        for (i = 0; i < N_OFFSET; i++)
            if (update_min(board,
                           current.x+offset[i].x,
                           current.y+offset[i].y,
                           cost+1)) {
                qtail++;
                queue[qtail].x = current.x+offset[i].x;
                queue[qtail].y = current.y+offset[i].y;
            }
    }
}

/*
  Enumerate the target meet point, for R*C=780 times.
  Use BFS to search the shortest path from the meet point.
  Backward search the knights pathes. Record the shortest length to the king's position.
  That will be the king's path. He may be picked up at the meet point.
*/
int main()
{
    {  /* read input */
        FILE *fin = fopen("camelot.in", "r");
        fscanf(fin, "%d %d\n", &R, &C);

        char c;
        K = -1;
        while ((c = fgetc(fin)) != EOF) {
            if (('A' <= c) && (c <= 'Z')) {
                K++;
                pos[K].y = c - 64;
                fscanf(fin, "%d", &pos[K].x);
            }
        }
        fclose(fin);
    }

    {  /* Shotest path between all pairs */
        int i, j, k, m, n;
        for (i = 1; i <= R; i++){
            for (j = 1; j <= C; j++){
                position p = {i, j};
                bfs(dist[i][j], p);
            }
        }

        for (i = 1; i <= R; i++) {
            for (j = 1; j <= C; j++) {
                /* All knights steps go to (i,j) */
                int knights_steps = 0;
                for (k = 1; k <= K; k++)
                    knights_steps += dist[i][j][pos[k].x][pos[k].y];
                if (knights_steps >= ans) continue;

                /* Extra cost to pick up the king */
                for (m = 1; m <= R; m++)
                    for (n = 1; n <= C; n++){
                        position pick_point = {m, n};
                        for (k = 1; k <= K; k++){
                            int steps = knights_steps - dist[i][j][pos[k].x][pos[k].y] + /* remove the cost knight k to the meet point */
                                    dist_to_king(pick_point) +  /* the cost of king to the pick point */
                                    dist[i][j][pick_point.x][pick_point.y] + dist[pick_point.x][pick_point.y][pos[k].x][pos[k].y]; /* cost of knight who pick */
                            if (steps < ans) ans = steps;
                        }
                    }
            }
        }
    }

    {  /* output */
        FILE *fout = fopen("camelot.out", "w");
        if (K == 0) fprintf(fout, "0\n");
        else fprintf(fout, "%d\n", ans);
        fclose(fout);
    }

    return 0;
}
