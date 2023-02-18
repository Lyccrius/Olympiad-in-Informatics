#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}

const int maxN = 2e4;
const int maxM = 1e5;

int N, M;

struct Node {
    int a, b, c;

    bool operator<(const Node &other) const {
        return c < other.c;
    }
} node[maxM + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN * 2 + 10];

    void Init() {
        for (int i = 1; i <= N + N; i++) node[i].fa = i;
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x].fa = y;
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) std::cin >> node[i].a >> node[i].b >> node[i].c;
    std::sort(node + 1, node + M + 1);
    DSU.Init();
    for (int i = M; i >= 0; i--) {
        int a = node[i].a;
        int b = node[i].b;
        int fa = DSU.Find(a);
        int fb = DSU.Find(b);
        if (fa == fb) {
            std::cout << node[i].c;
            return 0;
        }
        DSU.Union(a, b + N);
        DSU.Union(a + N, b);
    }
    return 0;
}