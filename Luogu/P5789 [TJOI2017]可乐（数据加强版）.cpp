#include <iostream>

const int maxT = 1e9;
const int maxN = 100;
const int maxM = 100;
const int mod = 2017;

int N, M;
int u, v;
int t;

struct Matrix {
    int n;
    int m;
    int a[maxN + 10][maxN + 10];

    Matrix operator*(const Matrix other) {
        Matrix ret;
        ret.n = this->n;
        ret.m = other.m;
        for (int i = 0; i <= ret.n; i++) {
            for (int j = 0; j <= ret.m; j++) {
                ret.a[i][j] = 0;
                for (int k = 0; k <= other.n; k++) {
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * other.a[k][j] % mod) % mod;
                }
            }
        }
        return ret;
    }
} I;

Matrix pow(Matrix a, int b) {
    Matrix ret = I;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

namespace graph {
    Matrix G;

    void addEdge(int tail, int head) {
        G.a[tail][head] = 1;
        return;
    }

    void solve() {
        int ans = 0;
        G = pow(G, t);
        for (int i = 0; i <= N; i++) ans = (ans + G.a[1][i]) % mod;
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    std::cin >> N >> M;
    I.n = N;
    I.m = N;
    for (int i = 0; i <= N; i++) I.a[i][i] = 1;
    graph::G.n = N;
    graph::G.m = N;
    for (int i = 1; i <= M; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    for (int i = 0; i <= N; i++) {
        graph::addEdge(i, i);
        graph::addEdge(i, 0);
    }
    std::cin >> t;
    graph::solve();
    return 0;
}