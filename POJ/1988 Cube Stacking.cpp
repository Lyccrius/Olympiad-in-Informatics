#include <iostream>

const int maxN = 30000;
const int maxP = 100000;

int N, P;
char op;
int X, Y;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int cnt;
        int res;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= maxN; i++) {
            node[i].fa = i;
            node[i].cnt = 1;
            node[i].res = 0;
        }
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        int fx = node[x].fa;
        node[x].fa = Find(node[x].fa);
        node[x].res += node[fx].res;
        return node[x].fa;
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        node[x].fa = y;
        node[x].res = node[y].cnt;
        node[y].cnt += node[x].cnt;
        return;
    }
} DSU;

int main() {
    DSU.Init();
    std::cin >> P;
    while (P--) {
        std::cin >> op;
        if (op == 'M') {
            std::cin >> X >> Y;
            DSU.Union(X, Y);
        } else {
            std::cin >> X;
            DSU.Find(X);
            std::cout << DSU.node[X].res << '\n';
        }
    }
    return 0;
}