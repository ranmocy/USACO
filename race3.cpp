/*
  PROG: race3
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <limits.h>
#define MAX_N 51

int n;
bool g[MAX_N][MAX_N], visited[MAX_N];
std::queue<int> vips, // very important points
                spoints; // splitting points

bool is_spoint(int point) {
    for (int i = 0; i < n; ++i) {
        if (visited[i] && i != point) {
            if (g[point][i]) {
                // as the finish point of first part, a splitting point can not has
                // a out-going edge
                return false;
            }

            for (int j = 0; j < n; ++j) {
                if (!visited[j]) {
                    if (g[j][i]) {
                        // there is an edge from second part to first part,
                        // so it's not a splitting point
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void solve() {
    for (int point = 1; point < n; ++point) {
        // try to remove point
        std::memset(visited, 0, sizeof visited);
        visited[point] = true;

        // bfs
        std::queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int i = 1; i <= n; ++i) {
                if (g[current][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        if (!visited[n]) {
            // there is no path from 0 to n, which means current point is a VIP
            vips.push(point);

            if (is_spoint(point)) {
                spoints.push(point);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    std::memset(g, 0, sizeof g);

    std::ifstream fin("race3.in");
    n = -1;
    int t;
    for (fin >> t; t != -1; fin >> t) {
        n++;
        while (t != -2) {
            g[n][t] = true;
            fin >> t;
        }
    }
    fin.close();

    printf("n:%d\n", n);

    solve();

    std::ofstream fout("race3.out");
    fout << vips.size();
    for (; !vips.empty(); vips.pop()) {
        fout << ' ' << vips.front();
    }
    fout << "\n";

    fout << spoints.size();
    for (; !spoints.empty(); spoints.pop()) {
        fout << ' ' << spoints.front();
    }
    fout << "\n";
    fout.close();
    return 0;
}
