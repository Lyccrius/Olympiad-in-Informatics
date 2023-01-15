#include <iostream>
#include <algorithm>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int inf = 1e9;

const int maxN = 35;
const int maxM = 595;

int n, m;
int a, b;
lxl c[maxN + 10];
std::map<lxl, int> f;
int ans = inf;

int main() {
    promote();
    std::cin >> n >> m;
    c[0] = 1;
    for (int i = 1; i < n; i++) c[i] = c[i - 1] * 2;
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        a--;
        b--;
        c[a] |= ((long long)1 << b);
        c[b] |= ((long long)1 << a);
    }
    for (int i = 0; i < (1 << (n / 2)); ++i) {
        long long t = 0;
        int cnt = 0;
        for (int j = 0; j < n / 2; ++j) {
            if ((i >> j) & 1) {
                t ^= c[j];
                cnt++;
            }
        }
        if (!f.count(t)) f[t] = cnt;
        else f[t] = std::min(f[t], cnt);
    }
    for (int i = 0; i < (1 << (n - n / 2)); ++i) {
        long long t = 0;
        int cnt = 0;
        for (int j = 0; j < (n - n / 2); ++j) {
            if ((i >> j) & 1) {
                t ^= c[n / 2 + j];
                ++cnt;
            }
        }
        if (f.count((((long long)1 << n) - 1) ^ t)) ans = std::min(ans, cnt + f[(((long long)1 << n) - 1) ^ t]);
    }
    std::cout << ans << "\n";
    return 0;
}