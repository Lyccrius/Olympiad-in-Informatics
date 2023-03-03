#include <iostream>
#include <algorithm>

const int maxN = 30000;
const int maxA = 1e6;
const int maxQ = 2e5;
const int sqrtN = 174;

int n;
int a[maxN + 10];
int q;

struct CaptainMo {
    struct Query {
        int id;
        int bel;
        int l, r;

        bool operator<(const Query &other) const {
            if (bel != other.bel) return bel < other.bel;
            return r < other.r;
        }
    } query[maxQ + 10];

    void Init() {
        for (int i = 1; i <= q; i++) query[i].id = i;
        for (int i = 1; i <= q; i++) query[i].bel = (query[i].l - 1) / sqrtN + 1;
        std::sort(query + 1, query + q + 1);
        return;
    }

    int res;
    int cnt[maxA + 10];
    int ans[maxQ + 10];

    void Add(int pos) {
        if (cnt[a[pos]] == 0) res++;
        cnt[a[pos]]++;
        return;
    }

    void Del(int pos) {
        cnt[a[pos]]--;
        if (cnt[a[pos]] == 0) res--;
    }

    void Solve() {
        int l = 0;
        int r = 0;
        for (int i = 1; i <= q; i++) {
            while (l < query[i].l) {
                Del(l);
                l++;
            }
            while (l > query[i].l) {
                l--;
                Add(l);
            }
            while (r < query[i].r) {
                r++;
                Add(r);
            }
            while (r > query[i].r) {
                Del(r);
                r--;
            }
            ans[query[i].id] = res;
        }
        return;
    }

    void Show() {
        for (int i = 1; i <= q; i++) std::cout << ans[i] << '\n';
        return;
    }
} CM;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::cin >> q;
    for (int i = 1; i <= q; i++) std::cin >> CM.query[i].l >> CM.query[i].r;
    CM.Init();
    CM.Solve();
    CM.Show();
    return 0;
}