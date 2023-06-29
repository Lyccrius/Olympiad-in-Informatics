#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<lxl> vlc;

lxl n;
lxl m;
vlc fac;
vlc ans;

void DFS(lxl now, lxl res) {
    if (now > n) {
        fac.push_back(res);
        return;
    }
    DFS(now + 1, res);
    DFS(now + 1, res * now);
    return;
}

int main() {
    std::cin >> n;
    std::cin >> m;
    DFS(1, 1);
    std::sort(fac.begin(), fac.end());
    fac.erase(std::unique(fac.begin(), fac.end()), fac.end());
    std::reverse(fac.begin(), fac.end());
    for (auto i : fac) {
        while (m >= i) {
            m -= i;
            ans.push_back(i);
        }
        if (!m) break;
    }
    std::sort(ans.begin(), ans.end());
    for (auto i : ans) std::cout << i << '\n';
    return 0;
}