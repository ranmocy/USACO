/*
  PROG: skidesign
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <limits.h>

#define MAX_N 1000
#define MAX_H 100
#define MIN_H 0
#define TARGET_DIFF 17

int n, h[MAX_N] /* old hill */, h2[MAX_N] /* new hill */;

int cost(int target[]) {
    int cost = 0;
    for (int j = 0; j < n; ++j) {
        cost += (target[j] - h[j]) * (target[j] - h[j]);
    }
    return cost;
}

int solve() {
    std::sort(h, h+n, std::less<int>());
    std::copy(h, h+n, h2);
    int total_cost = 0, times = std::max(h[n - 1] - h[0] - TARGET_DIFF, 0);

    for (int i = 0; i < times; ++i) {
        // if we increase all lowest hills by 1
        int h_lowest[n], height0 = h2[0];
        std::copy(h2, h2+n, h_lowest);
        for (int j = 0; (j < n) && (h_lowest[j] == height0); ++j) {
            h_lowest[j] += 1;
        }
        int cost0 = cost(h_lowest);

        // if we decrease all highest hills by 1
        int h_highest[n], height1 = h2[n - 1];
        std::copy(h2, h2+n, h_highest);
        for (int j = n - 1; (j >= 0) && (h_highest[j] == height1); --j) {
            h_highest[j] -= 1;
        }
        int cost1 = cost(h_highest);

        // compare costs
        if (cost0 < cost1) {
            std::copy(h_lowest, h_lowest+n, h2);
            total_cost = cost0;
        } else {
            std::copy(h_highest, h_highest+n, h2);
            total_cost = cost1;
        }
    }

    return total_cost;
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("skidesign.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> h[i];
    }
    fin.close();

    std::ofstream fout("skidesign.out");
    fout << solve() << "\n";
    fout.close();
    return 0;
}
