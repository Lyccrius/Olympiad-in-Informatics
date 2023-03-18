#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;
const int maxM = 2000;

const int mod = 998244353;

int n, m;
int a[maxN + 10][maxM + 10];
int ans;

namespace Brute {
    bool is() {
        return n <= 10;
    }

    int c[maxM + 10];
    int ans;

    bool check(int k) {
        if (k == 0) return false;
        for (int j = 1; j <= m; j++) {
            if (c[j] > k / 2) {
                return false;
            }
        }
        return true;
    }

    void DFS(int now, int res, int k) {
        if (now > n) {
            if (check(k)) ans = (ans + res) % mod;
            return;
        }
        DFS(now + 1, res, k);
        for (int j = 1; j <= m; j++) {
            c[j]++;
            DFS(now + 1, 1ll * res * a[now][j] % mod, k + 1);
            c[j]--;
        }
        return;
    }

    void mian() {
        DFS(1, 1, 0);
        std::cout << ans;
        return;
    }
}

namespace DP {
    namespace m2 {
        bool is() {
            return m == 2;
        }

        int f[maxN + 10][maxN + 10][maxN + 10];
        int ans;

        void mian() {
            f[0][0][0] = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= i; j++) {
                    for (int k = 0; k <= j; k++) {
                        f[i][j][k] = f[i - 1][j][k];
                        if (j && k) f[i][j][k] = (f[i][j][k] + 1ll * f[i - 1][j - 1][k - 1] * a[i][1] % mod) % mod;
                        if (j) f[i][j][k] = (f[i][j][k] + 1ll * f[i - 1][j - 1][k] * a[i][2] % mod) % mod;
                    }
                }
            }
            for (int j = 1; j <= n; j++) {
                if ((j & 1) == 0) {
                    ans = (ans + f[n][j][j / 2]) % mod;
                }
            }
            std::cout << ans;
        }
    }

    namespace m3 {
        bool is() {
            return m == 3;
        }

        int f[maxN + 10][maxN + 10][maxN + 10][maxN + 10];
        int ans;

        void mian() {
            f[0][0][0][0] = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= i; j++) {
                    for (int k = 0; k <= j; k++) {
                        for (int l = 0; l <= j; l++) {
                            f[i][j][k][l] = f[i - 1][j][k][l];
                            if (j && k) f[i][j][k][l] = (f[i][j][k][l] + 1ll * f[i - 1][j - 1][k - 1][l] * a[i][1] % mod) % mod;
                            if (j && l) f[i][j][k][l] = (f[i][j][k][l] + 1ll * f[i - 1][j - 1][k][l - 1] * a[i][2] % mod) % mod;
                            if (j) f[i][j][k][l] = (f[i][j][k][l] + 1ll * f[i - 1][j - 1][k][l] * a[i][3] % mod) % mod;
                        }
                    }
                }
            }
            for (int j = 1; j <= n; j++) {
                for (int k = 0; k <= j / 2; k++) {
                    for (int l = 0; l <= j / 2; l++) {
                        if (j - k - l <= j / 2) {
                            ans = (ans + f[n][j][k][l]) % mod;
                        }
                    }
                }
            }
            std::cout << ans;
            return;
        }
    }
}

int main() {
    //freopen("meal.in", "r", stdin);
    //freopen("meal.out", "w", stdout);
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    if (Brute::is()) Brute::mian();
    else if (DP::m2::is()) DP::m2::mian();
    else if (DP::m3::is()) DP::m3::mian();
    return 0;
}