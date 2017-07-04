/*
  PROG: ditch
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#include <limits.h>
#define MAX_M 200
#define NOT_VISITED -1

short n, m;
long g[MAX_M][MAX_M]; // g[i][j] for *total* capacity from i to j

long solve() {
    long max_flow = 0;
    short p[m]; // path of argument path. from node p[i] to node i
    while (true) {
        // reverse bfs to find argument path
        std::queue<short> q; // queue for bfs
        q.push(m - 1);
        for (short i = 0; i < m; ++i) {
            p[i] = NOT_VISITED;
        }
        while (!q.empty()) {
            short t = q.front();
            q.pop();
            for (short s = 0; s < m; ++s) {
                if (g[s][t] > 0 && p[s] == NOT_VISITED) {
                    p[s] = t;
                    q.push(s);
                }
            }
            if (p[0] != NOT_VISITED) {
                break;
            }
        }

        if (p[0] == NOT_VISITED) {
            // no more argument path
            break;
        }

        // find the volumn of the argument path
        long v = LONG_MAX;
        for (short s = 0; s != m-1; s = p[s]) {
            v = std::min(v, g[s][p[s]]);
        }
        printf("v: %ld\n", v);

        // update graph
        for (short s = 0; s != m-1; s = p[s]) {
            g[s][p[s]] -= v;
            g[p[s]][s] += v;
        }

        max_flow += v;
    }
    return max_flow;
}

int main(int argc, char const *argv[]) {
    std::memset(g, 0, sizeof g);

    std::ifstream fin("ditch.in");
    fin >> n >> m;
    short s, t;
    long c;
    for (short i = 0; i < n; ++i) {
        fin >> s >> t >> c;
        g[s-1][t-1] += c;
    }
    fin.close();

    std::ofstream fout("ditch.out");
    fout << solve() << "\n";
    fout.close();
    return 0;
}
