/*
  PROG: frameup
  LANG: C++11
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <limits.h>
#define MAX_H 30
#define MAX_N 26

class rectangle {
public:
    bool exist;
    int index, top, right, bottom, left;

    rectangle() {
        exist = false;
        index = -1;
        top = left = MAX_H;
        right = bottom = -1;
    }

    void update(int hh, int ww, int i) {
        exist = true;
        index = i;
        top = std::min(top, hh);
        left = std::min(left, ww);
        bottom = std::max(bottom, hh);
        right = std::max(right, ww);
    }
};


int h, w, map[MAX_H][MAX_H];

std::queue< std::vector<int> > results;
std::vector<int> current_result;

rectangle recs[MAX_N]; // all rectangle list
int chars[MAX_N], n = 0; // all different chars on the map, in order
bool ontop[MAX_N][MAX_N]; // ontop[i][j] is true when i is on top of j
int ontop_count[MAX_N]; // how many rectangles is i on top of
bool visited[MAX_N];


void find_result() {
    if (current_result.size() >= n) {
        results.push(current_result);
        return;
    }
    for (int i = 0; i < n; ++i) {
        int c = chars[i];
        if (ontop_count[c] == 0 && !visited[c]) {
            visited[c] = true;
            current_result.push_back(c);
            for (int j = 0; j < n; ++j) {
                int o = chars[j];
                if (ontop[o][c]) {
                    ontop_count[o]--;
                }
            }

            find_result();

            visited[c] = false;
            current_result.pop_back();
            for (int j = 0; j < n; ++j) {
                int o = chars[j];
                if (ontop[o][c]) {
                    ontop_count[o]++;
                }
            }
        }
    }
}

void solve() {
    // find all rectangles
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (map[i][j] >= 0) {
                recs[map[i][j]].update(i, j, map[i][j]);
            }
        }
    }

    // find all differnt chars, in order
    for (int i = 0; i < MAX_N; ++i) {
        if (recs[i].exist) {
            chars[n++] = i;
        }
    }

    // go through all edges to find order
    for (int r_index = 0; r_index < MAX_N; ++r_index) {
        rectangle r = recs[r_index];
        if (r.exist) {
            for (int ww = r.left; ww <= r.right; ++ww) {
                // top edge
                if (map[r.top][ww] != r_index) {
                    ontop[map[r.top][ww]][r_index] = true;
                }
                // bottom edge
                if (map[r.bottom][ww] != r_index) {
                    ontop[map[r.bottom][ww]][r_index] = true;
                }
            }
            for (int j = r.top + 1; j <= r.bottom - 1; ++j) {
                // left edge
                if (map[j][r.left] != r_index) {
                    ontop[map[j][r.left]][r_index] = true;
                }
                // right edge
                if (map[j][r.right] != r_index) {
                    ontop[map[j][r.right]][r_index] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ontop[chars[i]][chars[j]]) {
                printf("%c > %c\n", 'A' + chars[i], 'A' + chars[j]);
            }
        }
    }

    // find all topo order
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ontop[chars[i]][chars[j]]) {
                ontop_count[chars[i]]++;
            }
        }
    }

    find_result();
}

int main(int argc, char const *argv[]) {
    std::memset(map, 0, sizeof map);
    std::memset(ontop, 0, sizeof ontop);
    std::memset(ontop_count, 0, sizeof ontop_count);
    std::memset(visited, 0, sizeof visited);

    std::ifstream fin("frameup.in");
    fin >> h >> w;
    fin.get(); // skip newline
    char c;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            fin >> c;
            map[i][j] = (c == '.') ? -1 : c - 'A';
        }
    }
    fin.close();

    solve();

    std::ofstream fout("frameup.out");
    for (; !results.empty(); results.pop()) {
        std::vector<int> r = results.front();
        for (std::vector<int>::iterator i = r.begin(); i != r.end(); ++i) {
            fout << (char) ('A' + *i);
        }
        fout << "\n";
    }
    fout.close();
    return 0;
}
