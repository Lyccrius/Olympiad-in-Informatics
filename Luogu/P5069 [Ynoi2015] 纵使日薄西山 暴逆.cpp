#include <iostream>
#include <algorithm>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxQ = 1e5;
const int maxA = 1e9;

int n;
int a[maxN + 10];
int b[maxN + 10];
int v[maxN + 10];
int q;
int x[maxQ + 10], y[maxQ + 10];

bool cmpByA(const int &x, const int &y) {
    if (a[x] == a[y]) return x < y;
    return a[x] > a[y];
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> x[i] >> y[i];
        a[x[i]] = y[i];
        for (int i = 1; i <= n; i++) b[i] = i;
        std::sort(b + 1, b + n + 1, cmpByA);
        lxl ans = 0;
        for (int i = 1; i <= n; i++) v[i] = false;
        for (int i = 1; i <= n; i++) {
            if (v[b[i]]) continue;
            v[b[i]] = true;
            v[b[i] - 1] = true;
            v[b[i] + 1] = true;
            ans += a[b[i]];
        }
        std::cout << ans << '\n';
    }
    return 0;
}