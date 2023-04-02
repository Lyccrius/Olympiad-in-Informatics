#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxK = 4;
const int maxN = 5e5;
const int maxA = 3e4;

int T, k;
int n;
int a[maxK * 2 + 5][maxN + 10];
int s[maxN + 10];
int mn[maxK + 10];
int mx[maxK + 10];

void init() {
    std::memset(mn, 0x3f, sizeof(mn));
    std::memset(mx, 0xcf, sizeof(mx));
    std::memset(s, 1, sizeof(s));
    return;
}

bool DFS(int id, int lim) {
    if (id > n) return true;
    for (int S = 1; S <= k; S++) {
        bool ok = true;
        for (int j = 1; j <= k; j++) {
            int tn = mn[j];
            int tx = mx[j];
            tn = std::min(tn, a[S + j - 1][id]);
            tx = std::max(tx, a[S + j - 1][id]);
            if (tx - tn > lim) {
                ok = false;
                break;
            }
        }
        if (ok == false) continue;
        int bn[maxK + 10];
        int bx[maxK + 10];
        for (int j = 1; j <= k; j++) {
            bn[j] = mn[j];
            bx[j] = mx[j];
        }
        for (int j = 1; j <= k; j++) {
            mn[j] = std::min(mn[j], a[S + j - 1][id]);
            mx[j] = std::max(mx[j], a[S + j - 1][id]);
        }
        int sb = s[id];
        s[id] = S;
        if (DFS(id + 1, lim)) return true;
        for (int j = 1; j <= k; j++) {
            mn[j] = bn[j];
            mx[j] = bx[j];
        }
        s[id] = sb;
    }
    return false;
}

void mian() {
    std::cin >> n;
    for (int i = 1; i <= k; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= k; i++) for (int j = 1; j <= n; j++) a[i + k][j] = a[i][j];
    int l = 0;
    int r = maxA;
    while (l < r) {
        int mid = (l + r) / 2;
        init();
        if (DFS(1, mid)) r = mid;
        else l = mid + 1;
    }
    std::cout << l << '\n';
    return;
}

int main() {
    freopen("lock.in", "r", stdin);
    freopen("lock.out", "w", stdout);
    promote();
    std::cin >> T >> k;
    while (T--) mian();
    return 0;
}