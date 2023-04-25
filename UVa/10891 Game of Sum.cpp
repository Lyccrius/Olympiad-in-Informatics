#include <iostream>
#include <cstring>

typedef long long lxl;

const int maxN = 100;

int n;
int a[maxN + 10];
lxl p[maxN + 10];
lxl res[maxN + 10][maxN + 10];
lxl pre[maxN + 10][maxN + 10];
lxl suf[maxN + 10][maxN + 10];

void mian() {
    std::memset(res, 0, sizeof(res));
    std::memset(pre, 0, sizeof(pre));
    std::memset(suf, 0, sizeof(suf));
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) p[i] = p[i - 1] + a[i];
    for (int i = 1; i <= n; i++) res[i][i] = a[i];
    for (int i = 1; i <= n; i++) pre[i][i] = a[i];
    for (int i = 1; i <= n; i++) suf[i][i] = a[i];
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            if (j > n) break;
            res[i][j] = p[j] - p[i - 1];
            res[i][j] = std::max(res[i][j], p[j] - p[i - 1] - pre[i][j - 1]);
            res[i][j] = std::max(res[i][j], p[j] - p[i - 1] - suf[i + 1][j]);
            pre[i][j] = std::min(res[i][j], pre[i][j - 1]);
            suf[i][j] = std::min(res[i][j], suf[i + 1][j]);
        }
    }
    std::cout << res[1][n] - (p[n] - res[1][n]) << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}