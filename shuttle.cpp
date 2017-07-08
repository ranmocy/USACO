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

void front(int current) {
    if (current <= 0) {
        return;
    }
    front(current - 1);
    if (current % 2 == 0) {
        for (int i = 2 * current + 1; i >= 1; i -= 2) {
            move(i, current);
        }
    } else {
        for (int i = 1; i <= 2 * current + 1; i += 2) {
            move(i, current);
        }
    }
}

void end(int current) {
    if (current <= 0) {
        return;
    }
    if (current % 2 == 0) {
        for (int i = 2; i <= 2 * current; i += 2) {
            move(i, current);
        }
    } else {
        for (int i = 2 * current; i >= 2; i -= 2) {
            move(i, current);
        }
    }
    end(current - 1);
}

void solve() {
    front(n);
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
