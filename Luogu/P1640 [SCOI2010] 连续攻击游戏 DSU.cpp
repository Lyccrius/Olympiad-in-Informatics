#include <iostream>

const int maxN = 1e6;
const int maxA = 1e4;

int N;
int a, b;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int vis;
    } node[maxA + 10];

    void Init() {
        for (int i = 1; i <= maxA; i++) {
            node[i].fa = i;
        }
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) {
            node[x].vis = true;
            return;
        }
        if (x > y) std::swap(x, y);
        node[x].fa = y;
        node[x].vis = true;
        return;
    }
} DSU;

int main() {
    DSU.Init();
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> a >> b;
        DSU.Union(a, b);
    }
    for (int i = 1; i <= maxA; i++) {
        if (!DSU.node[i].vis) {
            std::cout << i - 1;
            return 0;
        }
    }
    std::cout << maxA;
    return 0;
}