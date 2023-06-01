#include <iostream>

typedef long long lxl;

const int maxN = 5e6;

int n, m;
int f[maxN + 10];
int p[maxN + 10];
int d[maxN + 10];
lxl ans;

void f2p() {
    for (int i = 1; i <= n - 1; i++) std::cin >> f[i];
    for (int i = 1; i <= n - 1; i++) d[f[i]]++;
    for (int i = 1, j = 1; i <= n - 2; i++, j++) {
        while (d[j]) j++;
        p[i] = f[j];
        while (i <= n - 2 && !--d[p[i]] && p[i] < j) p[i + 1] = f[p[i]], i++;
    }
    for (int i = 1; i <= n - 2; i++) ans ^= 1ll * i * p[i];
    return;
}

void p2f() {
    for (int i = 1; i <= n - 2; i++) std::cin >> p[i];
    for (int i = 1; i <= n - 2; i++) d[p[i]]++;
    p[n - 1] = n;
    for (int i = 1, j = 1; i <= n - 1; i++, j++) {
        while (d[j]) j++;
        f[j] = p[i];
        while (i <= n - 1 && !--d[p[i]] && p[i] < j) f[p[i]] = p[i + 1], i++;
    }
    for (int i = 1; i <= n - 1; i++) ans ^= 1ll * i * f[i];
    return;
}

int main() {
    std::cin >> n >> m;
    if (m == 1) f2p();
    if (m == 2) p2f();
    std::cout << ans << '\n';
    return 0;
}