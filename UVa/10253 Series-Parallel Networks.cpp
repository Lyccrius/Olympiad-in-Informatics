#include <iostream>

typedef long long lxl;

const int maxN = 30;

int n;
lxl c[maxN + 10];
lxl f[maxN + 10];

lxl C(lxl n, lxl m) {
    long double ret = 1;
    for (lxl i = n - m + 1; i <= n; i++) ret *= i;
    for (lxl i = 1; i <= m; i++) ret /= i;
    return ret;
}

void DFS(int n, int now, int tot) {
    if (tot == 0) {
        lxl res = 1;
        for (int i = 1; i <= now; i++) {
            if (c[i] == 0) continue;
            res *= C(f[i] + c[i] - 1, c[i]);
        }
        f[n] += res;
        return;
    }
    for (int i = now; (i < n) && (i <= tot); i++) {
        c[i]++;
        DFS(n, i, tot - i);
        c[i]--;
    }
    return;
}

void mian() {
    if (n == 1) {
        std::cout << 1 << '\n';
    } else {
        std::cout << 2ll * f[n] << '\n';
    }
    return;
}

int main() {
    f[1] = 1;
    for (int i = 2; i <= maxN; i++) DFS(i, 1, i);
    while (std::cin >> n && n) mian();
    return 0;
}