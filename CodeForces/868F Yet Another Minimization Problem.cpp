#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxA = 1e5;
const int maxN = 1e5;
const int maxK = 20;
const lxl inf = 1e18 + 10;

int n, k;
int a[maxN + 10];
lxl f[maxN + 10][maxK + 10];

namespace captainMo {
    int l = 1;
    int r = 0;
    lxl cnt[maxA + 10];
    lxl res;

    void Add(int x) {
        res += cnt[a[x]];
        cnt[a[x]]++;
        return;
    }

    void Del(int x) {
        cnt[a[x]]--;
        res -= cnt[a[x]];
        return;
    }

    lxl calc(int ql, int qr) {
        while (l > ql) Add(--l);
        while (r < qr) Add(++r);
        while (l < ql) Del(l++);
        while (r > qr) Del(r--);
        return res;
    }
}

void solve(int k, int l, int r, int tl, int tr) {
    if (l > r) return;
    if (tl > tr) return;
    int mid = (l + r) / 2;
    int dec = 0;
    lxl res = inf;
    for (int i = tl; i <= tr; i++) {
        lxl tmp = captainMo::calc(i + 1, mid);
        if (res > f[i][k - 1] + tmp) {
            res = f[i][k - 1] + tmp;
            dec = i;
        }
    }
    f[mid][k] = res;
    solve(k, l, mid - 1, tl, dec);
    solve(k, mid + 1, r, dec, tr);
    return;
}

int main() {
    promote();
    std::fill(f[0], f[0] + sizeof(f) / 8, inf); f[0][0] = 0;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= k; i++) solve(i, 1, n, 0, n - 1);
    std::cout << f[n][k] << '\n';
    return 0;
}