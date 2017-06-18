/*
  PROG: range
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#define MAX_N 250

int n = INT_MAX, // size of the map
    size[MAX_N][MAX_N], // size of the max square when map[i][j] is the right-bottom corner
    count[MAX_N]; // count of different size of square

int min(int a, int b, int c) {
    int t = a < b ? a : b;
    return t < c ? t : c;
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("range.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        count[i] = 0;
        for (int j = 0; j < n; ++j) {
            size[i][j] = 0;
        }
    }
    char t; // input char
    int p; // max square size of size[i][j]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> t;
            if (t == '1') {
                // ready to eat
                if (i > 0 && j > 0) {
                    p = min(size[i-1][j], size[i][j-1], size[i-1][j-1]) + 1;
                } else {
                    p = 1;
                }
            } else {
                // ravaged field
                p = 0;
            }
            size[i][j] = p;
            for (int k = 2; k <= p; k++) {
                count[k]++;
            }
        }
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", size[i][j]);
        }
        printf("\n");
    }

    std::ofstream fout("range.out");
    for (int i = 2; i <= n; ++i) {
        if (count[i] > 0) {
            fout << i << " " << count[i] << "\n";
        }
    }
    fout.close();
    return 0;
}
