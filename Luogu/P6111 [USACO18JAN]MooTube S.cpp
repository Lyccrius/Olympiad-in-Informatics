#include <cstdio>
#include <algorithm>

const int maxN = 5000 + 10;
const int maxQ = 5000 + 10;

int N, Q;
struct Edge {
    int p, q, r;
    bool operator<(Edge other) const {
        return r > other.r;
    }
} edge[maxN];
struct Query {
    int id;
    int k, v;
    bool operator<(Query other) const {
        return k > other.k;
    }
} query[maxQ];

namespace MooTube {
    struct Node {
        int bel;
        int size;
    } node[maxN];

    void Init() {
        for (int i = 1; i <= N; i++) {
            node[i].bel = i;
            node[i].size = 1;
        }
    }

    int Query(int x) {
        if (node[x].bel == x) return x;
        return node[x].bel = Query(node[x].bel);
    }

    void Union(int x, int y) {
        x = Query(x);
        y = Query(y);
        if (node[x].bel == node[y].bel) return;
        if (node[x].size > node[y].size) std::swap(x, y);
        node[x].bel = y;
        node[y].size += node[x].size;
        return;
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i < N; i++) scanf("%d%d%d", &edge[i].p, &edge[i].q, &edge[i].r);
    for (int i = 1; i <= Q; i++) scanf("%d%d", &query[i].k, &query[i].v), query[i].id = i;
    std::sort(edge + 1, edge + N + 1);
    std::sort(query + 1, query + Q + 1);
    MooTube::Init();
    int ans[maxQ];
    int head = 1;
    for (int i = 1; i <= Q; i++) {
        while (head <= N && edge[head].r >= query[i].k) {
            MooTube::Union(edge[head].p, edge[head].q);
            head++;
        }
        int bel = MooTube::Query(query[i].v);
        ans[query[i].id] = MooTube::node[bel].size;
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i] - 1);
    return 0;
}