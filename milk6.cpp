/*
  PROG: milk6
  LANG: C++11
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <limits.h>
#define MAX_N 33
#define MAX_M 1001
#define MAX_C (2000000 * MAX_M + 1)

struct edge {
    int s, t;
    long long c;
};

int n, m, indexes_count;
long long g[MAX_N][MAX_N], // original map
          map[MAX_N][MAX_N], // map used for max flow,
          max_flow; // max flow result
std::vector<edge> edges;

long long get_max_flow() {
    std::copy(&g[0][0], &g[0][0] + MAX_N * MAX_N, &map[0][0]);
    long long max = 0;
    int path[n+1];
    bool visited[n+1];

    while (true) {
        // bfs to get augmenting path
        std::memset(visited, 0, sizeof visited);
        std::queue<int> q;
        q.push(1);
        visited[1] = true;
        for (; !q.empty(); q.pop()) {
            int node = q.front();
            for (int i = 1; i <= n; ++i) {
                if (!visited[i] && map[node][i] > 0) {
                    q.push(i);
                    visited[i] = true;
                    path[i] = node;
                }
            }
            if (visited[n]) {
                break;
            }
        }

        if (!visited[n]) {
            // no more augmenting path
            break;
        }

        // find flow volumn of the path
        long long volumn = MAX_C;
        for (int i = n; i != 1; i = path[i]) {
            volumn = std::min(volumn, map[path[i]][i]);
        }

        // update the map
        for (int i = n; i != 1; i = path[i]) {
            map[path[i]][i] -= volumn;
            map[i][path[i]] += volumn;
        }

        max += volumn;
    }
    return max;
}

int main(int argc, char const *argv[]) {
    std::memset(g, 0, sizeof g);

    std::ifstream fin("milk6.in");
    fin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int s, t, w;
        fin >> s >> t >> w;
        w = w * MAX_M + 1;
        g[s][t] += w;
        edges.push_back((edge) {.s = s, .t = t, .c = w});
    }
    fin.close();

    max_flow = get_max_flow();
    indexes_count = max_flow % MAX_M;

    std::ofstream fout("milk6.out");
    fout << max_flow / MAX_M << " " << indexes_count << "\n";
    bool removed[edges.size()];
    std::memset(removed, 0, sizeof removed);
    for (int count = 0; count < indexes_count; ++count) {
        printf("finding edge #%d\n", count);
        for (int index = 0; index < edges.size(); ++index) {
            if (removed[index]) {
                continue;
            }
            edge e = edges.at(index);
            // try remove this edge
            g[e.s][e.t] -= e.c;
            long long mf = get_max_flow();
            printf("%d:%d,%d: %lld + %lld - %lld = %lld\n",
                   index, e.s, e.t, e.c / MAX_M, mf / MAX_M, max_flow / MAX_M,
                   (e.c + mf - max_flow) / MAX_M);
            if (mf + e.c == max_flow) {
                // this is part of the minimal cut
                fout << index + 1 << "\n";
                max_flow -= e.c;
                removed[index] = true;
                break;
            } else {
                // no, restore it
                g[e.s][e.t] += e.c;
            }
        }
    }
    fout.close();
    return 0;
}
