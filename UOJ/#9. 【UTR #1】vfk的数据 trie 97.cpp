#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <cstring>

typedef char chr;
typedef std::string str;
typedef std::deque<int> diq;
typedef std::map<chr, int> mci;

const int maxN = 10000;
const int maxM = 100;
const chr ind[70] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_0123456789.";
mci din;
int n;
chr s[maxN + 10][maxM + 10];
str t;
str p;

int c2i(chr ch) {
    //printf("%c to %d\n", ch, din[ch]);
    return din[ch];
}

struct TrieTree {
    struct Node {
        int son[70];
        int end;
        str s;
    } node[maxN * 70 + 10];

    int ncnt;

    void Insert(chr *s) {
        int u = 0;
        for (int i = 1; isdigit(s[i]); i++) {
            if (node[u].son[c2i(s[i])] == 0) {
                node[u].son[c2i(s[i])] = ++ncnt;
                node[node[u].son[c2i(s[i])]].s = node[u].s + s[i];
            }
            u = node[u].son[c2i(s[i])];
            //printf("u = %d\n", u);
        }
        node[u].end = true;
        //printf("inserted %s at %d\n", s + 1, u);
        return;
    }

    void BFS() {
        diq q;
        q.push_back(0);
        while (!q.empty()) {
            int u = q.front();
            //printf("BFS %d\n", u);
            q.pop_front();
            if (node[u].end) {
                std::cout << p << node[u].s << ".in" << '\n';
            }
            for (int i = 0; ind[i]; i++) {
                if (node[u].son[i]) {
                    q.push_back(node[u].son[i]);
                    //printf("push %c, %d\n", node[u].son[i]);
                }
            }
        }
        return;
    }
} TT;

int main() {
    for (int i = 0; ind[i]; i++) din[ind[i]] = i;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> (s[i] + 1);
    int m = strlen(s[1] + 1) - 3;
    while (m > 0 && isdigit(s[1][m])) m--;
    for (int i = 1; i <= m; i++) p.push_back(s[1][i]); //std::cout << p << '\n';
    for (int i = 1; i <= n; i++) TT.Insert(s[i] + m);
    TT.BFS();
    return 0;
}