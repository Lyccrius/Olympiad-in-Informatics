#include <iostream>
#include <vector>
#include <deque>

typedef long long lxl;

typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 500;
const int maxM = 1e3;

int kase;
int n, m;
int s, t;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int bel;
    } vertex[maxM + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;
    diq s;

    struct VBCC {
        vic q;
        int cnt;
    } vbcc[maxM + 10];
    
    int bcnt;

    void init() {
        for (int i = 1; i <= m; i++) vertex[i].head = 0;
        for (int i = 1; i <= m; i++) vertex[i].bel = 0;
        for (int i = 1; i <= m; i++) vertex[i].dfn = 0;
        for (int i = 1; i <= m; i++) vertex[i].low = 0;
        for (int i = 1; i <= bcnt; i++) vbcc[i].q.clear();
        for (int i = 1; i <= bcnt; i++) vbcc[i].cnt = 0;
        ecnt = 0;
        bcnt = 0;
        dfn = 0;
        m = 0;
        s.clear();
        return;
    }

    void addVBCC(int u) {
        int v;
        bcnt++;
        vbcc[bcnt].q.clear();
        do {
            v = s.back();
            s.pop_back();
            vbcc[bcnt].q.push_back(v);
            vertex[v].bel++;
        } while (v != u);
        return;
    }

    void Tarjan(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        s.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                Tarjan(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[v].low >= vertex[u].dfn) {
                    s.push_back(u);
                    addVBCC(v);
                }
            } else {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        return;
    }

    void solve() {
        lxl ans = 0;
        lxl cnt = 1;
        for (int i = 1; i <= bcnt; i++) for (auto u : vbcc[i].q) if (vertex[u].bel > 1) vbcc[i].cnt++;
        for (int i = 1; i <= bcnt; i++) {
            if (vbcc[i].cnt == 0) {
                ans += 2;
                if (vbcc[i].q.size() > 1) {
                    cnt *= 1ll * vbcc[i].q.size() * (vbcc[i].q.size() - 1) /2;
                }
            } else if (vbcc[i].cnt == 1) {
                ans += 1;
                if (vbcc[i].q.size() > 1) {
                    cnt *= vbcc[i].q.size() - 1;
                }
            }
        }
        std::cout << ans << ' ' << cnt << '\n';
        return;
    }
}

void mian() {
    graph::init();
    for (int i = 1; i <= n; i++) std::cin >> s >> t, graph::addEdge(s, t), graph::addEdge(t, s), m = std::max(m, s), m = std::max(m, t);
    for (int i = 1; i <= m; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i, 0);
    std::cout << "Case " << ++kase << ": ";
    graph::solve();
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}