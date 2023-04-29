#include <iostream>

const int maxN = 5e6;

int n, p, k, K;
int a[maxN + 10];
int pre[maxN + 10];
int suf[maxN + 10];
int sum;
int ans;

int inv(int x) {
    if (x == 1) return 1;
    return 1ll * (p - p / x) * inv(p % x) % p;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> p >> k;
    K = k % p;
    pre[0] = 1;
    suf[n + 1] = 1;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) pre[i] = 1ll * pre[i - 1] * a[i] % p;
    for (int i = n; i >= 1; i--) suf[i] = 1ll * suf[i + 1] * a[i] % p;
    for (int i = 1; i <= n; i++) sum = (sum + 1ll * K * pre[i - 1] % p * suf[i + 1] % p) % p, K = 1ll * K * k % p;
    ans = 1ll * sum * inv(pre[n]) % p;
    std::cout << ans << '\n';
    return 0;
}