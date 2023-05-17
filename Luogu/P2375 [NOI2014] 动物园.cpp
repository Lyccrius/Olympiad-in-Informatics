#include <iostream>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 5;
const int maxL = 1e6;
const int logL = 20;
const int mod = 1e9 + 7;

int n;
int l;
chr s[maxL + 10];

struct AhoCosarickAutomaton {
    struct Node {
        int son[30];
        int fail;
        int index;
        int head;
        int dep;
    } node[maxL + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxL + 10];

    int root;
    int ncnt;
    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = node[tail].head;
        node[tail].head = ecnt;
        return;
    }

    int shift(chr ch) {
        return ch - 'a' + 1;
    }

    struct SparseTable {
        struct Node {
            int f[logL + 5];
        } node[maxL + 10];

        void Init() {
            for (int i = 0; i <= maxL; i++) for (int p = 0; p <= logL; p++) node[i].f[p] = 0;
            return;
        }
    } ST;

    void Init() {
        ST.Init();
        for (int i = 0; i <= ncnt; i++) for (int j = 1; j <= 26; j++) node[i].son[j] = 0;
        for (int i = 0; i <= ncnt; i++) node[i].fail = 0;
        for (int i = 0; i <= ncnt; i++) node[i].head = 0;
        ncnt = 0;
        ecnt = 0;
        return;
    }

    void Insert(chr *s) {
        int u = root;
        for (int i = 1; s[i]; i++) {
            int ch = shift(s[i]);
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].index = true;
        return;
    }

    void Build() {
        diq q;
        for (int i = 1; i <= 26; i++) if (node[root].son[i]) q.push_back(node[root].son[i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int i = 1; i <= 26; i++) {
                if (node[u].son[i]) {
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    q.push_back(node[u].son[i]);
                } else {
                    node[u].son[i] = node[node[u].fail].son[i];
                }
            }
        }
        return;
    }

    void BuildFailTree() {
        for (int u = 1; u <= ncnt; u++) addEdge(node[u].fail, u);
        return;
    }

    void DFS(int u) {
        for (int p = 1; p <= logL; p++) ST.node[u].f[p] = ST.node[ST.node[u].f[p - 1]].f[p - 1];
        for (int e = node[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            node[v].dep = node[u].dep + 1;
            ST.node[v].f[0] = u;
            DFS(v);
        }
        return;
    }

    int Num(int u) {
        int v = u;
        for (int p = logL; p >= 0; p--) if (ST.node[v].f[p] > (u - 1) / 2) v = ST.node[v].f[p];
        if (v > u / 2) v = ST.node[v].f[0];
        return node[v].dep;
    }

    void Query(chr *s) {
        int res = 1;
        int u = root;
        for (int i = 1; s[i]; i++) {
            int ch = shift(s[i]);
            u = node[u].son[ch];
            res = 1ll * res * (Num(u) + 1) % mod;
        }
        std::cout << res << '\n';
        return;
    }
} ACM;

void mian() {
    std::cin >> (s + 1);
    ACM.Init(); 
    ACM.Insert(s);
    ACM.Build();
    ACM.BuildFailTree();
    ACM.DFS(0);
    ACM.Query(s);
    return;
}

int main() {
    std::cin >> n;
    while (n--) mian();
    return 0;
}