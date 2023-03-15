#include <iostream>

const int maxN = 1e5;
const int inf = 1e9 + 10;

int n;
int a[maxN + 10];
int b[maxN + 10];
int ans = inf;

int lowbit(int x) {
    return x & - x;
}

int highbit(int x) {
    int ret = 0;
    while (x) {
        ret = lowbit(x);
        x -= lowbit(x);
    }
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = b[i - 1] ^ a[i];
    for (int i = 1; i <= n; i++) {
        if (highbit(a[i]) == highbit(a[i + 1]) &&
            highbit(a[i]) == highbit(a[i + 2])) {
            std::cout << 1;
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                if ((b[j] ^ b[i - 1]) > (b[k] ^ b[j])) {
                    ans = std::min(ans, k - i - 1);
                }
            }
        }
    }
    if (ans == inf) ans = - 1;
    std::cout << ans;
}