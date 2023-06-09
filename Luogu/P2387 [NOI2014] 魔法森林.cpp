#include <iostream>

const int maxN = 50000;
const int maxM = 100000;
const int minA = 1;
const int maxA = 50000;
const int minB = 1;
const int maxB = 50000;
const int inf = maxA + maxB + 10;

int n, m;
int x[maxM + 10], y[maxM + 10], a[maxM + 10], b[maxM + 10];
int ans = inf;
int A, B;

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        node[u].fa = v;
        return;
    }
} DSU;

bool check() {
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        if (a[i] > A) continue;
        if (b[i] > B) continue;
        DSU.Union(x[i], y[i]);
    }
    if (DSU.Find(1) == DSU.Find(n)) {
        ans = std::min(ans, A + B);
        return true;
    } else {
        return false;
    }
}

bool divideA() {
    int l = minA;
    int r = maxA;
    while (l < r) {
        int mid = (l + r) / 2;
        A = mid;
        if (check()) r = mid;
        else l = mid + 1;
    }
    for (int i = l; i <= r + 2; i++) {
        A = i;
        if (check()) return true;
    }
    return false;
}

void divideB() {
    int l = minB;
    int r = maxB;
    while (l < r) {
        int mid = (l + r) / 2;
        B = mid;
        if (divideA()) r = mid;
        else l = mid + 1;
    }
    for (int i = l; i <= r + 27; i++) {
        B = i;
        divideA();
    }
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> x[i] >> y[i] >> a[i] >> b[i];
    divideB();
    if (ans == inf) ans = -1;
    std::cout << ans << '\n';
    return 0;
}