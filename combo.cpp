/*
  PROG: combo
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define DIGITS 3
#define TOLERANCE 2

int N, result = 0, lock1[DIGITS], lock2[DIGITS];

int combination(int range[DIGITS])
{
    int total = range[0];
    for (int i = 1; i < DIGITS; ++i)
    {
        total *= range[i];
    }
    return total;
}

int real_pos(int i) {
    return (i + N - 1) % N + 1;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int range_upper_limit(int pos) {
    return pos - TOLERANCE - 1 + min(TOLERANCE * 2 + 1, N);
}

int main(int argc, char const *argv[])
{
    {
        ifstream fin("combo.in");
        fin >> N;
        for (int i = 0; i < DIGITS; ++i)
        {
            fin >> lock1[i];
        }
        for (int i = 0; i < DIGITS; ++i)
        {
            fin >> lock2[i];
        }
        fin.close();
    }

    {
        int range[DIGITS];
        for (int i = 0; i < DIGITS; ++i)
        {
            range[i] = min(TOLERANCE * 2 + 1, N);
        }
        result += combination(range) * 2;

        for (int i = 0; i < DIGITS; ++i)
        {
            int count = 0;
            for (int a = lock1[i] - TOLERANCE; a <= range_upper_limit(lock1[i]); ++a)
            {
                int real_a = real_pos(a);
                for (int b = lock2[i] - TOLERANCE; b <= range_upper_limit(lock2[i]); ++b)
                {
                    int real_b = real_pos(b);
                    if (real_a == real_b)
                    {
                        count++;
                    }
                }
            }
            range[i] = count;
        }
        result -= combination(range);
    }

    {
        ofstream fout("combo.out");
        fout << result << "\n";
        fout.close();
    }

    return 0;
}
