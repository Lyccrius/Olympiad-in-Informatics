#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int n, x, y;
int a[maxN + 10];

int main() {
    std::cin >> n >> x >> y;
    if (1ll * x * y < n || x + y > n + 1) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    for (int i = 1; i <= n; i++) a[i] = i;
    int t = n - x;
    int r = n;
    int l = n - y + 1;
    while (t) {
        l = std::max(l, r - t);
        std::reverse(a + l, a + r + 1);
        r -= y;
        l -= std::min(t, y);
        t -= std::min(t, y - 1);
        /*
        if (t < y) {
            std::reverse(a + r - t, a + r + 1);
            break;
        } else {
            std::reverse(a + r - y + 1, a + r + 1);
            t -= (y - 1);
            r -= y;
        }
        */
    }
    for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
    return 0;
}