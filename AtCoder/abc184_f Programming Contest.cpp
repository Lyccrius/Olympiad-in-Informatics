#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<lxl> vlc;

const int maxN = 40;

lxl n, t;
lxl a[maxN + 10];
lxl s[maxN + 10];
lxl ans;
vlc resl;
vlc resr;

void DFS(vlc &res, lxl now, int cur) {
    if (now > t) return;
    //if (now + s[cur] <= ans) return;
    //ans = std::max(ans, now);
    res.push_back(now);
    if (cur > n) return;
    DFS(res, now + a[cur], cur + 2);
    DFS(res, now, cur + 2);
    return;
}

int main() {
    std::cin >> n >> t;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    std::reverse(a + 1, a + n + 1);
    for (int i = n; i >= 1; i--) s[i] = s[i + 1] + a[i];
    DFS(resl, 0, 1);
    DFS(resr, 0, 2);
    std::sort(resl.begin(), resl.end());
    std::sort(resr.begin(), resr.end());
    resl.erase(std::unique(resl.begin(), resl.end()), resl.end());
    resr.erase(std::unique(resr.begin(), resr.end()), resr.end());
    for (int i = 0; i < resl.size(); i++) {
        int j = std::upper_bound(resr.begin(), resr.end(), t - resl[i]) - resr.begin() - 1;
        if (j >= 0) ans = std::max(ans, resl[i] + resr[j]);
    }
    std::cout << ans << '\n';
    return 0;
}