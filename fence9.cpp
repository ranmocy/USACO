/*
  PROG: fence9
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <limits.h>
#define MAX_N 100

// triangle of (0, 0), (n, m), (p, 0)
int n, m, p;

double get_cross_x(int y, int a, int b) {
    // x / y = a / b
    int x = ceil(((double) y) * a / b);
    return (x * b == y * a) ? x + 1 : x;
}

int solve() {
    int left, right;
    long total = 0;
    for (int y = 1; y < m; ++y) {
        // check line y
        left = get_cross_x(y, n, m); // x / y = n / m
        right = p - get_cross_x(y, p-n, m); // (p - x) / y = (p - n) / m
        total += right - left + 1;
    }
    return total;
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("fence9.in");
    fin >> n >> m >> p;
    fin.close();

    std::ofstream fout("fence9.out");
    fout << solve() << "\n";
    fout.close();
    return 0;
}
