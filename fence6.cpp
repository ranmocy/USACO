/*
  PROG: fence6
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits.h>
#define MAX_N 100
#define NO_WAY -1
#define FROM_LEFT 0
#define FROM_RIGHT 1

short n = SHRT_MAX, length[MAX_N+1], map[MAX_N+1][MAX_N+1];
bool visited[MAX_N+1];
int best = INT_MAX;

void dfs(short edge, short side, int current) {
    printf("%d[%d], %d\n", edge, side, current);
    if (current >= best) {
        printf("======\n");
        return;
    }
    for (short i = 1; i <= n; ++i) {
        if (map[edge][i] == side) {
            if (visited[i]) {
                if (best > current) {
                  printf("%d[%d] => %d, %d, %d\n", edge, side, i, current, best);
                }
                // TODO: not current but current[edge] - current[i]
                best = std::min(best, current);
            } else {
                visited[i] = true;
                dfs(i, 1 - map[i][edge], current + length[i]);
                visited[i] = false;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("fence6.in");
    fin >> n;
    for (short i = 0; i <= n; ++i) {
        visited[i] = false;
    }
    short p, q, n1, n2;
    for (short i = 0; i <= n; ++i) {
        for (short j = 0; j <= n; ++j) {
            map[i][j] = NO_WAY;
        }
    }
    for (short i = 0; i < n; ++i) {
        fin >> p;
        fin >> length[p] >> n1 >> n2;
        for (short j = 0; j < n1; ++j) {
            fin >> q;
            map[p][q] = FROM_LEFT;
        }
        for (short k = 0; k < n2; ++k) {
            fin >> q;
            map[p][q] = FROM_RIGHT;
        }
    }
    fin.close();

    for (short i = 1; i <= n; ++i) {
        visited[i] = true;
        dfs(i, FROM_LEFT, length[i]);
        visited[i] = false;
    }

    std::ofstream fout("fence6.out");
    fout << best << "\n";
    fout.close();
    return 0;
}
