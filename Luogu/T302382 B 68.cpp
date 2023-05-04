#include <iostream>
#include <algorithm>

typedef long long lxl;

const int inf = 1e7;
const int lim = 2e8;

int n, b;
int ans;
int cnt;

int calc(lxl n) {
    int ret = 0;
    while (n) {
        if (n % b) ret++;
        n /= b;
        cnt++;
    }
    return ret;
}

int main() {
    ans = inf;
    std::cin >> n >> b;
    for (lxl i = 1; cnt <= lim; i++) ans = std::min(ans, calc(i * n));
    std::cout << ans << '\n';
    return 0;
}