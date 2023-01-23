#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

typedef std::pair<int, int> pii;

bool cmp(pii a, pii b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

const int maxN = 150;
const int maxM = 5000;

int n, m;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int low;
        int dfn;
        int bel;
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

    int cnt;
    std::stack<int> s;
    std::vector<pii> ans;

    int ebcccnt;

    void addEBCC(int u) {
        ebcccnt++;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[v].bel = ebcccnt;
        } while (v != u);
    }

    void DFS(int u, int from) {
        cnt++;
        vertex[u].dfn = cnt;
        vertex[u].low = cnt;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                DFS(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[v].low > vertex[u].dfn) ans.push_back(std::make_pair(std::min(u, v), std::max(u, v)));
            } else vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        if (vertex[u].low == vertex[u].dfn) addEBCC(u);
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a >> b, graph::addEdge(a, b), graph::addEdge(b, a);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::DFS(i, 0);
    std::sort(graph::ans.begin(), graph::ans.end(), cmp);
    for (auto i : graph::ans) std::cout << i.first << ' ' << i.second << '\n';
    return 0;
}