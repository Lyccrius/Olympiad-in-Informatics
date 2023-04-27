#include <iostream>

const int maxN = 300;
const int maxM = 300;
const int maxQ = 5e6;
const int mod = 998244353;

int n, m, q, x0;
int v, u, k;
int a[maxN + 10][maxM + 10];
int c[maxN + maxM + 10][maxN + maxM + 10];

void init() {
    for (int i = 0; i <= n + m; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
            //printf("c[%d][%d] = %d\n", i, j, c[i][j]);
        }
    }
    return;
}

int rand_() {
    x0 = (1ll * 100000005 * x0 + 20150823) % mod;
    return x0 / 100;
}

void mian() {
    v = rand_() % n + 1;
    u = rand_() % m + 1;
    k = rand_() % (n + m - v - u + 1);
    //printf("%d, %d, %d\n", v, u, k);
    for (int j = k; j <= n + m - v - u; j++) {
        for (int i = std::max(0, u + j - m); i <= std::min(j, n - v); i++) {
            //int x = v + i;
            //int y = u - i + j;
            //if (x > n || y > m) continue;
            a[v + i][u - i + j] += c[j][i];
            a[v + i][u - i + j] %= mod;
            //printf("a[%d][%d] = %d\n", v + i, u - i + j, a[v + i][u - i + j]);
            // n - v >= u + j - m
            // j <= n + m - v - u
        }
    }
    return;
}

int main() {
    std::cin >> n >> m >> q >> x0;
    init();
    while (q--) mian();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}