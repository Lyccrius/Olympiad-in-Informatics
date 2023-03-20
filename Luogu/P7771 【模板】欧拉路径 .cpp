#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> dic;

const int maxN = 1e5;
const int maxM = 2e5;

int n, m;
int u, v;
int s, t;
int cnt;
dic ans;

namespace graph {
    struct Edge {
        int to;
        int e;

        bool operator<(const Edge &other) const {
            return to < other.to;
        }
    };

    int ecnt;
    int vis[maxM + 10];

    struct Vertex {
        int ideg;
        int odeg;
        int vis;
        dic edge;
    } vertex[maxN + 10];

    void addEdge(int tail, int head) {
        ecnt++;
        //vertex[tail].edge.push_back((Edge) {head, ecnt});
        vertex[tail].edge.push_back(head);
        vertex[tail].odeg++;
        vertex[head].ideg++;
        return;
    }

    void DFS(int u) {
        //printf("DFS(%d)\n", u);
        //std::cout << u << ' ';
        while (vertex[u].edge.size()) {
            //int v = vertex[u].edge.front().to;
            //int e = vertex[u].edge.front().e;
            int v = vertex[u].edge.front();
            vertex[u].edge.pop_front();
            //if (vis[e]) continue;
            //vis[e] = true;
            DFS(v);
        }
        ans.push_back(u);
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, v);
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].ideg != graph::vertex[i].odeg) {
            if (graph::vertex[i].ideg == graph::vertex[i].odeg - 1) s = i;
            if (graph::vertex[i].ideg == graph::vertex[i].odeg + 1) t = i;
            cnt++;
        }
    }
    if (cnt == 0) {
        s = 1;
        t = 1;
    }
    if (cnt != 0 && cnt != 2) {
        std::cout << "No" << '\n';
        return 0;
    }
    if (s == 0 || t == 0) {
        std::cout << "No" << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) std::sort(graph::vertex[i].edge.begin(), graph::vertex[i].edge.end());
    graph::DFS(s);
    while (ans.size()) {
        std::cout << ans.back() << ' ';
        ans.pop_back();
    }
    return 0;
}