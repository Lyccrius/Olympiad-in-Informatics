#include <iostream>
#include <algorithm>
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
const int inf = 1e9 + 10;

int T;
int n;
int u[maxN + 10], v[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int size;
        int dep;
        int deg;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];
    
    int ecnt;

    void clear() {
        for (int i = 1; i <= maxN; i++) vertex[i].head = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].size = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].dep = 0;
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

    void DFS(int u, int from) {
        vertex[u].size = 1;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa = from;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        return;
    }
}

namespace Brute {
    bool is() {
        return n <= 1999;
    }

    int maxPart;
    int size[maxN + 10];
    int vis[maxN + 10];
    int res[maxN + 10];
    int cnt[maxN + 10];
    lxl ans;

    void init() {
        ans = 0;
        return;
    }

    void DFS(int u, int from, int tot) {
        using namespace graph;
        size[u] = 1;
        vis[u] = 1;
        res[u] = 0;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, tot);
            size[u] += size[v];
            res[u] = std::max(res[u], size[v]);
        }
        res[u] = std::max(res[u], tot - size[u]);
        //printf("res[%d] = %d\n", u, res[u]);
        maxPart = std::min(maxPart, res[u]);
        return;
    }

    void solve(int u, int v) {
        int tot;
        if (graph::vertex[u].dep > graph::vertex[v].dep) {
            tot = graph::vertex[u].size;
        } else {
            tot = n - graph::vertex[v].size;
        }
        //printf("solve %d[%d], %d[%d], tot = %d\n", u, graph::vertex[u].dep, v, graph::vertex[v].dep, tot);
        maxPart = inf;
        for (int i = 1; i <= n; i++) size[i] = 0;
        for (int i = 1; i <= n; i++) vis[i] = 0;
        for (int i = 1; i <= n; i++) res[i] = 0;
        DFS(u, v, tot);
        for (int i = 1; i <= n; i++) if (vis[i] && res[i] == maxPart) cnt[i]++;//, printf("%d is a focus, %d\n", i, res[i]);
        return;
    }

    void mian() {
        init();
        graph::DFS(1, 0);
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= n; j++) cnt[j] = 0;
            solve(u[i], v[i]);
            solve(v[i], u[i]);
            for (int i = 1; i <= n; i++) ans += cnt[i] * i;
        }
        std::cout << ans << '\n';
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

        void init() {
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
            init();
            int p;
            for (int i = 1; i <= n; i++) if (graph::vertex[i].deg == 1) p = i;
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

    namespace B {
        bool is() {
            return n == 262143;
        }

        int root;

        int cnt[maxN + 10];
        lxl ans;

        void init() {
            for (int i = 1; i <= n; i++) cnt[i] = 0;
            ans = 0;
            return;
        }

        void solve(int u, int fa) {
            if (fa != root) cnt[u]++;

        }

        void mian() {
            using namespace graph;
            init();
            for (int i = 1; i <= n; i++) if (vertex[i].deg == 2) root = i;
            DFS(root, 0);
            cnt[root] += (n + 1) / 2;
            for (int i = 1; i <= n; i++) {
                if (i == root) continue;
                //if (vertex[i].fa != root) 
                cnt[i]++;
            }
            for (int e = vertex[root].head; e; e = edge[e].next) {
                int v = edge[e].head;
                cnt[v] += vertex[v].size;
            }
            for (int i = 1; i <= n; i++) ans += 1ll * cnt[i] * i;//, printf("cnt[%d] = %d\n", i, cnt[i]);
            std::cout << ans << '\n';
            return;
        }
    }
}

void mian() {
    graph::clear();
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u[i] >> v[i];
        graph::addEdge(u[i], v[i]);
        graph::addEdge(v[i], u[i]);
    }
    if (Brute::is()) Brute::mian();
    else if (SubTask::A::is()) SubTask::A::mian();
    else if (SubTask::B::is()) SubTask::B::mian();
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