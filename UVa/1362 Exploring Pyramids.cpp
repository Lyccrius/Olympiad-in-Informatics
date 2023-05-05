#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 300;
const int mod = 1e9;

chr s[maxN + 10];
int f[maxN + 10][maxN + 10];
int n;

void mian() {
    n = strlen(s + 1);
    std::memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            if (j > n) break;
            if (s[i] != s[j]) continue;
            f[i][j] = f[i + 1][j - 1];
            for (int k = i - 1; k <= j - 1; k++) {
                if (s[i] != s[k]) continue;
                //if (s[k + 1] != s[j]) continue;
                f[i][j] = (f[i][j] + 1ll * f[i + 1][k - 1] * f[k][j] % mod) % mod;
            }
        }
    }
    std::cout << f[1][n] << '\n';
    return;
}

int main() {
    while (scanf("%s", s + 1) != EOF) mian();
    return 0;
}