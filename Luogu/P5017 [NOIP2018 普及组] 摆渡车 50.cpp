#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 500;
const int maxM = 100;
const int maxT = 4e6;
const int inf = 1e9 + 10;

int n, m;
int t[maxN + 10];
int c[maxT + 10];
int p[maxT + 10];
int f[maxT + 10];
int ans = inf;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> t[i];
    std::sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; i++) c[t[i]]++;
    for (int i = 1; i <= n; i++) p[t[i]] += t[i];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            f[i] += c[j] * (i - j);
        }
    }
    for (int i = 1; i <= maxT; i++) {
        if (i > t[n] + m) break;
        c[i] = c[i - 1] + c[i];
        p[i] = p[i - 1] + p[i];
    }
    for (int i = m; i <= maxT; i++) {
        f[i] = inf;
        if (i > t[n] + m) break;
        for (int j = 0; j <= i - m; j++) {
            int t = f[j] + (c[i] - c[j]) * i - (p[i] - p[j]);
            f[i] = std::min(f[i], t);
        }
    }
    for (int i = t[n]; i <= t[n] + m; i++) ans = std::min(ans, f[i]);
    std::cout << ans;
    return 0;
}