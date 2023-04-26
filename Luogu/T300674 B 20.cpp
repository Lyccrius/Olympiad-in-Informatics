#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int mod = 1e9 + 7;

int T;
int l, r;
int ans;

int abs(int x) {
    if (x < 0) x = - x;
    return x;
}

int f(int x, int y) {
    int ret = 0;
    vic bx;
    vic by;
    while (x) bx.push_back(x % 10), x /= 10;
    while (y) by.push_back(y % 10), y /= 10;
    std::sort(bx.begin(), bx.end());
    std::sort(by.begin(), by.end());
    std::reverse(bx.begin(), bx.end());
    std::reverse(by.begin(), by.end());
    while (bx.size() < by.size()) bx.push_back(0);
    while (bx.size() > by.size()) by.push_back(0);
    for (int i = 0; i < bx.size(); i++) ret = (ret + abs(bx[i] - by[i])) % mod;
    return ret;
}

void mian() {
    ans = 0;
    std::cin >> l >> r;
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            ans = (ans + 2 * f(i, j) % mod) % mod;
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}