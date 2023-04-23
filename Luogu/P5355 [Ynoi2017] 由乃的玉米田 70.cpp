#include <iostream>
#include <algorithm>
#include <bitset>

const int maxN = 1e5;
const int maxM = 1e5;
const int maxA = 1e5;
const int sqrN = 316;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int opt, l, r, x;

struct CaptaimMo {
    struct Query {
        int id;
        int opt;
        int l, r;
        int x;

        bool operator<(const Query &other) const {
            if (b[l] != b[other.l]) return b[l] < b[other.l];
            if (b[r] != b[other.r]) return b[r] < b[other.r];
            return id < other.id;
        }
    } query[maxM + 10];
    int ans[maxM + 10];
    int cnt[maxA + 10];

    std::bitset<maxA + 10> may;
    std::bitset<maxA + 10> yam;

    void add(int pos) {
        if (cnt[a[pos]] == 0) {
            may[a[pos]] = true;
            yam[maxA - a[pos]] = true;
        }
        cnt[a[pos]]++;
        return;
    }

    void del(int pos) {
        cnt[a[pos]]--;
        if (cnt[a[pos]] == 0) {
            may[a[pos]] = false;
            yam[maxA - a[pos]] = false;
        }
        return;
    }

    void solve() {
        int l = 1;
        int r = 0;
        std::sort(query + 1, query + m + 1);
        for (int i = 1; i <= m; i++) {
            while (l > query[i].l) l--, add(l);
            while (r < query[i].r) r++, add(r);
            while (l < query[i].l) del(l), l++;
            while (r > query[i].r) del(r), r--;
            if (query[i].opt == 1) {
                ans[query[i].id] = (may & (may << query[i].x)).any();
            } else if (query[i].opt == 2) {
                ans[query[i].id] = (may & (yam >> (maxA - query[i].x))).any();
            } else if (query[i].opt == 3) {
                for (int j = 1; j * j <= query[i].x; j++) {
                    if (query[i].x % j) continue;
                    if (may[j] && (may[query[i].x / j])) {
                        ans[query[i].id] = true;
                        break;
                    }
                }
            } else if (query[i].opt == 4) {
                if (query[i].x == 0) continue;
                for (int j = 1; j * query[i].x <= maxA; j++) {
                    if (may[j] && may[j * query[i].x]) {
                        ans[query[i].id] = true;
                        break;
                    }
                }
            }
        }
        return;
    }
} CMO;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> opt >> l >> r >> x, CMO.query[i] = (CaptaimMo::Query) {i, opt, l, r, x}; CMO.solve();
    for (int i = 1; i <= m; i++) if (CMO.ans[i]) std::cout << "yuno" << '\n'; else std::cout << "yumi" << '\n';
    return 0;
}