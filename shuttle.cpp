/*
  PROG: shuttle
  LANG: C++11
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <limits.h>
#define MAX_N 12 // number of marbles in one color

int n;
std::queue<int> q;

// index in [1, 2 * current + 1]
void move(int index, int current) {
    q.push(index + (n - current));
}

void middle(int current) {
    if (current <= 0) {
        return;
    }
    if (current % 2 == 0) {
        // moving white marbles
        // BWBW_
        for (int i = 2 * current - 1; i >= 1; i -= 2) {
            move(i, current);
        }
    } else {
        // moving black marbles
        // _WBWBWB
        for (int i = 3; i <= 2 * current + 1; i += 2) {
            move(i, current);
        }
    }
}

void front(int current) {
    if (current <= 0) {
        return;
    }
    front(current - 1);
    middle(current - 1);
    if (current % 2 == 0) {
        move(2 * current + 1, current);
    } else {
        move(1, current);
    }
}

void end(int current) {
    if (current <= 0) {
        return;
    }
    if (current % 2 == 0) {
        move(2, current);
    } else {
        move(2 * current, current);
    }
    middle(current - 1);
    end(current - 1);
}

void solve() {
    front(n);
    middle(n);
    end(n);
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("shuttle.in");
    fin >> n;
    fin.close();

    solve();

    std::ofstream fout("shuttle.out");
    while (!q.empty()) {
        fout << q.front();
        q.pop();
        for (int i = 1; i < 20; ++i) {
            if (q.empty()) {
                break;
            }
            fout << " " << q.front();
            q.pop();
        }
        fout << "\n";
    }
    fout.close();
    return 0;
}
