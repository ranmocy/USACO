/*
  PROG: nuggets
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits.h>
#define MAX_N 10
#define MAX_SIZE 256
#define MAX_RESULT_ARR MAX_SIZE * 2

int n = INT_MAX, box[MAX_N];
bool a[MAX_RESULT_ARR];

bool check_all_multiples() {
  for (int i = 1; i < n; ++i) {
    if (box[i] % box[0] != 0) {
      return false;
    }
  }
  return true;
}

bool check_all_even() {
  for (int i = 0; i < n; ++i) {
    if (box[i] % 2 != 0) {
      return false;
    }
  }
  return true;
}

void init_a() {
  for (int i = 0; i < MAX_SIZE; ++i) {
    a[i] = false;
  }
  a[MAX_SIZE - 1] = true; // for 0
}

void shift_a() {
  for (int i = 0; i < MAX_SIZE; ++i) {
    a[i] = a[i + MAX_SIZE];
  }
}

int solve() {
    std::sort(box, box+n, std::less<int>());
    if (box[0] == 1 || check_all_multiples() || check_all_even()) {
      printf("infinity\n");
      return 0;
    }
    init_a();

    long base = 1, // a[MAX_SIZE] means
         min = 1,
         max = 1; // value in (min, max] can be composed
    while (min < 2e9) {
      for (int i = MAX_SIZE; i < MAX_RESULT_ARR; ++i) {
        long current = base + i - MAX_SIZE;
        a[i] = false;
        for (int j = 0; j < n; ++j) {
          if (a[i - box[j]]) {
            a[i] = true;
            break;
          }
        }
        if (a[i]) {
          max = current;
        } else {
          min = max = current;
        }
        if (max - min >= box[0]) {
          return min;
        }
      }

      shift_a();
      base += MAX_SIZE;
    }

    printf("exceed 2e9\n");
    return 0;
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("nuggets.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
      fin >> box[i];
    }
    fin.close();

    std::ofstream fout("nuggets.out");
    fout << solve() << "\n";
    fout.close();
    return 0;
}
