#include <iostream>
#include <map>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef unsigned long long lxl;
typedef double dbl;

lxl n, k;

std::map<lxl, bool> vis;
std::map<lxl, bool> ban;
void init() {
    for (lxl i = 2; i <= n; i++) {
        //if (vis[i] == false) {
        //    for (lxl j = 2; i * j <= n; j++) vis[i * j] = true;
        if (ban[i] == false) for (lxl j = i * i; j <= n; j *= i) ban[j] = true;//, printf("ban %d\n", j);
        //}
    }
    return;
}

bool check(lxl v, lxl &p) {
    if (ban[v]) return false;
    lxl x = v;
    lxl y = k;
    while (y) {
        if (y & 1) p = p * x;
        if (p > n) return false;
        x = x * x;
        y = y / 2;
    }
    return true;
}

lxl ans = 1;

int main() {
    freopen("power.in", "r", stdin);
    freopen("power.out", "w", stdout);
    promote();
    std::cin >> n >> k; init();
    for (lxl i = 2; i <= n; i++) {
        lxl p = 1;
        if (check(i, p)) {
            ans += std::log(n / p) / std::log(i) + 1;
            //printf("%d, pow = %d: %d\n", i, p, ans);
        }
    }
    std::cout << ans;
    return 0;
}