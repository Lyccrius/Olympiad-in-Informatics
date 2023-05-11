#include <iostream>
#include <cstring>
#include <algorithm>

const int maxN = 1e5;
const int maxM = 1e5;

int t;
int n, m;
int x[maxN + 10];
int v[maxM + 10];

void mian() {
    std::memset(v, 0, sizeof(v));
    int cntL = 0;
    int cntR = 0;
    int cntX = 0;
    int ans = 0;
    int minX = maxM + 10;
    int maxX = -1;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
        if (x[i] == -1) cntL++;
        else if (x[i] == -2) cntR++;
        else v[x[i]] = 1, cntX++;
    }
    for (int i = 1; i <= m; i++) v[i] += v[i - 1];
    for (int i = 1; i <= n; i++) {
        if (x[i] < 0) continue;
        minX = std::min(minX, x[i]);
        maxX = std::max(maxX, x[i]);
        int vl = v[x[i] - 1];
        int vr = v[m] - v[x[i]];
        int cl = std::min(cntL, x[i] - 1 - vl);
        int cr = std::min(cntR, m - x[i] - vr);
        //printf("%d: vl = %d, vr = %d, cl = %d, cr = %d, res = %d\n", i, vl, vr, cl, cr, vl + vr + cl + cr + 1);
        ans = std::max(ans, vl + vr + cl + cr + 1);
    }
    ans = std::max(ans, std::min(m, v[m] + cntL));
    ans = std::max(ans, std::min(m, v[m] + cntR));
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}