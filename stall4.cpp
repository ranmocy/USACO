/*
  PROG: stall4
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <limits.h>
#define MAX_N 200 // cows
#define MAX_M 200 // stalls
#define MAX_NODE (MAX_M + MAX_N + 1)
#define SOURCE 0  // source of whole graph
#define TARGET (MAX_M + MAX_N + 1) // sink of whole graph
#define STALL(n) (MAX_N + n)
#define NOT_VISITED -1

short n, // cows
      m, // stalls
      g[MAX_NODE+1][MAX_NODE+1]; // graph of cows' preferneces


short solve() {
    short max = 0;
    short p[MAX_NODE+1];
    std::memset(p, 0, sizeof p);

    while (true) {
        // reverse bfs
        std::queue<short> q;
        q.push(TARGET);
        p[TARGET] = TARGET; // visited
        for (int i = 0; i < MAX_NODE; ++i) {
            p[i] = NOT_VISITED;
        }
        while (!q.empty()) {
            short t = q.front();
            q.pop();
            for (int s = 0; s < MAX_NODE; ++s) {
                if (g[s][t] > 0 && p[s] == NOT_VISITED) {
                    p[s] = t;
                    q.push(s);
                }
            }
            if (p[SOURCE] != NOT_VISITED) {
                break;
            }
        }

        if (p[SOURCE] == NOT_VISITED) {
            // no more augument path
            break;
        }

        // update graph
        printf("update: ");
        for (int t = SOURCE; t != TARGET; t = p[t]) {
            printf("%d ", t);
            g[t][p[t]]--;
            g[p[t]][t]++;
        }
        printf("\n");
        max++;
    }

    return max;
}

int main(int argc, char const *argv[]) {
    std::memset(g, 0, sizeof g);

    short t, stall;
    std::ifstream fin("stall4.in");
    fin >> n >> m;
    for (short cow = 1; cow <= n; ++cow) {
        fin >> t;
        for (short i = 0; i < t; ++i) {
            fin >> stall;
            g[cow][STALL(stall)] = 1;
        }
    }
    fin.close();

    for (int cow = 1; cow <= n; ++cow) {
        g[SOURCE][cow] = 1;
    }
    for (int stall = 1; stall <= m; ++stall) {
        g[STALL(stall)][TARGET] = 1;
    }

    std::ofstream fout("stall4.out");
    fout << solve() << "\n";
    fout.close();
    return 0;
}
