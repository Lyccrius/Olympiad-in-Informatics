#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 2e5;
const int maxQ = 2e5;
const int maxR = 2.5e4;
const int sqrN = 447;

int n, r, q;
int h[maxN + 10];
int s[maxN + 10];
int r1, r2;
int m;
vic a[maxR + 10];
int t[maxR + 10];
int p[maxR + 10];
int ans1[sqrN + 10][maxR + 10];
int ans2[maxR + 10][sqrN + 10];

namespace graph {
    struct Vertex {
        int head;
        int size;
        int dfn;
        int res;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN + 10];

    int ecnt;
    int dfn;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void DFS0(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].size = 1;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            DFS0(v);
            vertex[u].size += vertex[v].size;
        }
        return;
    }

    void DFS1(int u, int r1, int from) {
        vertex[u].res = vertex[from].res;
        if (h[u] == r1) {
            vertex[u].res++;
        } else {
            ans1[t[r1]][h[u]] += vertex[u].res;
        }
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            DFS1(v, r1, u);
        }
        return;
    }

    void DFS2(int u, int r2, int from) {
        vertex[u].res = 0;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            DFS2(v, r2, u);
            vertex[u].res += vertex[v].res;
        }
        if (h[u] == r2) {
            vertex[u].res++;
        } else {
            ans2[h[u]][t[r2]] += vertex[u].res;
        }
        return;
    }
}

struct Query {
    int pos;
    int val;

    bool operator<(const Query &other) const {
        if (pos != other.pos) return pos < other.pos;
        return val < other.val;
    }
};

std::vector<Query> query[maxR + 10];

void init(int r) {
    for (auto i : a[r]) query[r].push_back((Query) {graph::vertex[i].dfn, 1});
    for (auto i : a[r]) query[r].push_back((Query) {graph::vertex[i].dfn + graph::vertex[i].size, -1});
    std::sort(query[r].begin(), query[r].end());
    return;
}

int solve(int r1, int r2) {
    int ret = 0;
    int res = 0;
    int i = 0, j = 0;
    while (i < query[r1].size() && j < query[r2].size()) {
        if (query[r1][i].pos <= query[r2][j].pos) {
            res += query[r1][i].val;
            i++;
        } else {
            if (query[r2][j].val == 1) ret += res;
            j++;
        }
    }
    return ret;
}

int main() {
    std::cin >> n >> r >> q;
    std::cin >> h[1];
    for (int i = 2; i <= n; i++) {
        std::cin >> s[i] >> h[i];
        graph::addEdge(s[i], i);
    }
    graph::DFS0(1);
    for (int i = 1; i <= n; i++) a[h[i]].push_back(i);
    for (int i = 1; i <= r; i++) if (a[i].size() > sqrN) m++, t[i] = m, p[m] = i;
    for (int i = 1; i <= r; i++) if (a[i].size() <= sqrN) init(i);
    for (int i = 1; i <= m; i++) graph::DFS1(1, p[i], 0);
    for (int i = 1; i <= m; i++) graph::DFS2(1, p[i], 0);
    for (int i = 1; i <= q; i++) {
        std::cin >> r1 >> r2;
        if (a[r1].size() > sqrN) std::cout << ans1[t[r1]][r2] << '\n';
        else if (a[r2].size() > sqrN) std::cout << ans2[r1][t[r2]] << '\n';
        else std::cout << solve(r1, r2) << '\n';
        fflush(stdout);
    }
    return 0;
}