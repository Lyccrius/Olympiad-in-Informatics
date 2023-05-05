#include <iostream>

const int maxN = 4e6 + 1;

typedef long long lxl;

lxl phi[maxN + 10];
lxl f[maxN + 10];
lxl g[maxN + 10];
int n;

void mian() {
    std::cout << g[n] << '\n';
    return;
}

int main() {
    phi[1] = 1;
    for (int i = 1; i <= maxN; i++) {
        if (phi[i]) continue;
        for (int j = i; j <= maxN; j += i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
    for (int i = 1; i <= maxN; i++) {
        for (int j = 2 * i; j <= maxN; j += i) {
            f[j] += 1ll * i * phi[j / i];
        }
    }
    for (int i = 1; i <= maxN; i++) {
        g[i] = g[i - 1] + f[i];
    }
    while (std::cin >> n && n) mian();
    return 0;
}