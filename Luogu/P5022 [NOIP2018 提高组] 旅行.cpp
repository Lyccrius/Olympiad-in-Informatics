#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

typedef std::pair<int, int> pii;
typedef std::vector<pii> vpc;
typedef std::vector<int> vic;
typedef std::stack<int> sic;

const int maxN = 5000;
const int maxM = 5000;

int n, m;
int u, v;
vic res;
vic ans;

namespace graph {
    struct Vertex {
        int head;
        vic edge;
        int dfn;
        int low;
        int ins;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    namespace ring {
        int dfn;
        sic s;
        vpc r;

        void addSCC(int u) {
            int v;
            int w = u;
            do {
                if (s.empty()) return;
                v = s.top();
                s.pop();
                vertex[v].ins = false;
                if (v != w) r.push_back(std::make_pair(v, w));
                w = v;
            } while (v != u);
            return;
        }

        void Tarjan(int u, int from) {
            dfn++;
            vertex[u].dfn = dfn;
            vertex[u].low = dfn;
            vertex[u].ins = true;
            s.push(u);
            for (auto v : vertex[u].edge) {
                if (v == from) continue;
                if (!vertex[v].dfn) {
                    Tarjan(v, u);
                    vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                } else if (vertex[v].ins) {
                    vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
                }
            }
            if (vertex[u].dfn == vertex[u].low) addSCC(u);
            return;
        }

        bool check() {
            if (ans.empty()) return true;
            for (int i = 0; i < n; i++) {
                if (ans[i] < res[i]) return false;
                if (ans[i] > res[i]) return true;
            }
            return false;
        }

        void update() {
            ans.clear();
            for (int i = 0; i < n; i++) {
                ans.push_back(res[i]);
            }
            return;
        }

        void DFS(int u, int from, int fir, int sec) {
            res.push_back(u);
            for (auto v : vertex[u].edge) {
                if (v == from) continue;
                if (u == fir && v == sec) continue;
                if (u == sec && v == fir) continue;
                DFS(v, u, fir, sec);
            }
            return;
        }

        void mian() {
            Tarjan(1, 0);
            for (auto e : r) {
                res.clear();
                DFS(1, 0, e.first, e.second);
                if (check()) update();
            }
            return;
        }
    }

    namespace tree {
        void DFS(int u, int from) {
            ans.push_back(u);
            for (auto v : vertex[u].edge) {
                if (v == from) continue;
                DFS(v, u);
            }
            return;
        }
        
        void mian() {
            DFS(1, 0);
            return;
        }
    }

    void mian() {
        for (int u = 1; u <= n; u++) std::sort(vertex[u].edge.begin(), vertex[u].edge.end());
        if (n == m) ring::mian();
        if (n != m) tree::mian();
        for (auto u : ans) std::cout << u << ' ';
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        graph::vertex[u].edge.push_back(v);
        graph::vertex[v].edge.push_back(u);
    }
    graph::mian();
    return 0;
}