#include <iostream>
#include <algorithm>
#include <deque>

const int maxN = 1e5;
const int maxM = 1e5;
const int logN = 17;

int n, m;
int x, y;
int op;
int M;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int dfn;
        int top;
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

    int dfn;

    void DFS(int u, int from) {
        dfn++;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].dfn = dfn;
        vertex[u].top = dfn;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].top = std::max(vertex[u].top, vertex[v].top);
        }
        return;
    }
}

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT;

struct Event {
    int dep;
    int dfn;

    bool operator<(const Event &other) const {
        return dep > other.dep;
    }
};

struct Query {
    int i;
    int u;
    int dep;

    bool operator<(const Query &other) const {
        return dep > other.dep;
    }
};

std::deque<Event> events;
std::deque<Query> querys;

int maxDep;
int ans[maxM + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        std::cin >> x >> y;
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) events.push_back((Event) {graph::vertex[i].dep, graph::vertex[i].dfn});
    for (int i = 1; i <= n; i++) maxDep = std::max(maxDep, graph::vertex[i].dep); y = 0;
    for (int i = 1; i <= m; i++) {
        std::cin >> op >> x;
        if (op == 1) {
            y = x;
        } else {
            querys.push_back((Query) {++M, x, y});
        }
    }
    std::sort(events.begin(), events.end());
    std::sort(querys.begin(), querys.end());
    for (int i = maxDep; i >= 1; i--) {
        while (events.size() && events.front().dep > i) events.pop_front();
        while (events.size() && events.front().dep == i) {
            SGT.Modify(1, 1, n, events.front().dfn, 1);
            events.pop_front();
        }
        while (querys.size() && querys.front().dep > i) querys.pop_front();
        while (querys.size() && querys.front().dep == i) {
            ans[querys.front().i] = SGT.Query(1, 1, n, graph::vertex[querys.front().u].dfn, graph::vertex[querys.front().u].top);
            querys.pop_front();
        }
    }
    for (int i = 1; i <= M; i++) std::cout << ans[i] << '\n';
    return 0;
}