#include <iostream>

const int maxN = 5e5;
const int mod = 1e9 + 7;

int n;
int a[maxN + 10];
int b[maxN + 10];
int a1[maxN + 10];
int b1[maxN + 10];
int a2[maxN + 10];
int b2[maxN + 10];
int ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) a1[i] = (a1[i - 1] + a[i]) % mod;
    for (int i = 1; i <= n; i++) b1[i] = (b1[i - 1] + b[i]) % mod;
    for (int i = 1; i <= n; i++) a2[i] = (a2[i - 1] + a1[i]) % mod;
    for (int i = 1; i <= n; i++) b2[i] = (b2[i - 1] + b1[i]) % mod;
    for (int i = 1; i <= n; i++) ans = (ans + 1ll * a1[i] * b1[i] % mod * i % mod) % mod;
    for (int i = 1; i <= n; i++) ans = (ans + 1ll * a1[i - 1] * b1[i - 1] % mod * (n - i + 1) % mod) % mod;
    for (int i = 1; i <= n; i++) ans = (ans - 1ll * a1[i] * b2[i - 1] % mod + mod) % mod;
    for (int i = 1; i <= n; i++) ans = (ans - 1ll * b1[i] * a2[i - 1] % mod + mod) % mod;
    std::cout << ans << '\n';
    return 0;
}