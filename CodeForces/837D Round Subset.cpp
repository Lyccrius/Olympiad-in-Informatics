#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long lxl;

const int maxN = 200;
const int logA = 60;

int n, k;
lxl a[maxN + 10];
lxl a2[maxN + 10];
lxl a5[maxN + 10];
lxl f[maxN + 10][maxN * logA + 10];
lxl ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) while (a[i] && a[i] % 2 == 0) a[i] /= 2, a2[i]++;
    for (int i = 1; i <= n; i++) while (a[i] && a[i] % 5 == 0) a[i] /= 5, a5[i]++;
    std::memset(f, 0xcf, sizeof(f)); f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = k; j >= 1; j--) {
            for (int l = n * logA; l >= a5[i]; l--) {
                f[j][l] = std::max(f[j][l], f[j - 1][l - a5[i]] + a2[i]);
            }
        }
    }
    for (lxl i = 0; i <= n * logA; i++) ans = std::max(ans, std::min(i, f[k][i]));
    std::cout << ans;
    return 0;
}