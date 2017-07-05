/*
  PROG: buylow
  LANG: C++
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits.h>
#define MAX_N 5001 // for additional 0 at the end of it

class big {
private:
    int l;
    int digits[200];
public:
    big() {
        assign(0);
    }

    // assign single digit
    void assign(int digit) {
        l = 1;
        digits[0] = digit;
    }

    void assign(big other) {
        l = other.l;
        for (int i = 0; i < l; ++i) {
            digits[i] = other.digits[i];
        }
    }

    void add(big other) {
        int t = 0;
        for (int i = 0; i < l || i < other.l || t != 0; ++i) {
            if (i < l) t += digits[i];
            if (i < other.l) t += other.digits[i];
            digits[i] = t % 10;
            t /= 10;
            l = std::max(l, i+1);
        }
    }

    bool isLarger(big other) {
        if (l != other.l) {
            return l > other.l;
        }
        for (int i = l-1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        return false;
    }

    void print(std::ostream *out) {
        for (int i = l-1; i >= 0; --i) {
            *out << digits[i];
        }
    }
};

std::ostream& operator<<(std::ostream& out, big &obj) {
    obj.print(&out);
    return out;
}

int n, price[MAX_N], length[MAX_N];
big count[MAX_N];


void solve() {
    int prev_count, prev_prices[n];
    for (int i = 0; i < n; ++i) {
        length[i] = 1;
        count[i].assign(1);
        prev_count = 0;
        for (int j = i-1; j >= 0; --j) {
            if (price[i] < price[j]) {
                if (length[j] + 1 > length[i]) {
                    length[i] = length[j] + 1;
                    count[i].assign(count[j]);
                    prev_count = 1;
                    prev_prices[0] = price[j];
                } else if (length[j] + 1 == length[i]) {
                    bool prev_exist = false;
                    for (int k = 0; k < prev_count; ++k) {
                        if (prev_prices[k] == price[j]) {
                            prev_exist = true;
                            break;
                        }
                    }
                    if (prev_exist) {
                        continue;
                    } else {
                        count[i].add(count[j]);
                        prev_prices[prev_count++] = price[j];
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    std::memset(length, 0, sizeof length);

    std::ifstream fin("buylow.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> price[i];
    }
    fin.close();

    price[n++] = 0;
    solve();

    std::ofstream fout("buylow.out");
    fout << length[n-1] - 1 << ' ' << count[n-1] << "\n";
    fout.close();
    return 0;
}
