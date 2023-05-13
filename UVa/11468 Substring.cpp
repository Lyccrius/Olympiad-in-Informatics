#include <iostream>
#include <iomanip>
#include <deque>
#include <cstring>

typedef char chr;
typedef double dbl;
typedef std::deque<int> diq;

const int maxT = 50;
const int maxK = 20;
const int maxS = 20; 
const int maxL = 100;

int t;
int kase;
int k;
chr s[maxS + 10];
int n;
chr ch;
dbl p[70];
int l;

int shift(chr ch) {
    if ('A' <= ch && ch <= 'Z') return ch - 'A';
    if ('a' <= ch && ch <= 'z') return ch - 'a' + 26;
    return ch - '0' + 52;
}

struct AhoCosarickAutomaton {
    struct Node {
        int son[70];
        int fail;
        int index;
        int vis[maxL + 10];
        dbl res[maxL + 10];
    } node[maxK * maxS + 10];

    int ncnt;
    int root;

    void Init() {
        for (int i = 0; i <= ncnt; i++) {
            for (int j = 0; j < 62; j++) {
                node[i].son[j] = 0;
            }
            node[i].fail = 0;
            node[i].index = 0;
            for (int j = 0; j <= l; j++) {
                node[i].vis[j] = 0;
                node[i].res[j] = 0;
            }
        }
        ncnt = 0;
        return;
    }

    void Insert(chr *str, int n) {
        int u = root;
        for (int i = 1; i <= n; i++) {
            int ch = shift(str[i]);
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].index = true;
        return;
    }

    void Build() {
        diq q;
        for (int j = 0; j < 62; j++) {
            if (node[root].son[j]) {
                q.push_back(node[root].son[j]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int j = 0; j < 62; j++) {
                if (node[u].son[j]) {
                    node[node[u].son[j]].fail = node[node[u].fail].son[j];
                    node[node[u].son[j]].index |= node[node[node[u].fail].son[j]].index;
                    q.push_back(node[u].son[j]);
                } else {
                    node[u].son[j] = node[node[u].fail].son[j];
                }
            }
        }
        return;
    }

    dbl DFS(int u, int l) {
        //printf("DFS(%d, %d)\n", u, l);
        if (!l) return 1.0;
        if (node[u].index) return 0.0;
        if (node[u].vis[l]) return node[u].res[l];
        node[u].vis[l] = true;
        for (int j = 0; j < 62; j++) {
            //if (node[u].son[j] == 0) continue;
            if (node[node[u].son[j]].index) continue;
            node[u].res[l] += p[j] * DFS(node[u].son[j], l - 1);
        }
        //printf("DFS(%d, %d) = %lf\n", u, l, node[u].res[l]);
        return node[u].res[l];
    }
} ACM;

void init() {
    for (int i = 0; i < 62; i++) p[i] = 0;
    ACM.Init();
    return;
}

void mian() {
    init();
    std::cin >> k;
    for (int i = 1; i <= k; i++) {
        std::cin >> (s + 1);
        ACM.Insert(s, strlen(s + 1));
    }
    ACM.Build();
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> ch >> p[68];
        p[shift(ch)] = p[68];
    }
    std::cin >> l;
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << "Case #" << kase << ": " << std::setprecision(6) << ACM.DFS(ACM.root, l) << '\n';
    return;
}

int main() {
    std::cin >> t;
    for (kase = 1; kase <= t; kase++) mian();
    return 0;
}