#include <iostream>

const int maxN = 400;
const int mod = 998244353;

int n, K;
int d[maxN + 10][maxN + 10];
int c[maxN + 10][maxN + 10];
int g[maxN + 10];
int f[maxN + 10];
int ans = 1;

bool check() {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (d[i][j] > K) return false;
    for (int i = 1; i <= n; i++) if (d[i][i] != 0) return false;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (d[i][j] != d[j][i]) return false;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) if (d[i][j] > d[i][k] + d[k][j]) return false;
    return true;
}

struct DisjiontSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
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
        node[v].size += node[u].size;
        return;
    }
} DSU;

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> n >> K;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> d[i][j];
        }
    }
    if (!check()) {
        std::cout << 0 << '\n';
        return 0;
    }
    DSU.Init();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == 0) {
                DSU.Union(i, j);
                break;
            }
        }
    }
    //for (int i = 1; i <= n; i++) if (DSU.Find(i) == i) printf("%d, %d\n", i, DSU.node[i].size);
    for (int i = 1; i <= n; i++) {
        if (DSU.Find(i) != i) continue;
        for (int j = i + 1; j <= n; j++) {
            if (DSU.Find(j) != j) continue;
            bool flag = false;
            for (int k = 1; k <= n; k++) {
                if (DSU.Find(k) != k) continue;
                if (i == k) continue;
                if (j == k) continue;
                if (d[i][j] == d[i][k] + d[k][j]) flag = true;
            }
            if (flag) {
                ans = 1ll * ans * pow(K - d[i][j] + 1, DSU.node[i].size * DSU.node[j].size) % mod;
            } else {
                ans = 1ll * ans * (pow(K - d[i][j] + 1, DSU.node[i].size * DSU.node[j].size) - pow(K - d[i][j], DSU.node[i].size * DSU.node[j].size)) % mod;
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        g[i] = pow(K + 1, i * (i - 1) / 2);
        f[i] = g[i];
        for (int j = 1; j < i; j++) f[i] = (f[i] - 1ll * f[j] * g[i - j] % mod * pow(K, j * (i - j)) % mod * c[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i <= n; i++) {
        if (DSU.Find(i) != i) continue;
        ans = 1ll * ans * f[DSU.node[i].size] % mod;
    }
    std::cout << (ans + mod) % mod << '\n';
    return 0;
}