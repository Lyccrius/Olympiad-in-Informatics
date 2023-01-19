#include <iostream>
#include <algorithm>
#include <string>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const lxl inf = 1e12;

std::string need;
lxl c[5];
lxl n[5];
lxl p[5];
lxl r;
lxl ans;
lxl x[5];

int main() {
    std::cin >> need;
    for (int i = 0; i < need.size(); i++) {
        if (need[i] == 'B') c[1]++;
        if (need[i] == 'S') c[2]++;
        if (need[i] == 'C') c[3]++;
    }
    for (int i = 1; i <= 3; i++) std::cin >> n[i];
    for (int i = 1; i <= 3; i++) std::cin >> p[i];
    std::cin >> r;
    lxl a = inf;
    for (int i = 1; i <= 3; i++) if (c[i]) a = std::min(a, n[i] / c[i]);
    ans += a;
    for (int i = 1; i <= 3; i++) n[i] -= a * c[i];
    /*
    while (n[1] >= c[1] && n[2] >= c[2] && n[3] >= c[3]) {
        n[1] -= c[1];
        n[2] -= c[2];
        n[3] -= c[3];
        ans++;
    }
    */
    while (true) {
        bool flag = true;
        for (int i = 1; i <= 3; i++) if (c[i] && n[i]) flag = false;
        if (flag) break;
        for (int i = 1; i <= 3; i++) x[i] = std::max((long long)0, c[i] - n[i]);
        lxl cost = 0;
        for (int i = 1; i <= 3; i++) cost += x[i] * p[i];
        if (cost > r) break;
        r -= cost;
        for (int i = 1; i <= 3; i++) n[i] = std::max((long long)0, n[i] - c[i]);
        ans++;
    }
    lxl tot = 0;
    for (int i = 1; i <= 3; i++) tot += c[i] * p[i];
    ans += r / tot;
    std::cout << ans << '\n';
    return 0;
}