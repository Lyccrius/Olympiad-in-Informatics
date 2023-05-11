#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 300000;
const int maxS = 4000;
const int maxM = 100;
const int mod = 20071027;

chr a[maxN + 10];
chr b[maxM + 10];
int f[maxN + 10];
int s;
int n;
int kase;

struct TrieTree {
    struct Node {
        int son[30];
        int end;
    } node[maxS * maxM + 10];

    int ncnt;
    int root;

    void Init() {
        for (int i = 0; i <= ncnt; i++) node[i].end = false;
        for (int i = 0; i <= ncnt; i++) {
            for (int j = 0; j <= 26; j++) {
                node[i].son[j] = 0;
            }
        }
        return;
    }

    void Insert(chr *str) {
        int u = root;
        for (int i = 0; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].end = true;
        return;
    }

    void Query(chr *str, int p) {
        int u = root;
        for (int i = 0; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            if (node[u].son[ch] == 0) return;
            u = node[u].son[ch];
            if (node[u].end) {
                f[p] = (f[p] + f[p + i + 1]) % mod;
            }
        }
        return;
    }
} TT;

void mian() {
    TT.Init();
    std::cin >> s;
    for (int i = 1; i <= s; i++) {
        std::cin >> b;
        TT.Insert(b);
    }
    n = strlen(a);
    for (int i = 0; i <= n; i++) f[i] = 0;
    f[n] = 1;
    for (int i = n - 1; i >= 0; i--) TT.Query(a + i, i);
    //if (kase) std::cout << '\n';
    std::cout << "Case " << ++kase << ": " << f[0] << '\n';
    return;
}

int main() {
    while (scanf("%s", a) != EOF) mian();
    return 0;
}