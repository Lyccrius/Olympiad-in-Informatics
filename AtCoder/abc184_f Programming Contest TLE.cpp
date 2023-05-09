#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 40;

lxl n, t;
lxl a[maxN + 10];
lxl s[maxN + 10];
lxl ans;

void DFS(lxl now, int cur) {
    if (now > t) return;
    if (now + s[cur] <= ans) return;
    ans = std::max(ans, now);
    if (cur > n) return;
    DFS(now + a[cur], cur + 1);
    DFS(now, cur + 1);
    return;
}

int main() {
    std::cin >> n >> t;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    std::reverse(a + 1, a + n + 1);
    for (int i = n; i >= 1; i--) s[i] = s[i + 1] + a[i];
    DFS(0, 1);
    std::cout << ans << '\n';
    return 0;
}