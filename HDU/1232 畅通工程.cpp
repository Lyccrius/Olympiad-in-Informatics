#include <iostream>

const int maxN = 1000;

int N, M;
int X, Y;

struct DisjointSetUnion {
    int node[maxN + 10];

    void Init() {
        for (int i = 1; i <= N; i++) node[i] = i;
        return;
    }

    int Find(int x) {
        if (node[x] == x) return x;
        return node[x] = Find(node[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x] = y;
        return;
    }
} DSU;

void mian() {
    std::cin >> M;
    DSU.Init();
    for (int i = 1; i <= M; i++) {
        std::cin >> X >> Y;
        DSU.Union(X, Y);
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (DSU.node[i] == i) {
            ans++;
        }
    }
    std::cout << ans - 1 << '\n';
    return;
}

int main() {
    while (std::cin >> N && N) mian();
    return 0;
}