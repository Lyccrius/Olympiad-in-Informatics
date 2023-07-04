#include <iostream>
#include <cstring>

typedef char chr;
typedef long long lxl;

const int maxN = 2e7;
const int maxM = 2e7;

int n;
int m;
chr a[maxN + 10];
chr b[maxM + 10];
lxl z[maxM + 10];
lxl p[maxN + 10];

int main() {
    std::cin >> (a + 1);
    std::cin >> (b + 1);
    n = strlen(a + 1);
    m = strlen(b + 1);
    z[1] = m;
    for (int i = 2, l = 0, r = 0; i <= m; i++) {
        if (i <= r) z[i] = std::min(z[i - l + 1], (lxl) r - i + 1);
        while (i + z[i] <= m && b[i + z[i]] == b[1 + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    for (int i = 1, l = 0, r = 0; i <= n; i++) {
        if (i <= r) p[i] = std::min(z[i - l + 1], (lxl) r - i + 1);
        while (i + p[i] <= n && a[i + p[i]] == b[1 + p[i]]) p[i]++;
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    for (int i = 1; i <= m; i++) z[0] ^= 1ll * i * (z[i] + 1);
    for (int i = 1; i <= n; i++) p[0] ^= 1ll * i * (p[i] + 1);
    std::cout << z[0] << '\n';
    std::cout << p[0] << '\n';
    return 0;
}