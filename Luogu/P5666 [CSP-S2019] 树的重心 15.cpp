#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 3e5;

int T;
int n;
int u[maxN + 10], v[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int deg;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];
    
    int ecnt;

    void clear() {
        for (int i = 1; i <= maxN; i++) vertex[i].head = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].deg = 0;
        ecnt = 0;
        return;
    }

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[tail].deg++;
        return;
    }
}

namespace SubTask {
    namespace A {
        bool is() {
            return n == 49991;
        }

        vic a;
        vic b;

        void clear() {
            a.clear();
            b.clear();
            return;
        }

        void DFS(int u, int from) {
            using namespace graph;
            a.push_back(u);
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                DFS(v, u);
            }
            return;
        }

        void mian() {
            using namespace graph;
            int p;
            for (int i = 1; i <= n; i++) if (vertex[i].deg == 1) p = i;
            DFS(p, 0);
            b.push_back(2);
            for (int i = 1; i <= (n - 3) / 2; i++) b.push_back(3);
            b.push_back(2);
            for (int i = 1; i <= (n - 3) / 2; i++) b.push_back(3);
            b.push_back(2);
            lxl ans = 0;
            for (int i = 0; i < n; i++) ans += 1ll * a[i] * b[i];
            std::cout << ans << '\n';
            return;
        }
    }
}

void init() {
    graph::clear();
    SubTask::A::clear();
    return;
}

void mian() {
    init();
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u[i] >> v[i];
        graph::addEdge(u[i], v[i]);
        graph::addEdge(v[i], u[i]);
    }
    if (SubTask::A::is()) SubTask::A::mian();
    return;
}

int main() {
    //freopen("centroid.in", "r", stdin);
    //freopen("centroid.out", "w", stdout);
    promote();
    std::cin >> T;
    while (T--) mian();
    return 0;
}