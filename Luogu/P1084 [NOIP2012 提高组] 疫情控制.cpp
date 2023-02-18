#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 5e4;
const int maxM = 5e4;
const int logN = 16;
const int inf = 1e9;

int n;
int u, v, w;
int m;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int choice;
        int remain;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    struct SparseTable {
        struct Node {
            int f;
            int d;
        } node[maxN + 10][logN + 5];
    } ST;

    struct Army {
        int pos;
        int vis;
    } army[maxM + 10];

    struct Node {
        int number;
        int remain;

        bool operator<(const Node &other) const {
            return remain > other.remain;
        }
    };

    std::vector<Node> free;
    std::vector<Node> need;

    void DFS4Init(int u, int from) {
        for (int p = 1; p <= logN; p++) {
            ST.node[u][p].f = ST.node[ST.node[u][p - 1].f][p - 1].f;
            ST.node[u][p].d = ST.node[ST.node[u][p - 1].f][p - 1].d + ST.node[u][p - 1].d;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            ST.node[v][0].f = u;
            ST.node[v][0].d = w;
            DFS4Init(v, u);
        }
        return;
    }

    bool DFS4Check(int u, int from) {
        bool ret = true;
        bool isLeaf = true;
        if (vertex[u].vis) return true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            isLeaf = false;
            if (!DFS4Check(v, u)) {
                ret = false;
                if (u == 1) need.push_back((Node) {v, w});
                else return false;
            }
        }
        if (isLeaf) return false;
        return ret;
    }

    void init() {
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        for (int i = 1; i <= n; i++) vertex[i].choice = false;
        for (int i = 1; i <= m; i++) army[i].vis = false;
        free.clear();
        need.clear();
        return;
    }

    void pushUp(int &u, int &t, int x) {
        for (int p = logN; p >= 0; p--) {
            if (ST.node[u][p].f > 1 && ST.node[u][p].d + t <= x) {
                t += ST.node[u][p].d;
                u = ST.node[u][p].f;
            }
        }
        return;
    }

    void handle(int u, int t, int x, int i) {
        if (ST.node[u][0].f == 1 && ST.node[u][0].d + t <= x) {
            free.push_back((Node) {i, x - t - ST.node[u][0].d});
            if (vertex[u].remain > free.back().remain || !vertex[u].choice) {
                vertex[u].remain = free.back().remain;
                vertex[u].choice = i;
            }
        } else {
            vertex[u].vis = true;
        }
        return;
    }

    bool transfer() {
        std::sort(free.begin(), free.end());
        std::sort(need.begin(), need.end());
        int cur = 0;
        for (int i = 0; i < need.size(); i++) {
            if (!army[vertex[need[i].number].choice].vis) {
                army[vertex[need[i].number].choice].vis = true;
                continue;
            }
            while (cur < free.size() && army[free[cur].number].vis) cur++;
            if (cur >= free.size() || free[cur].remain < need[i].remain) return false;
            army[free[cur].number].vis = true;
        }
        return true;
    }

    bool check(int x) {
        init();
        for (int i = 1; i <= m; i++) {
            int u = army[i].pos;
            int t = 0;
            pushUp(u, t, x);
            handle(u, t, x, i);
        }
        if (DFS4Check(1, 0)) return true;
        return transfer();
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }
    graph::DFS4Init(1, 0);
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> graph::army[i].pos;
    int l = 0;
    int r = 5e5;
    while (l < r) {
        int mid = (l + r) / 2;
        if (graph::check(mid)) r = mid;
        else l = mid + 1;
    }
    std::cout << l;
    return 0;
}