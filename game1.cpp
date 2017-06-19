/*
  PROG: game1
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <limits.h>
#define MAX_N 100

int n = INT_MAX,
    b[MAX_N], // board numbers
    best[MAX_N][MAX_N]; // best score between i and j on board
bool selection[MAX_N][MAX_N]; // best score selection. false for left, true for right

// returns the second best between i and j on board
int second(int i, int j) {
    if (selection[i][j]) {
        return (j > 0) ? best[i][j-1] : 0;
    } else {
        return (i < n-1) ? best[i+1][j] : 0;
    }
}

void solve() {
    int j, vl, vr; // value if selection left end or right end
    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            j = i + l - 1;
            vl = b[i] + second(i+1, j);
            vr = b[j] + second(i, j-1);
            if (vl < vr) {
                best[i][j] = vr;
                selection[i][j] = true;
            } else {
                best[i][j] = vl;
                selection[i][j] = false;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("game1.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> b[i];
        best[i][i] = b[i];
        selection[i][i] = false;
    }
    fin.close();

    solve();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d(%c)\t", best[i][j], selection[i][j] ? 'r' : 'l');
        }
        printf("\n");
    }

    std::ofstream fout("game1.out");
    fout << best[0][n-1] << " " << second(0, n-1) << "\n";
    fout.close();
    return 0;
}
