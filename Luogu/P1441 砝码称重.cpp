#include <iostream>
#include <algorithm>

const int maxN = 20;
const int maxM = 4;
const int maxA = 100;

int n, m;
int a[maxN + 10];
int v[maxN + 10];
int f[maxN * maxA + 10];
int ans;

void DP() {
    int res = 0;
    int tot = 0;
    for (int i = 1; i <= maxN * maxA; i++) f[i] = false; f[0] = true;
    for (int i = 1; i <= n; i++) {
        if (v[i] == false) continue;
        for (int j = tot; j >= 0; j--) {
            if (f[j] == false) continue;
            if (f[j + a[i]]) continue;
            f[j + a[i]] = true;
            res++;
        }
        tot += a[i];
    }
    ans = std::max(ans, res);
    return;
}

void DFS(int now, int cur) {
    if (now >= n - m) {
        DP();
        return;
    }
    if (cur > n) return;
    v[cur] = true;
    DFS(now + 1, cur + 1);
    v[cur] = false;
    DFS(now, cur + 1);
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    DFS(0, 1);
    std::cout << ans << '\n';
    return 0;
}