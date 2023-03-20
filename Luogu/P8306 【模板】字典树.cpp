#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 1e5;
const int maxQ = 1e5;

int T;
int n, q;
chr s[maxN + 10];
chr t[maxN + 10];

struct TrieTree {
    struct Node {
        int val;
        int son[70];
    } node[maxN * 70 + 10];

    int root;
    int ncnt;

    int trans(char ch) {
        if ('0' <= ch && ch <= '9') return ch - '0' + 1;
        if ('A' <= ch && ch <= 'Z') return ch - 'A' + 1 + 10;
        if ('a' <= ch && ch <= 'z') return ch - 'a' + 1 + 10 + 26;
    }

    void Clear() {
        for (int i = 1; i <= ncnt; i++) {
            node[i].val = 0;
            std::memset(node[i].son, 0, sizeof(node[i].son));
        }
        ncnt = 1;
        return;
    }

    void Insert(chr *str) {
        int n = std::strlen(str + 1);
        int u = 1;
        for (int i = 1; i <= n; i++) {
            int ch = trans(str[i]);
            //printf("node[%d].val = %d\n", u, node[u].val);
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
            node[u].val++;
        }
        return;
    }

    int Query(chr *str) {
        int n = std::strlen(str + 1);
        int u = 1;
        for (int i = 1; i <= n; i++) {
            int ch = trans(str[i]);
            if (!node[u].son[ch]) return 0;
            u = node[u].son[ch];
            //printf("node[%d].val = %d\n", u, node[u].val);
        }
        return node[u].val;
    }
} TT;

void mian() {
    TT.Clear();
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> (s + 1), TT.Insert(s);
    for (int i = 1; i <= q; i++) std::cin >> (t + 1), std::cout << TT.Query(t) << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}