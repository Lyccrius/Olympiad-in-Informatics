#include <iostream>

const int maxN = 400;
const int mod = 1e9 + 7;

int N;
int a[maxN + 10][maxN + 10];

int inv(int x) {
    if (x == 1) return 1;
    return mod - 1ll * inv(mod % x) * (mod / x) % mod;
}

struct Matrix {
    int n, m;
    int a[maxN + 10][2 * maxN + 10];

    void show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cout << a[i][j] << ' ';
            }
            std::cout << '\n';
        }
        return;
    }

    bool Gauss() {
        for (int i = 1; i <= n; i++) {
            int i_;
            for (i_ = i; i_ <= n; i_++) if (a[i_][i] != 0) break;
            if (i_ > n) return false;
            for (int j = i; j <= m; j++) std::swap(a[i][j], a[i_][j]);
            int invII = inv(a[i][i]);
            for (int j = m; j >= i; j--) a[i][j] = 1ll * a[i][j] * invII % mod;
            for (int i_ = 1; i_ <= n; i_++) if (i_ != i) for (int j = m; j >= i; j--) a[i_][j] = (a[i_][j] - 1ll * a[i_][i] * a[i][j] % mod + mod) % mod;
        }
        return true;
    }
} A;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) std::cin >> a[i][j];
    A.n = N;
    A.m = 2 * N;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) A.a[i][j] = a[i][j];
    for (int i = 1; i <= N; i++) A.a[i][N + i] = 1;
    if (!A.Gauss()) {
        std::cout << "No Solution" << '\n';
        return 0;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            std::cout << A.a[i][N + j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}