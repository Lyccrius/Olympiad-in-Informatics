#include <iostream>

const int maxT = 1e5;

int T;
int n, m;

void mian() {
    bool cross = false;
    int ans = 0;
    std::cin >> n >> m;
    n--;
    m--;
    if (n >= 1 && m >= 1) {
        n -= 1;
        m -= 1;
        ans += 2;
        int t = std::min(n, m);
        n -= t;
        m -= t;
        ans += t;
        cross = true;
    }
    if (n < m) std::swap(n, m);
    if (n >= 2 - cross) {
        n -= 2 - cross;
        ans += 2 - cross;
        int t = n / 2;
        n -= t * 2;
        ans += t;
    }
    if (n) ans++;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}