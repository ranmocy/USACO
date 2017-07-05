/*
  PROG: job
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <limits.h>
#define MAX_N 1000
#define MAX_M 30

int n, // number of jobs
    na, // number of A machines
    nb, // number of B machines
    ma[MAX_M], // job time for A machines
    mb[MAX_M], // job time for B machines
    job_a[MAX_N], // minimal finishing time of job[i] to finish task A
    job_b[MAX_N], // minimal finishing time of job[i] to finish task B
    max_a = 0, max_b = 0;

void process(int machines, int cost[], int job_time[]) {
    int availability[machines];
    std::memset(availability, 0, sizeof availability);

    for (int job = 0; job < n; ++job) {
        // find the earliest finishing time of the job
        int min_time = INT_MAX, min_index = -1;
        for (int i = 0; i < machines; ++i) {
            int finish_time = availability[i] + cost[i];
            if (finish_time < min_time) {
                min_time = finish_time;
                min_index = i;
            }
        }
        availability[min_index] = min_time;
        job_time[job] = min_time;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", job_time[i]);
    }
    printf("\n");
}

void solve() {
    process(na, ma, job_a);
    process(nb, mb, job_b);
    for (int i = 0; i < n; ++i) {
        max_a = std::max(max_a, job_a[i]);
        max_b = std::max(max_b, job_a[n - 1 - i] + job_b[i]);
    }
}

int main(int argc, char const *argv[]) {
    std::memset(job_a, 0, sizeof job_a);
    std::memset(job_b, 0, sizeof job_b);

    std::ifstream fin("job.in");
    fin >> n >> na >> nb;
    for (int i = 0; i < na; ++i) {
        fin >> ma[i];
    }
    for (int i = 0; i < nb; ++i) {
        fin >> mb[i];
    }
    fin.close();

    solve();

    std::ofstream fout("job.out");
    fout << max_a << ' ' << max_b << "\n";
    fout.close();
    return 0;
}
