#include <iostream>

const int maxN = 5e3;
const int mod = 998244353;

int n;
int s[maxN + 10][maxN + 10];
int p0w[maxN + 10];
int fac[maxN + 10];
int f;

int main() {
    std::cin >> n;
    for (int i = 0; i <= n; i++) s[i][i] = 1;
    for (int i = 1; i <= n; i++) s[i][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= i - 1; j++) {
            s[i][j] = (1ll * j * s[i - 1][j] % mod + s[i - 1][j - 1]) % mod;
        }
    }
    p0w[0] = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) p0w[i] = 1ll * p0w[i - 1] * 2 % mod;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    for (int i = 0; i <= n; i++) for (int j = 0; j <= i; j++) f = (1ll * s[i][j] * p0w[j] % mod * fac[j] % mod + f) % mod;
    std::cout << f << '\n';
    return 0;
}