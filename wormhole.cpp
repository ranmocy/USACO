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

struct hole_pos
{
    int x, y;
};

struct hole_connection
{
    // destination(hole id) when enter from left, or exit from right
    int left, right;
};

int i, j, N, result = 0;
struct hole_pos hole[MAX_N];
struct hole_connection map[MAX_N];
bool visited[MAX_N];

// dfs the map from SOURCE_ID, and we reach SOURCE_ID via hole if VIA_HOLE is true, via map otherwise.
// if it reach a visited hole, there is a loop
// via_map and via_hole should appear alternately
// e.x. some_point =via_map=> A =via_hole=> B =via_map=> C =via_hole=> D =via_map=> A
bool dfs(int source_id, bool via_map)
{
    visited[source_id] = via_map;
    for (int target_id = 0; target_id < N; ++target_id)
    {
        if (target_id != source_id
            && ((!via_map && map[source_id].right == target_id)
                || (via_map && map[source_id].left == target_id)))
        {
            if ((!via_map && visited[target_id]) || dfs(target_id, !via_map))
            {
                return true;
            }
        }
    }
    visited[source_id] = false;
    return false;
}

// test if there is a loop. If so, result++;
void test()
{
    for (int i = 0; i < N; ++i)
    {
        visited[i] = false;
    }
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i] && dfs(i, true))
        {
            result++;
            return;
        }
    }
}

// enumerate all the possiblility of connections
void connect(int source_id)
{
    // skip those connected holes
    while (source_id < N && map[source_id].left != NOT_CONNECTED) {
        source_id++;
    }

    // if it's the last one
    if (source_id >= N)
    {
        test();
        return;
    }

    // otherwise, connect it with another one
    for (int target_id = source_id + 1; target_id < N; ++target_id)
    {
        if (map[target_id].left == NOT_CONNECTED)
        {
            map[source_id].left = target_id;
            map[target_id].left = source_id;
            connect(source_id + 1);
            map[source_id].left = NOT_CONNECTED;
            map[target_id].left = NOT_CONNECTED;
        }
    }
}

int main(int argc, char const *argv[])
{
    {
        ifstream fin("wormhole.in");
        fin >> N;
        for (int i = 0; i < N; ++i)
        {
            fin >> hole[i].x >> hole[i].y;
        }
        fin.close();
    }

    {
        for (int i = 0; i < N; ++i)
        {
            map[i].left = map[i].right = NOT_CONNECTED;
        }
        // init map connectivity
        for (int i = 0; i < N; ++i)
        {
            int connected_id = NOT_CONNECTED, dist = INT_MAX;
            for (int j = 0; j < N; ++j)
            {
                if (i != j && hole[i].y == hole[j].y)
                {
                    int dist_ij = hole[j].x - hole[i].x;
                    if (0 < dist_ij && dist_ij < dist)
                    {
                        connected_id = j;
                        dist = dist_ij;
                    }
                }
            }
            map[i].right = connected_id;
        }
        connect(0);
    }

    {
        ofstream fout("wormhole.out");
        fout << result << "\n";
        fout.close();
    }

    return 0;
}
