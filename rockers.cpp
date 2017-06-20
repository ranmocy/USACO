/*
  PROG: rockers
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#define MAX_N 20

int N, T, M, l[MAX_N+1], f[MAX_N+1][MAX_N+1][MAX_N+1];

int optimize(int orig, int potential, bool condition) {
  if (condition && potential > orig) {
    return potential;
  } else {
    return orig;
  }
}

void solve() {
  for (int n = 1; n <= N; ++n) {
    for (int m = 1; m <= M; ++m) {
      for (int t = 0; t <= T; ++t) {
        int v = 0;
        v = optimize(v, f[n-1][t][m], n > 1); // drop the song
        v = optimize(v, f[n][t-1][m], t > 0); // drop the time
        v = optimize(v, f[n][t][m-1], m > 1); // drop the disk
        v = optimize(v, f[n-1][t-l[n]][m]+1, t>=l[n]); // new song in current disk
        v = optimize(v, f[n-1][T][m-1]+1, t>=l[n]); // new song in new disk
        f[n][t][m] = v;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("rockers.in");
    fin >> N >> T >> M;
    for (int i = 1; i <= N; ++i) {
      fin >> l[i];
    }
    fin.close();

    for (int j = 0; j <= T; ++j) {
      for (int k = 0; k <= M; ++k) {
        f[0][j][k] = 0;
      }
    }
    for (int i = 0; i <= N; ++i) {
      for (int j = 0; j <= T; ++j) {
        f[i][j][0] = 0;
      }
    }

    solve();

    for (int i = 0; i <= N; ++i) {
      for (int j = 0; j <= T; ++j) {
        for (int k = 0; k <= M; ++k) {
          printf("%d\t", f[i][j][k]);
        }
        printf("\n");
      }
      printf("\n\n");
    }

    std::ofstream fout("rockers.out");
    fout << f[N][T][M] << "\n";
    fout.close();

    return 0;
}
