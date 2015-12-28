/*
  PROG: wormhole
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits.h>
using namespace std;

#define MAX_N 12
#define NOT_CONNECTED -1

struct hole_pos {
    int x, y;
};

struct hole_connection {
    // destination(hole id) when enter from left, or exit from right
    int left, right;
};

int i, j, N;
struct hole_pos hole[MAX_N];
struct hole_connection map[MAX_N];


// test if there is a loop.
// If move right after N times(we should reach each node at least once)
// and we still can move right, then there is a loop.
bool test_loop() {
    for (int i = 0; i < N; ++i) {
        int current_id = i;
        for (int j = 0; j < N; ++j) {
            current_id = map[map[current_id].left].right;
            if (current_id == NOT_CONNECTED) {
                break;
            }
        }
        if (current_id != NOT_CONNECTED) {
            return true;
        }
    }
    return false;
}

// enumerate all the possiblility of connections
int connect(int source_id) {
    // skip those connected holes
    while (source_id < N && map[source_id].left != NOT_CONNECTED) {
        source_id++;
    }

    // if it's the last one
    if (source_id >= N) {
        return test_loop() ? 1 : 0;
    }

    int result = 0;
    // otherwise, connect it with another one
    for (int target_id = source_id + 1; target_id < N; ++target_id) {
        if (map[target_id].left == NOT_CONNECTED) {
            map[source_id].left = target_id;
            map[target_id].left = source_id;
            result += connect(source_id + 1);
            map[source_id].left = map[target_id].left = NOT_CONNECTED;
        }
    }
    return result;
}

int solve() {
    for (int i = 0; i < N; ++i) {
        map[i].left = map[i].right = NOT_CONNECTED;
    }
    // init map connectivity
    for (int i = 0; i < N; ++i) {
        int connected_id = NOT_CONNECTED, dist = INT_MAX;
        for (int j = 0; j < N; ++j) {
            int dist_ij = hole[j].x - hole[i].x;
            if (0 < dist_ij && dist_ij < dist && hole[i].y == hole[j].y) {
                connected_id = j;
                dist = dist_ij;
            }
        }
        map[i].right = connected_id;
    }
    return connect(0);
}

int main(int argc, char const *argv[]) {
    ifstream fin("wormhole.in");
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> hole[i].x >> hole[i].y;
    }
    fin.close();

    ofstream fout("wormhole.out");
    fout << solve() << "\n";
    fout.close();

    return 0;
}
