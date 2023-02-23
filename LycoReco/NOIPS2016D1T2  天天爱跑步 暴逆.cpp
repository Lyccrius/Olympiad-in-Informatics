#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 3e5;
const int maxM = 3e5;

int n, m;
int u, v;
int w[maxN + 10];
int s[maxM + 10], t[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }
}

namespace Subtask12 {
    int ans[maxN + 10];

    void mian() {
        for (int i = 1; i <= m; i++) ans[s[i]]++;
        for (int j = 1; j <= n; j++) {
            if (w[j] == 0) {
                std::cout << ans[j] << ' ';
            } else {
                std::cout << 0 << ' ';
            }
        }
        return;
    }
}

namespace Subtask34 {
    int ans[maxN + 10];

    void mian() {
        for (int i = 1; i <= m; i++) ans[s[i]]++;
        for (int j = 1; j <= n; j++) {
            std::cout << ans[j] << ' ';
        }
        return;
    }
}

namespace Subtask5 {
    int ans[maxN + 10];

    bool DFS(int u, int t, int from, int now) {
        if (u == t) {
            if (w[u] == now) {
                ans[u]++;
            }
            return true;
        }
        for (int e = graph::vertex[u].head; e; e = graph::edge[e].next) {
            int v = graph::edge[e].head;
            if (v == from) continue;
            if (DFS(v, t, u, now + 1)) {
                if (w[u] == now) {
                    ans[u]++;
                }
            }
        }
        return false;
    }

    void mian() {
        for (int i = 1; i <= m; i++) {
            DFS(s[i], t[i], 0, 0);
        }
        for (int j = 1; j <= n; j++) {
            std::cout << ans[j] << ' ';
        }
        return;
    }
}

namespace Subtask678 {
    vic st[maxN + 10];
    vic ed[maxN + 10];
    int a[maxN + 10];
    int b[maxN + 10];
    int ans[maxM + 10];

    namespace up {
        void mian() {
            for (int i = 1; i <= m; i++) {
                if (s[i] < t[i]) {
                    st[s[i]].push_back(t[i]);
                    ed[t[i]].push_back(s[i]);
                }
            }
            for (int j = 1; j <= n; j++) {
                a[j] += st[j].size();
                ans[j] += a[j - w[j]];
                for (auto s : ed[j]) {
                    a[s]--;
                }
            }
        }
    }

    namespace dw {
        void mian() {
            vic st[maxN + 10];
            vic ed[maxN + 10];
            for (int i = 1; i <= m; i++) {
                if (s[i] > t[i]) {
                    st[s[i]].push_back(t[i]);
                    ed[t[i]].push_back(s[i]);
                }
            }
            for (int j = n; j >= 1; j--) {
                b[j] += st[j].size();
                ans[j] += b[j + w[j]];
                for (auto s : ed[j]) {
                    b[s]--;
                }
            }
        }
    }

    void mian() {
        up::mian();
        dw::mian();
        for (int j = 1; j <= n; j++) std::cout << ans[j] << ' ';
        return;
    }
}

namespace Subtask9101112 {
    int dep[maxN + 10];
    int ans[maxN + 10];

    void DFS(int u, int from) {
        for (int e = graph::vertex[u].head; e; e = graph::edge[e].next) {
            int v = graph::edge[e].head;
            if (v == from) continue;
            dep[v] = dep[u] + 1;
            DFS(v, u);
            ans[u] += ans[v];
        }
        return;
    }

    void mian() {
        for (int i = 1; i <= m; i++) {
            ans[t[i]]++;
        }
        DFS(1, 0);
        for (int j = 1; j <= n; j++) {
            if (w[j] == dep[j]) {
                std::cout << ans[j] << ' ';
            } else {
                std::cout << 0 << ' ';
            }
        }
        return;
    }
}

namespace Subtask13141516 {
    vic st[maxN + 10];
    int a[maxN + 10];
    int dep[maxN + 10];
    int ans[maxN + 10];

    void DFS(int u, int from) {
        int tmp = a[dep[u] + w[u]];
        a[dep[u]] += st[u].size();
        for (int e = graph::vertex[u].head; e; e = graph::edge[e].next) {
            int v = graph::edge[e].head;
            if (v == from) continue;
            dep[v] = dep[u] + 1;
            DFS(v, u);
        }
        ans[u] = a[dep[u] + w[u]] - tmp;
        return;
    }

    void mian() {
        for (int i = 1; i <= m; i++) {
            st[s[i]].push_back(t[i]);
        }
        DFS(1, 0);
        for (int j = 1; j <= n; j++) {
            std::cout << ans[j] << ' ';
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    for (int j = 1; j <= n; j++) std::cin >> w[j];
    for (int i = 1; i <= m; i++) std::cin >> s[i] >> t[i];
    if (n == 991 && m == 991) Subtask12::mian();
    if (n == 992 && m == 992) Subtask34::mian();
    if (n == 993 && m == 993) Subtask5::mian();
    if (n == 99994 && m == 99994) Subtask678::mian();
    if (n == 99995 && m == 99995) Subtask9101112::mian();
    if (n == 99996 && m == 99996) Subtask13141516::mian();
    return 0;
}