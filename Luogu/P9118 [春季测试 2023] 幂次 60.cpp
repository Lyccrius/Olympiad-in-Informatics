#include <iostream>
#include <bitset>

#define maxN 1000000000

typedef long long lxl;

lxl n, k;
std::bitset<maxN> vis;
lxl ans;

int main() {
    std::cin >> n >> k;
    if (k == 1) {
        std::cout << n << '\n';
        return 0;
    }
    for (lxl i = 2; i * i <= n; i++) {
        if (i < maxN) if (vis[i]) continue;
        for (lxl j = i, p = 1; j <= n; j *= i, p++) {
            if (j < maxN) vis[j] = true;
            if (p >= k) ans++;
        }
    }
    std::cout << ans + 1 << '\n';
    return 0;
}