#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 50;
const int maxM = 501;
const int maxK = 200;
const int maxT = 1e9;
const int maxW = 5;
const int maxC = 52501;
const int maxY = 1e9;
const int logT = 30;
const lxl inf = 1ll * maxT * maxC + 1ll * maxK * maxY;

int n, m, T, k;
int c[maxN + 10];
int u[maxM + 10], v[maxM + 10], w[maxM + 10];

struct Festival {
    int t, x, y;

    bool operator<(const Festival &other) const {
        return t < other.t;
    }
} f[maxK + 10];

struct Matrix {
    int n, m;
    lxl a[maxW * maxN + 10][maxW * maxN + 10];

    Matrix() {
        std::fill(a[0], a[0] + sizeof(a) / 8, -inf);
        return;
    }

    Matrix operator*(const Matrix &other) {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        for (int i = 1; i <= ret.n; i++) {
            for (int j = 1; j <= ret.m; j++) {
                for (int k = 1; k <= m; k++) {
                    ret.a[i][j] = std::max(ret.a[i][j], a[i][k] + other.a[k][j]);
                }
            }
        }
        return ret;
    }
} G[logT + 5];

struct Vector {
    int n;
    lxl a[maxW * maxN + 10];

    Vector() {
        std::fill(a, a + sizeof(a) / 8, -inf);
        return;
    }

    Vector operator*(Matrix other) {
        Vector ret;
        ret.n = n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ret.a[j] = std::max(ret.a[j], a[i] + other.a[i][j]);
            }
        }
        return ret;
    }
} A;

void addEdge(int u, int v, int w) {
    for (int i = 1; i < w; i++) G[0].a[(i - 1) * n + u][i * n + u] = 0;
    G[0].a[(w - 1) * n + u][v] = c[v];
    return;
}

int main() {
    std::cin >> n >> m >> T >> k;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i] >> w[i], addEdge(u[i], v[i], w[i]);
    for (int i = 1; i <= k; i++) std::cin >> f[i].t >> f[i].x >> f[i].y;
    f[++k].t = T;
    std::sort(f + 1, f + k + 1);
    A.n = G[0].n = G[0].m = 5 * n;
    A.a[1] = c[1];
    for (int i = 1; i <= logT; i++) G[i] = G[i - 1] * G[i - 1];
    for (int i = 1; i <= k; i++) {
        int dt = f[i].t - f[i - 1].t;
        for (int j = logT; j >= 0; j--) if ((dt >> j) & 1) A = A * G[j];
        A.a[f[i].x] += f[i].y;
    }
    if (A.a[1] < 0) A.a[1] = -1;
    std::cout << A.a[1] << '\n';
    return 0;
}