#include <iostream>

const int maxN = 1e5;
const int maxC = 1e5;
const int maxM = 1e5;
const int sqrN = 317;

int n, c, m;
int a[maxN + 10];
int ans;
int l, r;
int L, R;

struct BlockArray {
    struct Block {
        int l, r;
    } block[sqrN + 10];

    struct Array {
        int bel;
    } array[maxN + 10];

    int cnt[sqrN + 10][maxC + 10];
    int ans[sqrN + 10][sqrN + 10];
    int tmp[maxC + 10];

    void Build() {
        for (int i = 1; i <= n; i++) array[i].bel = (i - 1) / sqrN + 1;
        for (int i = n; i >= 1; i--) block[array[i].bel].l = i;
        for (int i = 1; i <= n; i++) block[array[i].bel].r = i;
        for (int i = 1; i <= n; i++) cnt[array[i].bel][a[i]]++;
        for (int i = 1; i <= array[n].bel; i++) for (int j = 1; j <= c; j++) cnt[i][j] += cnt[i - 1][j];
        for (int i = 1; i <= array[n].bel; i++) {
            for (int j = i; j <= array[n].bel; j++) {
                ans[i][j] = ans[i][j - 1];
                for (int k = block[j].l; k <= block[j].r; k++) {
                    tmp[a[k]]++;
                    if (tmp[a[k]] == 1) continue;
                    if (tmp[a[k]] & 1) ans[i][j]--;
                    else ans[i][j]++;
                }
            }
            for (int j = block[i].l; j <= n; j++) tmp[a[j]]--;
        }
        return;
    }

    int brute(int l, int r) {
        int ret = 0;
        for (int i = l; i <= r; i++) {
            tmp[a[i]]++;
            if (tmp[a[i]] == 1) continue;
            if (tmp[a[i]] & 1) ret--;
            else ret++;
        }
        for (int i = l; i <= r; i++) tmp[a[i]]--;
        return ret;
    }

    int Query(int l, int r) {
        int ret = ans[array[l].bel + 1][array[r].bel - 1];
        if (array[l].bel == array[r].bel) return brute(l, r);
        for (int i = l; i <= block[array[l].bel].r; i++) {
            tmp[a[i]]++;
            if (cnt[array[r].bel - 1][a[i]] - cnt[array[l].bel][a[i]] + tmp[a[i]] == 1) continue;
            if ((cnt[array[r].bel - 1][a[i]] - cnt[array[l].bel][a[i]] + tmp[a[i]]) & 1) ret--;
            else ret++;
        }
        for (int i = block[array[r].bel].l; i <= r; i++) {
            tmp[a[i]]++;
            if (cnt[array[r].bel - 1][a[i]] - cnt[array[l].bel][a[i]] + tmp[a[i]] == 1) continue;
            if ((cnt[array[r].bel - 1][a[i]] - cnt[array[l].bel][a[i]] + tmp[a[i]]) & 1) ret--;
            else ret++;
        }
        for (int i = l; i <= block[array[l].bel].r; i++) tmp[a[i]]--;
        for (int i = block[array[r].bel].l; i <= r; i++) tmp[a[i]]--;
        return ret;
    }
} BA;

int main() {
    std::cin >> n >> c >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    BA.Build();
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        L = (l + ans) % n + 1;
        R = (r + ans) % n + 1;
        if (L > R) std::swap(L, R);
        std::cout << (ans = BA.Query(L, R)) << '\n';
    }
    return 0;
}