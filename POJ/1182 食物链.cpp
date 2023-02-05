#include <iostream>
#include <cstdio>

const int maxN = 50000;
const int maxK = 100000;

int N, K;
int D, X, Y;
int cnt;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int dep;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= N; i++) {
            node[i].fa = i;
            node[i].dep = 0;
        }
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        int fx = node[x].fa;
        node[x].fa = Find(node[x].fa);
        node[x].dep += node[fx].dep;
        node[x].dep %= 3;
        return node[x].fa;
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        node[x].fa = y;
        //node[x].res = node[y].cnt;
        //node[y].cnt += node[x].cnt;
        return;
    }
} DSU;

int main() {
    //std::cin >> N >> K;
    scanf("%d%d", &N, &K);
    DSU.Init();
    while (K--) {
        scanf("%d%d%d", &D, &X, &Y);
        if (X > N || Y > N) {
            cnt++;
            continue;
        }
        if (D == 2 && X == Y) {
            cnt++;
            continue;
        }
        int fx = DSU.Find(X);
        int fy = DSU.Find(Y);
        if (fx == fy) {
            if ((DSU.node[X].dep - DSU.node[Y].dep + 3) % 3 != D - 1) cnt++;
        } else {
            DSU.node[fx].fa = fy;
            DSU.node[fx].dep = (DSU.node[Y].dep - DSU.node[X].dep + 3 + D - 1) % 3;
        }
    }
    std::cout << cnt;
    return 0;
}