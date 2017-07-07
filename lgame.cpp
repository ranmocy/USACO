/*
  PROG: lgame
  LANG: C++11
  ID: ranmocy1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <limits.h>
#define MAX_N 100
#define MIN_VALUE -100 // max is 7 * 7

const int value[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

const int get_value(const std::string & str) {
    int v = 0;
    for (std::string::const_iterator it=str.begin(); it!=str.end(); ++it) {
        v += value[*it - 'a'];
    }
    return v;
}

class Trie {
private:
    bool node_exist;
    Trie * nodes[26];
public:
    Trie() {
        node_exist = false;
        std::memset(nodes, 0, sizeof nodes);
    }

    int size() {
        int s = 1;
        for (int i = 0; i < 26; ++i) {
            if (nodes[i] != 0) {
                s += nodes[i]->size();
            }
        }
        return s;
    }

    void add(const std::string & str) {
        if (str.size() == 0) {
            node_exist = true;
            return;
        }
        int index = str[0] - 'a';
        if (nodes[index] == 0) {
            nodes[index] = new Trie();
        }
        std::string substr = str.substr(1);
        nodes[index]->add(substr);
    }

    bool exist(const std::string & str) {
        if (str.size() == 0) {
            return node_exist;
        }
        int index = str[0] - 'a';
        if (nodes[index] == 0) {
            return false;
        }
        std::string substr = str.substr(1);
        return nodes[index]->exist(substr);
    }
};


Trie trie;
std::string chars;
int max_value = 0;
std::set<std::string> set;


void update_value(const std::string & str, const int value) {
    if (value > max_value) {
        max_value = value;
        set = std::set<std::string>();
        set.insert(str);
        printf("%s, %d, %d\n", str.c_str(), value, max_value);
    } else if (value == max_value) {
        set.insert(str);
        printf("%s, %d, %d\n", str.c_str(), value, max_value);
    }
}

void order_chars(std::string & str) {
    int l = str.length(), v = get_value(str);
    do {
        if (trie.exist(str)) {
            update_value(str, v);
        }
        for (int i = 3; i <= l - 3; ++i) {
            std::string first = str.substr(0, i), second = str.substr(i);
            if (first.compare(second) < 0 && trie.exist(first) && trie.exist(second)) {
                str.insert(i, " ");
                update_value(str, v);
                str.erase(i, 1);
            }
        }
    } while ( std::next_permutation(str.begin(), str.end()) );
}

void pick_chars(const int index, const int n, std::string & current_str) {
    if (index >= n) {
        int l = current_str.length();
        if (l >= 3 && l <= 7) {
            order_chars(current_str);
        }
        return;
    }
    current_str.push_back(chars[index]);
    pick_chars(index+1, n, current_str);
    current_str.erase(current_str.size() - 1);
    pick_chars(index+1, n, current_str);
}

void solve() {
    std::string str;
    int n = chars.length();
    pick_chars(0, n, str);
}

int main(int argc, char const *argv[]) {
    std::ifstream fdict("lgame.dict");
    std::string t;
    int dict_size = 0;
    for (std::getline(fdict, t); t[0] != '.'; std::getline(fdict, t)) {
        trie.add(t);
        dict_size++;
    }
    fdict.close();
    printf("dict size:%d, trie size:%d\n", dict_size, trie.size());

    std::ifstream fin("lgame.in");
    fin >> chars;
    fin.close();
    std::sort(chars.begin(), chars.end());
    std::cout << chars << ", " << chars.length() << "\n";

    solve();

    std::ofstream fout("lgame.out");
    fout << max_value << "\n";
    for (std::set<std::string>::iterator it = set.begin(); it != set.end(); ++it) {
        fout << *it << "\n";
    }
    fout.close();
    return 0;
}
