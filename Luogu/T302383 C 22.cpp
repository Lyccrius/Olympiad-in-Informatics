#include <iostream>

const int maxN = 1000;
const int maxM = 1000;
const int mod = 998244353;

int q;
int n, m;
int c[maxN + 10][maxM + 10];
int a[maxN + 10][maxM + 10];

void mian() {
    std::cin >> n >> m;
    m = std::min(m, n);
    std::cout << a[n][m] << '\n';
    return;
}

int main() {
    for (int i = 0; i <= 1000; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    for (int i = 0; i <= 1000; i++) {
        a[i][0] = i / 2 + 1;
        for (int j = 1; j <= i; j++) {
            a[i][j] = a[i][j - 1];
            for (int k = j; k <= i; k += 2) {
                a[i][j] = (a[i][j] + c[k][j]) % mod;
            }
        }
        //for (int j = 0; j <= i; j++) std::cout << a[i][j] << ' ';
        //std::cout << '\n';
    }
    std::cin >> q;
    while (q--) mian();
    return 0;
}