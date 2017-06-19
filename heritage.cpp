/*
  PROG: heritage
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <limits.h>
#define MAX_N 27

int n = INT_MAX;
char in[MAX_N], pre[MAX_N], post[MAX_N];

void pp(char* arr) {
    for (int i = 0; i < n; ++i) {
        printf("%c", arr[i] == 0 ? '*' : arr[i]);
    }
    printf("\n");
}

void solve(int a, int b, int c, int d, int e, int f) {
    if (a > b || c > d || e > f) {
        return;
    }
    char root = pre[c];
    int root_in_in;
    for (root_in_in = a; root_in_in <= b; ++root_in_in) {
        if (in[root_in_in] == root) {
            break;
        }
    }
    int left_size = root_in_in - a;
    post[f] = root;
    solve(a, root_in_in-1, c+1, c+left_size, e, e+left_size-1);
    solve(root_in_in+1, b, c+left_size+1, d, e+left_size, f-1);
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("heritage.in");
    for (n = 0; ; n++) {
        in[n] = fin.get();
        if (in[n] == '\n') {
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        fin >> pre[i];
    }
    fin.close();

    solve(0, n-1, 0, n-1, 0, n-1);

    pp(in);
    pp(pre);
    pp(post);

    std::ofstream fout("heritage.out");
    for (int i = 0; i < n; ++i) {
        fout << post[i];
    }
    fout << "\n";
    fout.close();
    return 0;
}

// AEFDBHGC
